/*
 * DriveControl.h
 *
 *  Created on: Jan 5, 2015
 *      Author: sujiwo
 */

#ifndef ROBOCAR_SERVER_DRIVECONTROL_H_
#define ROBOCAR_SERVER_DRIVECONTROL_H_


#include "zmp/RcControl.h"
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <boost/thread.hpp>

namespace Robocar {

#define ROBOCAR_DRIVER_PORT 12345


#pragma pack (push)
#pragma pack (1)

struct DriveMessage {
	float steering;
	int	acceleration,
		brake;
	int	gear,
		mode;
};
#pragma pack (pop)


enum GEAR_POSITION {
	GEAR_BRAKE = 0,
	GEAR_RETREAT = 1,
	GEAR_NEUTRAL = 2,
	GEAR_DRIVE = 3,
};


class DriveControl
{
public:
	DriveControl();

	~DriveControl();

	static DriveControl *getInstance ()
	{
		static DriveControl* instance = new DriveControl ();
		return instance;
	}

	static void stopInstance ()
	{
		DriveControl::getInstance()->~DriveControl();
	}

	static void startServer ();

	static void stopServer ();

	zmp::zrc::RcControl *getDrive ()
	{ return &drivecontrol; }

	boost::interprocess::interprocess_semaphore *getSemaphore ()
	{ return driveControlLock; }

	void changeState (DriveMessage &newState);

	void getState (DriveMessage &state);

private:
	zmp::zrc::RcControl drivecontrol;
	boost::interprocess::interprocess_semaphore *driveControlLock;
	boost::thread *serverThread;
	int gearPosition;
	volatile bool doStop;
};


} /* namespace Robocar */

#endif /* ROBOCAR_SERVER_DRIVECONTROL_H_ */
