/*
 * SensorDriver.h
 *
 *  Created on: Dec 15, 2014
 *      Author: jiwo
 */

#ifndef SENSORDRIVER_H_
#define SENSORDRIVER_H_


#include "Message.h"
#include "MessageQueue.h"
#include <boost/thread.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>


using boost::thread;
typedef boost::interprocess::interprocess_semaphore semaphore;



namespace Robocar
{


class SensorDriver
{
public:
	SensorDriver (MessageQueue *_q) :
		srvQueue (_q),
		doStop (false)
	{
		init ();
		startSignal = new semaphore (0);
		drvThread = new thread ();
	}

	virtual void init ();

	static void threadEntryPoint (TextSensorDriver *drv)
	{
		debug ("threadEntryPoint, wait...");
		// wait for signal
		drv->startSignal->wait();
		drv->work ();
	}

protected:
	MessageQueue *srvQueue;
	thread *drvThread;
	bool doStop;
	semaphore *startSignal;
};


}


#endif /* SENSORDRIVER_H_ */
