/*
 * TextSensorDriver.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: jiwo
 */

#include "TextSensorDriver.h"


namespace Robocar {


TextSensorDriver::TextSensorDriver(MessageQueue *_msgq) :
	srvQueue(_msgq),
	doStop (false), doQuit (false)
{
	init ();
	startSignal = new semaphore (0);
	drvThread = new thread (&threadEntryPoint, this);
}


void TextSensorDriver::init()
{ text = string("Hello World"); }


TextSensorDriver::~TextSensorDriver()
{
	delete drvThread;
}


void TextSensorDriver::threadEntryPoint (TextSensorDriver *drv)
{
	// wait for signal
	drv->startSignal->wait();
	drv->work ();
}


void TextSensorDriver::work ()
{
	doStop = false;

	debug ("textdriver doing work");
	while (doQuit==false) {
		while (doStop==false) {
			unsigned char *buf = new unsigned char[text.size()];
			memcpy (buf, text.c_str(), text.size());
			shared_ptr<Message> txt = Message::create (TextSensorDriverMessageCategory, text.size(), buf);
			srvQueue->push (txt);
			sleep (WaitTime);
		}
		if (doQuit==true) break;
		startSignal->wait();
	}
}


void TextSensorDriver::stop ()
{
	doStop = true;
}


void TextSensorDriver::start ()
{
	doStop = false;
	startSignal->post();
}



} /* namespace Robocar */
