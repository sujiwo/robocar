/*
 * MessageQueue.h
 *
 *  Created on: Dec 8, 2014
 *      Author: sujiwo
 */

#ifndef MESSAGEQUEUE_H_
#define MESSAGEQUEUE_H_


#include <queue>
#include <boost/interprocess/sync/interprocess_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <boost/interprocess/sync/interprocess_condition.hpp>
#include "Message.h"

using std::queue;


namespace Robocar {

class MessageQueue
{
public:
	MessageQueue() {}

	// Clearing the message queue will affect that
	// all messages will be destroyed
	~MessageQueue();

	void push (shared_ptr<Message>);
	bool empty ();
	shared_ptr<Message> pop ();

private:
	queue < shared_ptr<Message> > pipeline;
	boost::interprocess::interprocess_mutex _mutex;
	boost::interprocess::interprocess_condition _condvar;
};

} /* namespace Robocar */

#endif /* MESSAGEQUEUE_H_ */
