/*
 * Message.h
 *
 *  Created on: Dec 5, 2014
 *      Author: sujiwo
 */

#ifndef MESSAGE_H_
#define MESSAGE_H_

#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>


#define MessageMaximumSize 2097152

using boost::shared_ptr;

/*
 * Wire format of the message
 * 1 byte : type
 * 4 byte : timestamp
 * 4 byte : size
 * rest : message
 */


namespace Robocar {

#pragma pack (push)
#pragma pack (1)
struct _messageBuffer {
	uint8_t type;
	uint64_t time_second;
	uint64_t time_microsecond;
	uint32_t size;
	uint8_t __msgStart;
};
#pragma pack (pop)


class Message {
public:

	Message () :
		type(0),
		size(0)
	{ gettimeofday (&timestamp, NULL); }

	Message(uint8_t category, int length, shared_ptr<uint8_t> source) :
		type(category),
		size(length),
		content(source)
	{ gettimeofday (&timestamp, NULL); }

	static shared_ptr<Message> create (uint8_t category, int length, uint8_t *source);
	static shared_ptr<Message> create (uint8_t category, int length, shared_ptr<uint8_t> source);

	uint32_t getWireSize ()
	{
		/*return sizeof(type) +
			// size of time field
			2*sizeof(uint64_t) +
			sizeof(size) + size;*/
		return sizeof (_messageBuffer)
			- sizeof(uint8_t)
			+ size;
	}

	void send (boost::asio::ip::tcp::socket &serverSocket);

	static shared_ptr<Message> receive (boost::asio::ip::tcp::socket &clientSocket);

	uint8_t getType() { return this->type; }
	timeval getTimestamp() { return timestamp; }
	uint32_t getSize() { return size; }
	shared_ptr<uint8_t> getPtr () { return content; }
	char *getContent() { return (char*)content.get(); }

	boost::posix_time::ptime getPtime ();

protected:
	uint8_t type;
	struct timeval timestamp;
	uint32_t size;
	shared_ptr<uint8_t> content;
	//shared_ptr<_messageBuffer> serialize ();
	_messageBuffer * serialize ();
	// add time element here

};


} /* namespace Robocar */

#endif /* MESSAGE_H_ */
