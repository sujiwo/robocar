/*
 * Client.cpp
 *
 *  Created on: Dec 9, 2014
 *      Author: jiwo
 */

#include <iostream>
#include <string>
#include "string.h"
#include <stdlib.h>
#include <boost/asio.hpp>
#include "Message.h"
#include "HokuyoDriver.h"
#include "USBCameraDriver.h"
#include "debug.h"
#include "MessageRegisters.h"
#include <cstring>
#include <signal.h>
#include <boost/unordered_map.hpp>
#include <boost/function.hpp>
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/fill_image.h>
#include <std_msgs/String.h>
#include <nav_msgs/Odometry.h>
#include "IMUMessage.h"
#include "Odometer.h"


using std::string;
using std::cerr;
using std::cout;
using std::endl;
using boost::asio::ip::tcp;
using boost::asio::io_service;
using boost::unordered_map;


#define ROBOCAR_DEFAULT_PORT 1607


typedef boost::function <void (Robocar::Message*, ros::NodeHandle &roshdl)> messageHandlerFunc_t;


namespace Robocar {

uint32_t imageFrameId = 0;


class Client
{
public:
	Client (string hostname) :
		doStop (false),
		lidarFrameNumber (0)
	{
		lidarpub = roshandle.advertise <sensor_msgs::LaserScan> ("robocar_lidarscan", 100);
		imagepub1 = roshandle.advertise <sensor_msgs::Image> ("/robocar/camera/left", 10);
		imagepub2 = roshandle.advertise <sensor_msgs::Image> ("/robocar/camera/right", 10);
		textpub = roshandle.advertise <std_msgs::String> ("robocar_debug", 100);
		imupub = roshandle.advertise <nav_msgs::Odometry> ("robocar_odometry", 1000);

		// XXX: Only accept IP address
		boost::asio::ip::address serverAddress;
		serverAddress = boost::asio::ip::address::from_string(hostname);
		server.address (serverAddress);

		server.port (ROBOCAR_DEFAULT_PORT);
		iocli = new io_service ();
		socket = new tcp::socket (*iocli);
	}


	void start ()
	{
		socket->connect(server);
		while (doStop == false) {
			try {
				shared_ptr<Message> msg = Message::receive(*socket);
				int tp = (int)msg->getType();
				cout << "Type: " << tp << endl;

				switch (msg->getType()) {

					case TextSensorDriverMessageCategory:
						textMessageFunc(msg); break;

					case HokuyoDriverMessageCategory:
						lidar2dMessageFunc (msg); break;

					case USBCameraDriverMessageCategory:
						usbImageMessageFunc (msg); break;

					case CameraDriverMessageCategory:
						cameraImageMessageFunc (msg); break;

					case IMUMessageCategory :
						imuMessageFunc (msg); break;
				}
			} catch (std::exception &e) {
				cout << "Why? " << e.what() << endl;
				exit (EXIT_FAILURE);
			}
		}
		socket->close();
		cerr << "Stopped" << endl;
	}


	void stop ()
	{
		doStop = true;
	}


	~Client ()
	{
		delete (socket);
		delete (iocli);
	}


	void textMessageFunc (shared_ptr<Message> msg)
	{
		std_msgs::String debugmsg;
		string s (msg->getContent(), msg->getSize());
		debugmsg.data = s;
		textpub.publish(debugmsg);
	}


	void lidar2dMessageFunc (shared_ptr<Message> message)
	{
		shared_ptr<hokuyo::LaserScan> scanrecv = Robocar::HokuyoMessage::deserialize(*message.get());
		sensor_msgs::LaserScan scanmsg;
		scanmsg.angle_min = scanrecv->config.min_angle;
		scanmsg.angle_max = scanrecv->config.max_angle;
		scanmsg.range_min = scanrecv->config.min_range;
		scanmsg.range_max = scanrecv->config.max_range;
		scanmsg.scan_time = scanrecv->config.scan_time;
		scanmsg.ranges = scanrecv->ranges;
		scanmsg.angle_increment = scanrecv->config.ang_increment;
		scanmsg.intensities = scanrecv->intensities;
		scanmsg.header.seq = lidarFrameNumber++;
		scanmsg.header.frame_id = string("robocar_lidar");

		lidarpub.publish(scanmsg);
	}


	// XXX: Implicit assumption of image size
#define DefaultImageWidth 640
#define DefaultImageHeight 480
	void usbImageMessageFunc (shared_ptr<Message> message)
	{
		sensor_msgs::Image img;
		sensor_msgs::fillImage (img, "rgb8",
			DefaultImageHeight, DefaultImageWidth, 3*DefaultImageWidth,
			(void*)message->getContent());
		img.header.frame_id = imageFrameId++;
		imagepub1.publish(img);
	}


// XXX: Improve stereo camera support
	void cameraImageMessageFunc (shared_ptr<Message> imageMsg)
	{
		sensor_msgs::Image imgLeft, imgRight;

		uint16_t *sizes = (uint16_t*)imageMsg->getContent();
		uint8_t *imageData = (uint8_t*)&sizes[2];
		printf ("%d x %d\n", sizes[0], sizes[1]);

		//shared_ptr<uint8_t> stereoImg = processStereo (sizes[0], sizes[1], 1, imageData);

		uint8_t *left = imageData,
			*right = &(imageData[sizes[1]*sizes[0]]);
		
		sensor_msgs::fillImage (imgLeft, "mono8",
			sizes[1], sizes[0], sizes[0],
			(void*)left);
		imgLeft.header.frame_id = "Robocar";
		imagepub1.publish (imgLeft);

		sensor_msgs::fillImage (imgRight, "mono8",
			sizes[1], sizes[0], sizes[0],
			(void*)right);
		imgRight.header.frame_id = "Robocar";
		imagepub2.publish (imgRight);

	}


	static shared_ptr<uint8_t> processStereo (int width, int height, int bytePerPix, shared_ptr<uint8_t> source)
	{
		return processStereo (width, height, bytePerPix, source.get());
	}


	static shared_ptr<uint8_t> processStereo (int width, int height, int bytePerPix, uint8_t* source)
	{
		uint32_t size = width*height*bytePerPix*2;
		shared_ptr<uint8_t> retval (new uint8_t [size]);
		uint8_t* target = retval.get();
		uint8_t *left = source,
			*right = &source[size/2];

		for (int i=0; i<height; i++) {
			memcpy (&target[i*2*width], &left[i*width], width*bytePerPix);
			memcpy (&target[width*(i*2+1)], &right[i*width], width*bytePerPix);
		}

		return retval;
	}


	void imuMessageFunc (shared_ptr<Message> imuMsg)
	{
		// Nasty bug is expected due to wrong time
		float *imudata = (float*)imuMsg->getContent();

		Vector3 accel (imudata[SENSOR_ACCELERATION_X],
			imudata[SENSOR_ACCELERATION_Y],
			imudata[SENSOR_ACCELERATION_Z]);
		odometer.updateAcceleration (accel, imuMsg->getPtime());
		odometer.updateAttitude(imudata[SENSOR_GYRO], imuMsg->getPtime());

		Vector3 &pos = odometer.getPosition(),
			&velocity = odometer.getVelocity();
		Quat orientation = odometer.getAttitude();

		nav_msgs::Odometry odomsg;
		odomsg.header.stamp = odometer.getRosTime();
		odomsg.header.frame_id = "robocar_odometer";

		pos = odometer.getPosition();
		odomsg.pose.pose.position.x = pos.x();
		odomsg.pose.pose.position.y = pos.y();
		odomsg.pose.pose.position.z = pos.z();

		Quat q = odometer.getAttitude();
		odomsg.pose.pose.orientation.w = q.w;
		odomsg.pose.pose.orientation.x = q.x;
		odomsg.pose.pose.orientation.y = q.y;
		odomsg.pose.pose.orientation.z = q.z;

		velocity = odometer.getVelocity();
		odomsg.twist.twist.linear.x = velocity.x();
		odomsg.twist.twist.linear.y = velocity.y();
		odomsg.twist.twist.linear.z = velocity.z();

		imupub.publish (odomsg);
	}


private:
	tcp::endpoint server;
	tcp::socket *socket;
	io_service *iocli;
	volatile bool doStop;
	//unordered_map <int, messageHandlerFunc_t> messageHandlers;

	ros::NodeHandle roshandle;
	ros::Publisher lidarpub;
	ros::Publisher imagepub1, imagepub2;
	ros::Publisher textpub;
	ros::Publisher imupub;

	int lidarFrameNumber;
	Odometer odometer;
};

}



Robocar::Client *__client;
void clientSignalHandler (int signalNumber)
{
	__client->stop();
}




int main (int argc, char **argv)
{
	ros::init (argc, argv, "robocar_client_node");
	string adr (argv[1]);
	Robocar::Client client (adr);
	__client = &client;
	signal (SIGINT, clientSignalHandler);
	signal (SIGTERM, clientSignalHandler);

	client.start();
}
