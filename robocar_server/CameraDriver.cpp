/*
 * Camera.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: sujiwo
 */

#include "CameraDriver.h"
#include "string.h"
#include "debug.h"
#include <iostream>
#include <boost/shared_ptr.hpp>
#include "NetpbmWriter.h"


using std::cerr;
using std::endl;


namespace Robocar {


CameraDriver::CameraDriver (MessageQueue *_msgq) :
	srvQueue (_msgq),
	doStop (false), doQuit(false)
{
	this->init ();
	startSignal = new semaphore (0);
	intervalPerFrame = (long int)(1e6/(float)CameraFrameRate);
	drvThread = new thread (&threadEntryPoint, this);
}


void CameraDriver::init ()
{
	ipm.Init ();
	ipm.StopImap ();
	ipm.Reset ();
	// Why this program must be loaded? still not clear to me
	ipm.LoadProgram (zmp::zrc::IMAP_ALG_STEREO_OBSTACLES_1);
	ipm.StartImap();
	// XXX: Need to change channel
	ipm.SelectImageOutput (zmp::zrc::SOF_NORMALIZED_STEREO);
	ipm.SelectResultOutput (zmp::zrc::SOR_RESULT_LANE);
	ipm.Wait();
	// Fake collect call is needed, by trial
	ipm.CollectResult ();
	ipm.CollectImage ();
}


void CameraDriver::start ()
{
	doStop = false;
	startSignal->post();
}


void CameraDriver::stop ()
{ doStop = true; }


CameraDriver::~CameraDriver()
{
	ipm.StopImap ();
}


void CameraDriver::work()
{
	doStop = false;

	while (doQuit==false) {
		while (doStop==false) {
			if (ipm.CollectImage ()) {
				// XXX: need better way to determine resolution
				shared_ptr<ImageMessage> image (new ImageMessage(320, 240, ipm));
				Message *msg = (Message*)image.get();
				srvQueue->push (image);
				//debug ("CameraDriver: Pushed image");
			}
			else {
				debug ("Unable to grab stereo image");
			}
			//ipm.Wait();
			usleep (intervalPerFrame);
		}

		if (doQuit==true) break;
		startSignal->wait();
	}
}


/*
 * Robocar's camera can only capture grayscale image, so it's
 * safe to say that byte per pixel=1
 */
ImageMessage::ImageMessage (int w, int h, zmp::zrc::IpmManager &ipm) :
	width (w),
	height (h)
{
	int imgbytes = ipm.ImageLength();
	int msgsize = imgbytes + 2*sizeof(uint16_t);
	content = shared_ptr<uint8_t> (new uint8_t [imgbytes]);
	uint16_t *pictsize = (uint16_t*)content.get();
	pictsize[0] = (uint16_t)w;
	pictsize[1] = (uint16_t)h;
	//cerr << "Size: " << size[0] << "X" << size[1] << endl;
	data = (uint8_t*)&pictsize[2];
	memcpy (data, ipm.ImageData(), imgbytes);

	//timestamp = (uint64_t)time(NULL);
	size = msgsize;
	type = CameraDriverMessageCategory;
	gettimeofday (&timestamp, NULL);
}

}
