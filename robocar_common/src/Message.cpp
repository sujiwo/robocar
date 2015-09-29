/*
 * Message.cpp
 *
 *  Created on: Dec 5, 2014
 *      Author: sujiwo
 */

#include "Message.h"
#include <cstring>
#include <stdlib.h>
#include <endian.h>



namespace Robocar {

void Message::send (boost::asio::ip::tcp::socket &serverSocket)
{
	_messageBuffer *buffer = serialize ();
	boost::asio::write (
		serverSocket,
		boost::asio::buffer(
			buffer, getWireSize()
		)
	);
	delete[] buffer;
	return;
}


shared_ptr<Message> Message::create (uint8_t category, int length, uint8_t *source)
{
	shared_ptr<uint8_t> buffer (source);
	shared_ptr<Message> m (new Message (category, length, buffer));
	return m;
}


shared_ptr<Message> Message::create (uint8_t category, int length, shared_ptr<uint8_t> source)
{
	shared_ptr<Message> m (new Message (category, length, source));
	return m;
}


/*
 * This function serialize, and converts byte order into net byte order
 * AKA. big endian
 */
//shared_ptr<_messageBuffer> Message::serialize ()
_messageBuffer * Message::serialize ()
{
	_messageBuffer * msgBuffer = ((_messageBuffer*)(new uint8_t[getWireSize()]));
	msgBuffer->type = type;

	// Date handling
	msgBuffer->time_second = (uint64_t)timestamp.tv_sec;
	msgBuffer->time_microsecond = (uint64_t)timestamp.tv_usec;

	msgBuffer->size = htobe32(size);
	memcpy (&(msgBuffer->__msgStart), content.get(), size);
	return msgBuffer;
}

shared_ptr<Message> Message::receive (boost::asio::ip::tcp::socket &clientSocket)
{
	_messageBuffer header;
	boost::asio::mutable_buffers_1 headerReadBuf =
		boost::asio::buffer (
			&header,
			sizeof(header)-sizeof(header.__msgStart)
		);
	boost::asio::read (clientSocket, headerReadBuf);

	shared_ptr<Message> newmsg (new Message);
	newmsg->type = header.type;
	//newmsg->timestamp = be64toh(header.timestamp);
	// date/time handling
	//newmsg->timestamp = header.timestamp;
	newmsg->timestamp.tv_sec = header.time_second;
	newmsg->timestamp.tv_usec = header.time_microsecond;

	newmsg->size = be32toh(header.size);

	if (newmsg->size > MessageMaximumSize) {
		int tp = (int)newmsg->type;
		printf ("Message type %d is %d > %d\n", tp, newmsg->size, MessageMaximumSize);
		return shared_ptr<Message>();
	}

	//uint8_t *msgcontent = new uint8_t[newmsg->size];
	shared_ptr<uint8_t> msgcontent (new uint8_t[newmsg->size]);
	boost::asio::read (clientSocket, boost::asio::buffer((void*)msgcontent.get(), newmsg->size));
	newmsg->content = msgcontent;

	return newmsg;
}


boost::posix_time::ptime Message::getPtime ()
{
	boost::posix_time::ptime dt = boost::posix_time::from_time_t(timestamp.tv_sec);
	boost::posix_time::time_duration td = boost::posix_time::microseconds (timestamp.tv_usec);
	dt = dt + td;
	return dt;
}

} /* namespace Robocar */





