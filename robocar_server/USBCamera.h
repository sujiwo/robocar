/*
 * USBCamera.h
 *
 *  Created on: Dec 13, 2014
 *      Author: jiwo
 */

#ifndef USBCAMERA_H_
#define USBCAMERA_H_


#include <libv4l2.h>
#include <linux/videodev2.h>
#include <exception>
#include <stdint.h>
#include <unistd.h>
#include <string.h>
#include <memory>


using std::auto_ptr;


#pragma pack (push)
#pragma pack (1)
struct yuyvPixel {
	uint8_t y0, u, y1, v;
};

struct rgbPixel {
	uint8_t r, g, b;
};
#pragma pack (pop)


template <typename PixelType>
class CameraImage
{
private:
	uint32_t width;
	uint32_t height;
	PixelType *data;

public:
	CameraImage () :
		width(0), height(0), data(NULL) {}

	CameraImage (int _width, int _height, void *imgdata) :
		width(_width), height(_height)
	{ data = ((PixelType*)imgdata); }

	CameraImage (int _width, int _height) :
		width (_width), height(_height)
	{
		this->data = new PixelType [width*height];
		memset (this->data, 0, width*height*sizeof(PixelType));
	}

	CameraImage (CameraImage &src) :
		width(src.width), height(src.height), data(src.data)
	{}

	void destroy ()
	{ delete[] data; }

	PixelType& at (int bar, int col)
	{ return data [bar*width + col]; }

	PixelType& operator () (int bar, int col)
	{ return at (bar, col); }

	PixelType& idx (int i)
	{ return data [i]; }

	PixelType& operator [] (int i)
	{ return idx (i); }

	int getWidth () { return this->width; }
	int getHeight () { return this->height; }
	PixelType* getData () { return this->data; }
};


typedef CameraImage <yuyvPixel> yuyvImage;
typedef CameraImage <rgbPixel> rgbImage;


// XXX: need better ways to define length of request buffer
#define RequestBufferLength 1


struct CameraBuffer {
	uint8_t *start;
	size_t length;
};


class USBCameraException : public std::exception
{
public:
	USBCameraException (const char *_msg) : msg(_msg) {}
	inline const char *what () { return msg; }

private:
	const char *msg;
};


class USBCamera
{
public:
	USBCamera (const char *deviceName) ;
	~USBCamera ();
	void start ();
	void stop ();
	void finish ();

	// Capture a frame, send as yuyv data
	yuyvImage * capture ();

	// Conversion
	static
	rgbImage * yuyv2rgb (yuyvImage &source);

	inline int getWidth () { return width; }
	inline int getHeight () { return height; }

private:
	int fd;
	uint32_t width;
	uint32_t height;
	size_t bufferCount;
	CameraBuffer *buffers;
	CameraBuffer head;
};



#endif /* USBCAMERA_H_ */
