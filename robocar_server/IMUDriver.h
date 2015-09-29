/*
 * IMUDriver.h
 *
 *  Created on: Dec 26, 2014
 *      Author: sujiwo
 */

#ifndef ROBOCAR_SERVER_IMUDRIVER_H_
#define ROBOCAR_SERVER_IMUDRIVER_H_

#include "zmp/RcControl.h"
#include "MessageQueue.h"
#include "DriveControl.h"
#include "IMUMessage.h"
#include "MessageRegisters.h"
#include <boost/interprocess/sync/interprocess_semaphore.hpp>


typedef boost::interprocess::interprocess_semaphore semaphore;


namespace Robocar
{

// In Frame-per-second
const int DefaultProbingRate = 5;

class IMUDriver
{
public:
	IMUDriver (MessageQueue *);
	virtual ~IMUDriver();
	void init () ;

	static void threadEntryPoint (IMUDriver *drv) ;

	void work ();

	void start ();

	void stop () ;

	inline size_t messageSize ()
	{ return ImuArraySize*sizeof(float); }

private:
	MessageQueue *serverMessageQueue;
	zmp::zrc::RcControl *control;
	semaphore *controlLock;
	semaphore *startSignal;
	volatile bool doStop, doQuit;
	useconds_t ProbingDelay;
	boost::thread *drvThread;
};

} /* namespace Robocar */

#endif /* ROBOCAR_SERVER_IMUDRIVER_H_ */
