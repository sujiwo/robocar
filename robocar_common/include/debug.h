/*
 * debug.h
 *
 *  Created on: Dec 10, 2014
 *      Author: jiwo
 */

#ifndef DEBUG_H_
#define DEBUG_H_

#include <cstdarg>
#include <iostream>
#include <cstdio>


namespace Robocar
{

inline void debug (const char *strfmt, ...)
{
#ifdef DEBUG
	va_list args;
	va_start (args, strfmt);
	vprintf (strfmt, args);
	va_end (args);
	fprintf (stdout, "\n");
#endif
}

}

#endif /* DEBUG_H_ */
