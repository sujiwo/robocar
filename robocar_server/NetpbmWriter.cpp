/*
 * NetpbmWriter.cpp
 *
 *  Created on: Jan 8, 2015
 *      Author: sujiwo
 */

#include "NetpbmWriter.h"


NetpbmWriter::NetpbmWriter(const char *targetFilename, int _width, int _height, const uint8_t *imageData) :
	width (_width),
	height (_height),
	outfd (targetFilename),
	dataptr (imageData)
{}


NetpbmWriter::~NetpbmWriter()
{
	outfd.close ();
}


bool NetpbmWriter::doWrite ()
{
	// Write header
	outfd << "P5\n"
			<< this->width << " " << this->height << "\n"
			<< "255"
			<< "\n";
	outfd.write ((char*)dataptr, width*height*sizeof(uint8_t));
}


bool NetpbmWriter::write (const char *targetFilename, int _width, int _height, const uint8_t *imageData)
{
	NetpbmWriter wrt (targetFilename, _width, _height, imageData);
	return wrt.doWrite();
}
