/*
 * USBCameraDriver.cpp
 *
 *  Created on: Dec 11, 2014
 *      Author: jiwo
 */

#include "USBCameraDriver.h"
#include <unistd.h>
#include <string.h>
#include "debug.h"
#include "MessageRegisters.h"
#include <zlib.h>




namespace Robocar {

USBCameraDriver::USBCameraDriver(MessageQueue *_msgq, const char *_devfilename) :
	devfilename (_devfilename),
	camera (NULL),
	doStop (false), doQuit(false),
	srvQueue (_msgq),
	lastImageSize (0)
{
	this->init ();
	startSignal = new semaphore (0);
	drvThread = new thread (&threadEntryPoint, this);
	setFrameRate();
}


void USBCameraDriver::init ()
{
	camera = usb_cam_camera_start(devfilename, 640, 480, defaultFrameRate);
}


void USBCameraDriver::threadEntryPoint(USBCameraDriver *drv)
{
	drv->startSignal->wait ();
	drv->work ();
}


// XXX: This means that the image will be sent uncompressed
// Investigate zlib
shared_ptr<uint8_t> USBCameraDriver::imageHandler ()
{
	shared_ptr<uint8_t> camImg (new uint8_t [camera->image_size]);
	memcpy (camImg.get(), camera->image, camera->image_size);
	lastImageSize = camera->image_size;
	return camImg;
}


void USBCameraDriver::work ()
{
	while (doQuit==false) {
		while (doStop==false) {
			usb_cam_camera_grab_image (camera);
			shared_ptr<uint8_t> camImg = imageHandler ();
			shared_ptr<Message> camMsg =
				Message::create (USBCameraDriverMessageCategory, lastImageSize, camImg);
			srvQueue->push (camMsg);
			usleep (intervalPerFrame);
		}
		if (doQuit==true) break;
		startSignal->wait();
	}
}


void USBCameraDriver::start()
{
	doStop = false;
	startSignal->post();
}


void USBCameraDriver::stop ()
{
	doStop = true;
}


USBCameraDriver::~USBCameraDriver()
{
	usb_cam_camera_shutdown ();
	delete (camera);
}

} /* namespace Robocar */
