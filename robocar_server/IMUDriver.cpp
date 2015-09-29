/*
 * IMUDriver.cpp
 *
 *  Created on: Dec 26, 2014
 *      Author: sujiwo
 */

#include "IMUDriver.h"
#include "zmp/Baseboard.h"
#include "zmp/BaseboardCom.h"
#include "string.h"


namespace Robocar {


IMUDriver::IMUDriver(MessageQueue *_srvq) :
	serverMessageQueue (_srvq),
	control (DriveControl::getInstance()->getDrive()),
	controlLock (DriveControl::getInstance()->getSemaphore()),
	doStop (false), doQuit (false)
{
	startSignal = new semaphore (0);
	ProbingDelay = (long int)(1e6/(float)DefaultProbingRate);
	drvThread = new boost::thread (&threadEntryPoint, this);
}


IMUDriver::~IMUDriver()
{
	delete (startSignal);
}


void IMUDriver::init ()
{
}


void IMUDriver::threadEntryPoint (IMUDriver *drv)
{
	drv->startSignal->wait ();
	drv->work ();
}


void IMUDriver::work ()
{
	doStop = false;

	while (doQuit==false) {
		while (doStop == false) {

			zmp::zrc::POWER_VALUE pwr;
			zmp::zrc::SENSOR_VALUE snr;
			memset (&pwr, 0, sizeof(pwr));
			memset (&snr, 0, sizeof(snr));

			controlLock->wait ();
			control->GetPowerInfoReq (&pwr);
			control->GetSensorInfoReq (&snr);
			controlLock->post ();

			// format message
			float *imudata = new float [ImuArraySize];
			shared_ptr<uint8_t> ImuPtr ((uint8_t*)imudata);
			imudata [SENSOR_GYRO] = snr.gyro;
			imudata [SENSOR_ACCELERATION_X] = snr.acc_x;
			imudata [SENSOR_ACCELERATION_Y] = snr.acc_y;
			imudata [SENSOR_ACCELERATION_Z] = snr.acc_z;
			imudata [SENSOR_ENCODER_MOTOR] = snr.enc_0;
			imudata [SENSOR_ENCODER_WHEEL_1] = snr.enc_1;
			imudata [SENSOR_ENCODER_WHEEL_2] = snr.enc_2;
			imudata [SENSOR_ENCODER_WHEEL_3] = snr.enc_3;
			imudata [SENSOR_ENCODER_WHEEL_4] = snr.enc_4;
			imudata [POWER_CURRENT] = pwr.motor_current;
			imudata [POWER_BATTERYLEVEL] = pwr.battery_level;

			shared_ptr<Message> imumsg = Message::create (
				IMUMessageCategory,
				IMUDriver::messageSize(),
				ImuPtr);

			serverMessageQueue->push(imumsg);

			usleep (ProbingDelay);
		}

		if (doQuit==true) break;
		startSignal->wait();
	}
}


void IMUDriver::start ()
{
	doStop = false;
	startSignal->post();
}


void IMUDriver::stop ()
{
	doStop = true;
}

} /* namespace Robocar */
