/*
 * DriveControl.cpp
 *
 *  Created on: Jan 5, 2015
 *      Author: sujiwo
 */

#include "DriveControl.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <boost/asio.hpp>


using boost::asio::io_service;
//using boost::asio::ip;
using boost::asio::ip::tcp;


namespace Robocar {


/*inline float clamp (float m1, float v, float m2)
{
	return (m1 > v) ? m1 : (m2 < v ? m2 : v);
}*/
#define clamp(minval, val, maxval) \
	(minval > val) ? minval : (maxval < val ? maxval : val)


DriveControl::DriveControl() :
	driveControlLock (NULL), serverThread (NULL),
	gearPosition (GEAR_BRAKE),
	doStop (false)
{
	// Robocar Init
	system ("ipm_serial S 4 0");
	sleep (1);
	system ("ipm_serial S 4 1");
	sleep (1);
	drivecontrol.init ();
	drivecontrol.Start ();
	// XXX: ZMP should provide enum more clearly...
	drivecontrol.SetReportFlagReq(7);
	drivecontrol.SetServoEnable(1);
	drivecontrol.SetMotorEnableReq(1);
	drivecontrol.SetDriveSpeed(0);
	drivecontrol.SetSteerAngle(0);

	driveControlLock = new boost::interprocess::interprocess_semaphore (1);
}


DriveControl::~DriveControl()
{
	drivecontrol.Stop();
	drivecontrol.Close();
	delete (driveControlLock);
}


void DriveControlThreadWork ()
{
	DriveControl *driveControl = DriveControl::getInstance();
	io_service iosrv;
	tcp::acceptor acceptor (iosrv,
		tcp::endpoint(
			tcp::v4(), ROBOCAR_DRIVER_PORT
		)
	);

	acceptor.listen(1);
	while (true) {
		tcp::socket *socket = new tcp::socket(iosrv);
		acceptor.accept (*socket);

		while (true) {
			if (socket->is_open()==false)
				break;

			int frmRuntimeMgr[5];
			boost::asio::mutable_buffers_1 readbuf = boost::asio::buffer (frmRuntimeMgr);

			boost::asio::read (*socket, readbuf);

			// Fixing values, then change state
			// XXX: only steering & acceleration are currently supported
			DriveMessage newState;
			newState.steering = clamp (-30.0, 30.0*(float)frmRuntimeMgr[0]/120.0, 30.0);
			newState.acceleration = (int)clamp (0, 2800.0*(float)frmRuntimeMgr[1]/100.0, 2800);
			newState.gear = frmRuntimeMgr[3];
			driveControl->changeState (newState);

			//driveControl->getState (newState);
			frmRuntimeMgr[0] = (int)(120.0*newState.steering/30.0);
			frmRuntimeMgr[1] = (int)(100.0*newState.acceleration/2800.0);
			frmRuntimeMgr[3] = newState.gear;

			boost::asio::write (*socket, readbuf);
		}

		socket->close();
		delete(socket);
	}
}


void DriveControl::changeState(DriveMessage &newstate)
{
	//printf ("Gear: %d; Steering: %f; Acceleration: %d\n", newstate.gear, newstate.steering, newstate.acceleration);
	driveControlLock->wait();
	gearPosition = newstate.gear;
	drivecontrol.SetSteerAngle (newstate.steering);
	int acceleration;

	switch (gearPosition) {
	case GEAR_RETREAT:
		acceleration = -newstate.acceleration; break;
	case GEAR_DRIVE:
		acceleration = newstate.acceleration; break;
	default:
		acceleration = 0;
	}
	//printf ("Acceleration: %d\n", acceleration);
	drivecontrol.SetDriveSpeed (acceleration);

	driveControlLock->post();
}


void DriveControl::getState(DriveMessage &state)
{
	driveControlLock->wait ();
	drivecontrol.GetPresentSpeed (&state.acceleration);
	state.acceleration = abs(state.acceleration);
	driveControlLock->post ();
}


void DriveControl::startServer()
{
	DriveControl *driveControl = DriveControl::getInstance();
	driveControl->serverThread = new boost::thread (DriveControlThreadWork);
}


void DriveControl::stopServer()
{

}


} /* namespace Robocar */
