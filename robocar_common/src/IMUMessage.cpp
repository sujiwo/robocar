/*
 * IMUMessage.cpp
 *
 *  Created on: Jan 13, 2015
 *      Author: sujiwo
 */

#include "IMUMessage.h"
#include "MessageRegisters.h"
#include <string.h>


namespace Robocar {

shared_ptr<IMUMessage> IMUMessage::deserialize (Message &msg)
{
	if (msg.getType() != IMUMessageCategory)
		throw std::exception ("Wrong message");
	shared_ptr<IMUMessage> imudata = IMUMessage::create();
	memcpy (imudata->getPtr().get(), msg.getContent(), msg.getSize());
	return imudata;
}

} /* namespace Robocar */
