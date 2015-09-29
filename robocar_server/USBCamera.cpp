/*
 * USBCamera.cpp
 *
 *  Created on: Dec 13, 2014
 *      Author: jiwo
 */


#include "debug.h"
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <sys/select.h>
#include <stdlib.h>
#include <fcntl.h>
#include "USBCamera.h"



int xioctl (int fd, int request, void *arg)
{
	return ioctl (fd, request, arg);
}


USBCamera::USBCamera (const char *devfilename)
{
	fd = v4l2_open (devfilename, O_RDWR);
	if (fd==-1)
		throw USBCameraException ("Open");

	// query device
	struct v4l2_capability devCap;
	if (xioctl(fd, VIDIOC_QUERYCAP, &devCap)==-1)
		throw USBCameraException ("QueryCap");
	struct v4l2_cropcap cropCap;
	memset (&cropCap, 0, sizeof(cropCap));
	cropCap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (xioctl (fd, VIDIOC_CROPCAP, &cropCap)==-1)
		throw USBCameraException ("QueryCropCap");

	// use all resolution
	this->width = cropCap.defrect.width;
	this->height = cropCap.defrect.height;

	// request format
	struct v4l2_format vidformat;
	memset (&vidformat, 0, sizeof(vidformat));
	vidformat.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	vidformat.fmt.pix.width = this->width;
	vidformat.fmt.pix.height = this->height;
	vidformat.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	vidformat.fmt.pix.field = V4L2_FIELD_NONE;
	if (xioctl (this->fd, VIDIOC_S_FMT, &vidformat)==-1)
		throw USBCameraException ("Unable to set format");

	// request mmap buffer
	struct v4l2_requestbuffers req;
	memset (&req, 0, sizeof(req));
	req.count = RequestBufferLength;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;
	xioctl (this->fd, VIDIOC_REQBUFS, &req);
	this->bufferCount = req.count;
	this->buffers = (CameraBuffer*)calloc (req.count, sizeof(CameraBuffer));

	// setting buffers
	size_t buf_max = 0;
	for (int i=0; i<this->bufferCount; i++) {
		v4l2_buffer buf;
		memset (&buf, 0, sizeof(buf));
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = i;
		xioctl (this->fd, VIDIOC_QUERYBUF, &buf);
		if (buf.length > buf_max)
			buf_max = buf.length;
		buffers[i].length = buf.length;
		buffers[i].start = (uint8_t*)
			mmap (NULL,
			buf.length,
			PROT_READ|PROT_WRITE,
			MAP_SHARED,
			this->fd,
			buf.m.offset);
	}
	this->head.start = new uint8_t[buf_max];
}


void USBCamera::start()
{
	int er;

	for (int i=0; i<this->bufferCount; i++) {
		struct v4l2_buffer buf;
		memset (&buf, 0, sizeof(buf));
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = i;
		er = xioctl (this->fd, VIDIOC_QBUF, &buf);
	}

	enum v4l2_buf_type buftype = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	er = xioctl (this->fd, VIDIOC_STREAMON, &buftype);
	return;
}


void USBCamera::stop()
{
	enum v4l2_buf_type t = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	xioctl (this->fd, VIDIOC_STREAMOFF, &t);
}


yuyvImage* USBCamera::capture ()
{
	// check if camera ready
	timeval timeout;
	timeout.tv_sec = 1;
	timeout.tv_usec = 0;
	fd_set fds;
	FD_ZERO (&fds);
	FD_SET (this->fd, &fds);
	select (this->fd+1, &fds, NULL, NULL, &timeout);

	// prepare buffer
	v4l2_buffer buf;
	memset (&buf, 0, sizeof(buf));
	buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf.memory = V4L2_MEMORY_MMAP;

	// copy buffer
	xioctl (this->fd, VIDIOC_DQBUF, &buf);
	memcpy (this->head.start, this->buffers[buf.index].start, buf.bytesused);
	this->head.length = buf.bytesused;
	xioctl (this->fd, VIDIOC_QBUF, &buf);

	yuyvImage *retval = new yuyvImage (this->width, this->height, this->head.start);
	return (retval);
}


inline int clamp (int min, int v, int max)
{
	return (v < min) ? min : (max < v) ? max : v;
}


rgbImage* USBCamera::yuyv2rgb (yuyvImage &yuyv)
{
	rgbImage *rgb  = new rgbImage (yuyv.getWidth(), yuyv.getHeight());

	/*for (int i=0; i<yuyv.getHeight(); i++) {
		for (int j=0; j<yuyv.getWidth(); j+=2) {

			int index = i*yuyv.getWidth() + j;
			yuyvPixel src = yuyv (i, j);
			rgbPixel &rgb1 = rgb->at (i, j),
				&rgb2 = rgb->at (i, j+1);

			int y0 = src.y0 << 8,
				u  = src.u - 128,
				y1 = src.y1 << 8,
				v  = src.v - 128;

			rgb1.r = clamp (0, (y0+359*v)>>8, 255);
			rgb1.g = clamp (0, (y0+88*v-183*u)>>8, 255);
			rgb1.b = clamp (0, (y0+454*u)>>8, 255);
			rgb2.r = clamp (0, (y1+359*v)>>8, 255);
			rgb2.g = clamp (0, (y1+88*v-183*u)>>8, 255);
			rgb2.b = clamp (0, (y1+454*u)>>8, 255);
		}
	}*/
	uint8_t *yuyvData = (uint8_t*)yuyv.getData();
	uint8_t *rgbData = (uint8_t*)rgb->getData();
	for (size_t i = 0; i < yuyv.getHeight(); i++) {
	for (size_t j = 0; j < yuyv.getWidth(); j += 2) {
		size_t index = i * yuyv.getWidth() + j;
		int y0 = yuyvData[index * 2 + 0] << 8;
		int u = yuyvData[index * 2 + 1] - 128;
		int y1 = yuyvData[index * 2 + 2] << 8;
		int v = yuyvData[index * 2 + 3] - 128;
		rgbData[index * 3 + 0] = clamp(0, (y0 + 359 * v) >> 8, 255);
		rgbData[index * 3 + 1] = clamp(0, (y0 + 88 * v - 183 * u) >> 8, 255);
		rgbData[index * 3 + 2] = clamp(0, (y0 + 454 * u) >> 8, 255);
		rgbData[index * 3 + 3] = clamp(0, (y1 + 359 * v) >> 8, 255);
		rgbData[index * 3 + 4] = clamp(0, (y1 + 88 * v - 183 * u) >> 8, 255);
		rgbData[index * 3 + 5] = clamp(0, (y1 + 454 * u) >> 8, 255);
		}
	}

	return (rgb);
}


USBCamera::~USBCamera ()
{
	this->stop ();
	for (int i=0; i<this->bufferCount; i++) {
		munmap (this->buffers[i].start, this->buffers[i].length);
	}

	free (this->buffers);
	delete (this->head.start);

	v4l2_close (this->fd);
}
