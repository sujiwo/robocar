/*
 * NetpbmWriter.h
 *
 *  Created on: Jan 8, 2015
 *      Author: sujiwo
 */

#ifndef ROBOCAR_SERVER_NETPBMWRITER_H_
#define ROBOCAR_SERVER_NETPBMWRITER_H_

#include <stdint.h>
#include <fstream>


class NetpbmWriter
{
public:
	NetpbmWriter(const char *targetFilename, int width, int height, const uint8_t *imageData);
	static bool write (const char *targetFilename, int width, int height, const uint8_t *imageData);
	virtual ~NetpbmWriter();

private:
	bool doWrite ();
	int width, height;
	std::ofstream outfd;
	const uint8_t *dataptr;
};

#endif /* ROBOCAR_SERVER_NETPBMWRITER_H_ */
