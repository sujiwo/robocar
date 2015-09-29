#include "Message.h"
#include "MessageQueue.h"
#include "hokuyo.h"
#include "HokuyoDriver.h"
#include "USBCameraDriver.h"
#include "CameraDriver.h"
#include "TextSensorDriver.h"
#include "debug.h"
#include "MessageRegisters.h"
#include <iostream>
#include <string>
#include <cstring>
#include <list>
#include <signal.h>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>

#ifdef HW_ROBOCAR
#include "DriveControl.h"
#include "IMUDriver.h"
#endif


using std::list;
using std::cerr;
using std::exception;
using std::string;
using boost::asio::ip::tcp;
using boost::asio::io_service;
using boost::thread;
typedef boost::interprocess::interprocess_semaphore semaphore;


#define ROBOCAR_DEFAULT_PORT 1607


namespace Robocar {


class Server
{
public:
	Server (bool _dryRun=false, bool _noVision=false) :
		doStop (false),
		lidardriver (NULL),
		usbcamdriver (NULL),
#ifdef HW_ROBOCAR
		camdriver (NULL),
		imu (NULL),
#endif
		dryRun (_dryRun),
		noVision (_noVision)
	{
		try {
			// Initialize server internals
			serverQueue = new MessageQueue ();
			iosrv = new io_service ();
			acceptor = new tcp::acceptor (*iosrv, tcp::endpoint(tcp::v4(), ROBOCAR_DEFAULT_PORT));
			driverInit ();

			} catch (exception &e) {
				cerr << e.what() << std::endl;
			}
	}


	void driverInit ()
	{
		// Initialize drivers
		textdriver = new TextSensorDriver (serverQueue);
		try {
			lidardriver = new HokuyoSensorDriver (serverQueue, "/dev/ttyACM0");
			debug ("LIDAR initialized");
		} catch (exception &e) {
			debug ("Unable to initialize LIDAR");
		}
		try {
			if (noVision==false) {
				usbcamdriver = new USBCameraDriver (serverQueue, "/dev/video0");
				debug ("USB Camera initialized");
			}
		} catch (exception &e) {
			debug ("Unable to initialize USB Camera");
		}

#ifdef HW_ROBOCAR
		if (dryRun==false) {
			DriveControl::startServer ();

			if (noVision==false) {
				camdriver = new CameraDriver (serverQueue);
				debug ("Built-in camera initialized");
			}

			imu = new IMUDriver (serverQueue);
			debug ("IMU initialized");
		}
#endif

		debug ("Drivers initialized");
	}


	void driverStart ()
	{
		// Starting drivers
		textdriver->start();
		if (lidardriver)
			lidardriver->start ();
		if (usbcamdriver)
			usbcamdriver->start ();

#ifdef HW_ROBOCAR
		if (dryRun==false) {
			if (camdriver != NULL) {
				camdriver->start();
				debug ("Built-in camera started");
			}
			imu->start();
			debug ("IMU started");
		}
#endif
		debug ("Drivers started");
	}


	void driverStop ()
	{
		textdriver->stop();
		if (lidardriver)
			lidardriver->stop ();
		if (usbcamdriver)
			usbcamdriver->stop ();
#ifdef HW_ROBOCAR
		if (dryRun==false) {
			if (camdriver != NULL) {
				camdriver->stop();
				debug ("Built-in camera stopped");
			}
			imu->stop();
		}
#endif
	}


	void driverDelete ()
	{
		try {
			delete textdriver;
			if (usbcamdriver != NULL) {
				delete usbcamdriver;
			}
			if (lidardriver != NULL) {
				delete lidardriver;
			}
		} catch (std::exception &e) {}

#ifdef HW_ROBOCAR
		if (dryRun==false) {
			if (camdriver != NULL)
				delete camdriver;
			delete imu;
			DriveControl::stopServer ();
		}
#endif
	}


	void start ()
	{
		acceptor->listen(1);
		tcp::socket *socket;
		int clientCount = 0;

		while (doStop == false) {

			socket = new tcp::socket (*iosrv);

			debug ("Accepting...");
			acceptor->accept (*socket);
			debug ("Get client !");
			clientCount += 1;

			driverStart ();

			while (true) {
				if (socket->is_open()==false || doStop==true) break;
				shared_ptr<Message> msg = serverQueue->pop ();
				try {
					msg->send (*socket);
					int tp = (int)msg->getType();
					//cout << "Sent message " << tp << endl;
				} catch (boost::system::system_error &serr) {
					debug ("Unable to send");
					break;
				}
			}
			debug ("Client closing!");

			driverStop();
			socket->close();
			delete (socket);

		}
	}

	void stop ()
	{
		debug ("Stopping Immediately");
		this->doStop = true;
	}

	~Server ()
	{
		// stop drivers and erase their threads
		driverStop ();
		driverDelete();

		// closing connections
		acceptor->close();
		iosrv->stop();

		// deallocate resources
		delete acceptor;
		delete iosrv;
		delete serverQueue;
	}

private:
	MessageQueue *serverQueue;
	tcp::acceptor *acceptor;
	io_service *iosrv;
	TextSensorDriver *textdriver;
	USBCameraDriver *usbcamdriver;
	HokuyoSensorDriver *lidardriver;
#ifdef HW_ROBOCAR
	CameraDriver *camdriver;
	IMUDriver *imu;
#endif

	volatile bool doStop;
	// if this variable is true, all routines correspond
	// to Robocar hardware will be skipped
	bool dryRun;
	// if this variable is true, all vision drivers
	// (cameras) will be disabled
	bool noVision;
};

}


Robocar::Server *_server;
void signalHandler (int s)
{
	_server->stop();
	delete (_server);
	exit (EXIT_SUCCESS);
}


/*
 * TODO: add clean shutdown
 */

int main (int argc, char **argv)
{
	bool dryRun = false, noVision = false;
	if (argc > 1) {
		string cmdarg1 (argv[1]);
		if (cmdarg1=="-nr") {
			dryRun = true;
		}
		else if (cmdarg1=="-nc") {
			noVision = true;
		}
		else if (cmdarg1=="-ncr" || cmdarg1=="nrc") {
			dryRun = true;
			noVision = true;
		}
	}

	Robocar::Server srv (dryRun, noVision);
	_server = &srv;

	signal (SIGTERM, signalHandler);
	signal (SIGINT, signalHandler);

	srv.start();
}
