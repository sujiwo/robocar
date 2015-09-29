/*
 * HokuyoMessage.h
 *
 *  Created on: Dec 10, 2014
 *      Author: jiwo
 */

#ifndef HOKUYOMESSAGE_H_
#define HOKUYOMESSAGE_H_

#include "hokuyo.h"
#include "Message.h"
#include "MessageQueue.h"
#include <vector>
#include <boost/thread.hpp>
#include <boost/interprocess/sync/interprocess_semaphore.hpp>


using boost::thread;
typedef boost::interprocess::interprocess_semaphore semaphore;




template<typename T>
void
createVectorFromArray (T* array, int sz, std::vector<T> &target)
{
	target = std::vector<T> (array, array+sz);
}


namespace Robocar {

#pragma pack (push)
#pragma pack (1)
struct _hokuyoMessageBuffer {
	float min_angle;
	float max_angle;
	float angular_increment;
	float scan_time;
	float min_range;
	float max_range;
	// num of points
	uint32_t num_ranges;
	uint8_t _ranges;
};
#pragma pack (pop)



class HokuyoMessage : public Message
{
public:
	HokuyoMessage (hokuyo::LaserScan &scanresult) ;
	// XXX: Need to formulate better output for this function
	static shared_ptr<hokuyo::LaserScan> deserialize (Message &msg);
};


class HokuyoSensorDriver
{

public:
	HokuyoSensorDriver (MessageQueue *_msgq, const char *_devfilename) ;

	~HokuyoSensorDriver ();

	void init () ;

	static void threadEntryPoint (HokuyoSensorDriver *drv) ;

	void work ();

	static shared_ptr<uint8_t> serializeMessage (hokuyo::LaserScan &scanResult, uint32_t &bufferSize);

	void start ();

	void stop () ;

private:
	MessageQueue *srvQueue;
	thread *drvThread;
	volatile bool doStop, doQuit;
	semaphore *startSignal;
	const char *devfilename;
	hokuyo::Laser *laser;
	hokuyo::LaserConfig laserconf;
};


}


#endif /* HOKUYOMESSAGE_H_ */
