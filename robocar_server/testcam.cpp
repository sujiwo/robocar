/*
 * testcam.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: jiwo
 */


#include "usb_cam.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <jpeglib.h>
#include <sys/types.h>


using std::cout;
using std::endl;


void saveJpeg (const char *filename, uint8_t *rgb, int width, int height)
{
	FILE *jpgfile = fopen (filename, "w");
	JSAMPARRAY image;
	image = (JSAMPARRAY)calloc (height, sizeof(JSAMPROW));

	for (size_t i=0; i<height; i++) {
		image[i] = (JSAMPROW)calloc (width*3, sizeof(JSAMPLE));

		for (size_t j=0; j<width; j++) {
			image[i][j*3 + 0] = rgb[(i*width + j)*3 + 0] ;
			image[i][j*3 + 1] = rgb[(i*width + j)*3 + 1];
			image[i][j*3 + 2] = rgb[(i*width + j)*3 + 2];
		}
	}

	struct jpeg_compress_struct compress;
	struct jpeg_error_mgr error;
	compress.err = jpeg_std_error (&error);
	jpeg_create_compress (&compress);
	jpeg_stdio_dest(&compress, jpgfile);

	compress.image_width = width;
	compress.image_height = height;
	compress.input_components = 3;
	compress.in_color_space = JCS_RGB;
	jpeg_set_defaults(&compress);
	jpeg_set_quality(&compress, 100, TRUE);
	jpeg_start_compress(&compress, TRUE);
	jpeg_write_scanlines(&compress, image, height);
	jpeg_finish_compress(&compress);
	jpeg_destroy_compress(&compress);

	for (size_t i=0; i<height; i++) {
		free (image[i]);
	}
	free (image);

	fclose (jpgfile);
}


int main (int argc, char *argv[])
{
	usb_cam_camera_image_t *camera = usb_cam_camera_start("/dev/video0", 640, 480, 15);
	usb_cam_camera_grab_image (camera);
	saveJpeg("testcam.jpg", (uint8_t*)camera->image, camera->width, camera->height);

	return 0;
}
