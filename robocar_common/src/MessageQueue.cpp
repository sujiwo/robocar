/*
 * MessageQueue.cpp
 *
 *  Created on: Dec 8, 2014
 *      Author: sujiwo
 */

#include "MessageQueue.h"


using boost::interprocess::scoped_lock;
using boost::interprocess::interprocess_mutex;

namespace Robocar {

MessageQueue::~MessageQueue()
{
	while (!pipeline.empty()) {
		shared_ptr<Message> m = pipeline.front();
		pipeline.pop();
	}
}

void MessageQueue::push(shared_ptr<Message> src)
{
	scoped_lock<interprocess_mutex> lock(_mutex);
	pipeline.push (src);
	lock.unlock();
	_condvar.notify_one();
}

bool MessageQueue::empty()
{
	scoped_lock<interprocess_mutex> lock(_mutex);
	return pipeline.empty();
}

shared_ptr<Message> MessageQueue::pop ()
{
	scoped_lock<interprocess_mutex> lock(_mutex);
	while (pipeline.empty()) {
		_condvar.wait(lock);
	}

	shared_ptr<Message> front = pipeline.front();
	pipeline.pop();
	return front;
}

} /* namespace Robocar */
