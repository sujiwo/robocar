/*
 * HokuyoDriver.cpp
 *
 *  Created on: Dec 10, 2014
 *      Author: jiwo
 */


#include "MessageRegisters.h"
#include "HokuyoDriver.h"
#include "debug.h"
/*#include "boost/date_time/posix_time/posix_time.hpp"


using boost::posix_time;
using boost::posix_time::ptime;*/


namespace Robocar
{


struct timeval nanosecond_to_timeval (const uint64_t nanosec)
{
	double tsec = nanosec * 1e-9;
	struct timeval tv;
	tv.tv_sec = (time_t)tsec;
	tv.tv_usec = (nanosec-(uint64_t)(tv.tv_sec*1e9))*1e-3;
	return tv;
}


uint64_t timeval_to_nanosecond (const struct timeval &tv)
{
	uint64_t ns1 = tv.tv_sec * 1e9;
	uint64_t ns2 = tv.tv_usec * 1e3;
	return ns1 + ns2;
}


HokuyoMessage::HokuyoMessage (hokuyo::LaserScan &scanResult)
{
	timestamp = nanosecond_to_timeval (scanResult.system_time_stamp);
	uint32_t msgContentSize;
	content = HokuyoSensorDriver::serializeMessage(scanResult, msgContentSize);
	this->size = msgContentSize;
}


shared_ptr<hokuyo::LaserScan> HokuyoMessage::deserialize(Message &msg)
{
	shared_ptr<hokuyo::LaserScan> scanrecv (new hokuyo::LaserScan ());
	_hokuyoMessageBuffer *scanmsg = (_hokuyoMessageBuffer*)msg.getContent();

	scanrecv->system_time_stamp = timeval_to_nanosecond (msg.getTimestamp());
	scanrecv->config.min_angle = scanmsg->min_angle;
	scanrecv->config.max_angle = scanmsg->max_angle;
	scanrecv->config.min_range = scanmsg->min_range;
	scanrecv->config.max_range = scanmsg->max_range;
	scanrecv->config.ang_increment = scanmsg->angular_increment;
	float *ranges = (float*)&scanmsg->_ranges;
	createVectorFromArray<float> (ranges,
		scanmsg->num_ranges,
		scanrecv->ranges);
	//void *ptrForIntensity = (void*)&(scanmsg->_ranges) + scanmsg->num_ranges*sizeof(float);
	float *ptrForIntensity = &ranges[scanmsg->num_ranges];
	createVectorFromArray<float> (ptrForIntensity,
		scanmsg->num_ranges,
		scanrecv->intensities);

	return scanrecv;
}


HokuyoSensorDriver::HokuyoSensorDriver (MessageQueue *_msgq, const char *_devfilename) :
	srvQueue(_msgq),
	devfilename(_devfilename),
	doStop (false)
{
	init ();
	startSignal = new semaphore (0);
	drvThread = new thread (&threadEntryPoint, this);
}


HokuyoSensorDriver::~HokuyoSensorDriver ()
{
	laser->close();
	delete laser;
}


void HokuyoSensorDriver::init ()
{
	laser = new hokuyo::Laser ();
	laser->open (devfilename);
	laser->getConfig (this->laserconf);
}


void HokuyoSensorDriver::threadEntryPoint (HokuyoSensorDriver *drv)
{
	drv->startSignal->wait ();
	drv->work ();
}


void HokuyoSensorDriver::work ()
{
	while (doQuit==false) {
		hokuyo::LaserScan scanResult;

		laser->laserOn();
		debug ("Laser scans work");
		laser->requestScans(false,
			laserconf.min_angle,
			laserconf.max_angle);

		while (doStop==false) {
			int status = laser->serviceScan (scanResult);
			if (status != 0) {
				debug ("Error getting scan");
				break;
			}

			uint32_t bufferSize;
			shared_ptr<uint8_t> buffer =
				HokuyoSensorDriver::serializeMessage
					(scanResult, bufferSize);
			shared_ptr<Message> sensorMsg
				(new Message (
					HokuyoDriverMessageCategory,
					bufferSize,
					buffer));
			srvQueue->push(sensorMsg);
			//sendScan (scanResult);
		}

		laser->stopScanning();
		laser->laserOff();

		if (doQuit==true) break;
		startSignal->wait();
	}
}


shared_ptr <uint8_t>
HokuyoSensorDriver::serializeMessage (hokuyo::LaserScan &scanResult, uint32_t &bufferSize)
{
	// determine size
	bufferSize = sizeof(_hokuyoMessageBuffer) - 1;
	// add intensity
	bufferSize += (scanResult.ranges.size() * sizeof(float));
	bufferSize += (scanResult.intensities.size() * sizeof(float));

	// buffer
	_hokuyoMessageBuffer *msgBuf = (_hokuyoMessageBuffer*)malloc (bufferSize);
	msgBuf->min_angle = scanResult.config.min_angle;
	msgBuf->max_angle = scanResult.config.max_angle;
	msgBuf->angular_increment = scanResult.config.ang_increment;
	msgBuf->scan_time = scanResult.config.scan_time;
	msgBuf->min_range = scanResult.config.min_range;
	msgBuf->max_range = scanResult.config.max_range;
	msgBuf->num_ranges = scanResult.ranges.size();
	// copy data
	memcpy (&(msgBuf->_ranges), scanResult.ranges.data(), msgBuf->num_ranges*sizeof(float));
	//void *ptrForIntensity = (void*)&(msgBuf->_ranges) + scanResult.ranges.size()*sizeof(float);
	float *ptrForIntensity = &(((float*)(msgBuf->_ranges))[scanResult.ranges.size()]);
	memcpy (ptrForIntensity, scanResult.intensities.data(), scanResult.intensities.size()*sizeof(float));

	return shared_ptr<uint8_t> ((unsigned char*)msgBuf);
}


void HokuyoSensorDriver::stop ()
{
	this->doStop = true;
}


void HokuyoSensorDriver::start()
{
	doStop = false;
	startSignal->post();
}

}
