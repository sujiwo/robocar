/*
 * USBCameraDriver.h
 *
 *  Created on: Dec 11, 2014
 *      Author: jiwo
 */

#ifndef CAMERADRIVER_H_
#define CAMERADRIVER_H_


#include "Message.h"
#include "MessageQueue.h"
#include "zmp/IpmManager.h"
#include "MessageRegisters.h"
#include <boost/thread.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <exception>
#include <stdint.h>




using boost::thread;
typedef boost::interprocess::interprocess_semaphore semaphore;

const int CameraFrameRate = 7;


namespace Robocar {


class ImageMessage : public Message
{
public:
	ImageMessage (int width, int height, zmp::zrc::IpmManager &ipm);
	//~ImageMessage ();
	//_messageBuffer *serialize ();
	//static ImageMessage* deserialize (Message* msg);
	inline uint8_t* getData () { return data; }

private:
	int width, height;
	uint8_t* data;
};


class CameraDriver
{
public:
	CameraDriver (MessageQueue *_msgq);
	~CameraDriver ();

	void init ();

	inline static void threadEntryPoint (CameraDriver *drv)
	{
		drv->startSignal->wait ();
		drv->work ();
	}

	void work ();

	void start ();

	void stop ();

private:
	MessageQueue *srvQueue;
	boost::thread *drvThread;
	volatile bool doStop, doQuit;
	boost::interprocess::interprocess_semaphore *startSignal;
	zmp::zrc::IpmManager ipm;
	useconds_t intervalPerFrame;
};

} /* namespace Robocar */

#endif /* USBCAMERADRIVER_H_ */
