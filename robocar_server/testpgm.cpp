/*
 * testpgm.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: sujiwo
 */

#include "NetpbmWriter.h"
#include "stdint.h"
#include <string.h>


uint8_t *grayimage (int width, int height)
{
	if (width != height)
		return NULL;

	size_t imgbytes = width*height*sizeof(uint8_t);
	uint8_t *imgret = new uint8_t [imgbytes];
	memset (imgret, 0, imgbytes);
	int i, j;
	for (i=0; i<height; i++) {
		for (j=0; j<width; j++) {
			if (i==j || j==width-i)
				imgret [i*width+j] = 255;
		}
	}

	return imgret;
}


int main (int argc, char *argv[])
{
	uint8_t *gray = grayimage (100, 100);
	NetpbmWriter::write("/tmp/test.pgm", 100, 100, gray);
	delete[] gray;
}
