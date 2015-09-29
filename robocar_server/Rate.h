/*
 * Rate.h
 *
 *  Created on: Jan 7, 2015
 *      Author: sujiwo
 */

#ifndef ROBOCAR_SERVER_RATE_H_
#define ROBOCAR_SERVER_RATE_H_


class Rate
{
public:
	Rate (double frequency);
	bool sleep ();
	void reset ();
};



#endif /* ROBOCAR_SERVER_RATE_H_ */
