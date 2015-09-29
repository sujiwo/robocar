/*
 * TextSensorDriver.h
 *
 *  Created on: Jan 8, 2015
 *      Author: jiwo
 */

#ifndef TEXTSENSORDRIVER_H_
#define TEXTSENSORDRIVER_H_

#include "Message.h"
#include "MessageQueue.h"
#include "MessageRegisters.h"
#include "debug.h"
#include <string>
#include <boost/thread.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>


using boost::thread;
using std::string;
typedef boost::interprocess::interprocess_semaphore semaphore;

const int WaitTime = 2;


namespace Robocar {

class TextSensorDriver
{
public:
	TextSensorDriver (MessageQueue *_msgq);
	~TextSensorDriver ();
	void init ();

	static void threadEntryPoint (TextSensorDriver *drv);
	void work ();
	void start ();
	void stop ();

private:
	MessageQueue *srvQueue;
	thread *drvThread;
volatile bool doStop, doQuit;
	string text;
	semaphore *startSignal;
};

} /* namespace Robocar */

#endif /* TEXTSENSORDRIVER_H_ */
