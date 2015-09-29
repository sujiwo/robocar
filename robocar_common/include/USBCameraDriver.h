/*
 * USBCameraDriver.h
 *
 *  Created on: Dec 11, 2014
 *      Author: jiwo
 */

#ifndef USBCAMERADRIVER_H_
#define USBCAMERADRIVER_H_


#include "Message.h"
#include "MessageQueue.h"
#include <vector>
#include <boost/thread.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>
#include <exception>
#include "usb_cam.h"


#define defaultFrameRate 15


using boost::thread;
typedef boost::interprocess::interprocess_semaphore semaphore;


namespace Robocar {

class USBCameraDriver
{
public:
	USBCameraDriver (MessageQueue *_msgq, const char *_devfilename);
	virtual ~USBCameraDriver ();

	void init ();

	static void threadEntryPoint (USBCameraDriver *drv);

	inline void setFrameRate (int rate=defaultFrameRate)
	{ intervalPerFrame = (long int)(1e6/(float)rate); }

	void work ();

	void start ();

	void stop () ;

private:
	MessageQueue *srvQueue;
	boost::thread *drvThread;
	volatile bool doStop, doQuit;
	boost::interprocess::interprocess_semaphore *startSignal;
	const char *devfilename;
	usb_cam_camera_image_t *camera;
	useconds_t intervalPerFrame;
	uint32_t lastImageSize;

	shared_ptr<uint8_t> imageHandler ();
};

} /* namespace Robocar */

#endif /* USBCAMERADRIVER_H_ */
