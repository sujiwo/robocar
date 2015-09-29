/*
 * IMUMessage.h
 *
 *  Created on: Jan 13, 2015
 *      Author: sujiwo
 */

#ifndef ROBOCAR_COMMON_SRC_IMUMESSAGE_H_
#define ROBOCAR_COMMON_SRC_IMUMESSAGE_H_


#include "Message.h"


namespace Robocar {

enum IMU_FIELD_TYPE {
	SENSOR_GYRO = 0,
	SENSOR_ACCELERATION_X = 1,
	SENSOR_ACCELERATION_Y = 2,
	SENSOR_ACCELERATION_Z = 3,
	SENSOR_ENCODER_MOTOR = 4,
	SENSOR_ENCODER_WHEEL_1 = 5,
	SENSOR_ENCODER_WHEEL_2 = 6,
	SENSOR_ENCODER_WHEEL_3 = 7,
	SENSOR_ENCODER_WHEEL_4 = 8,
	POWER_CURRENT = 9,
	POWER_BATTERYLEVEL = 10,
};
// value of this variable must reflect number of enum
// members above
const int ImuArraySize = 11;


/*class IMUMessage: public Message
{
public:
	inline IMUMessage (shared_ptr<float> _src) :
		imuDataArray (_src)
	{
		content = (shared_ptr<uint8_t>)imuDataArray;
		size = ImuArraySize * sizeof(float);
	}

	inline float &operator[] (int p)
	{ return imuDataArray[p]; }

	inline static shared_ptr<IMUMessage> create (float *src)
	{
		shared_ptr<float> dta (src);
		return shared_ptr<IMUMessage> (dta);
	}

	inline static shared_ptr<IMUMessage> create ()
	{
		shared_ptr<float> dta (new float[ImuArraySize]);
		return shared_ptr<IMUMessage> (dta);
	}

	static shared_ptr<IMUMessage> deserialize (Message &msg);

protected:
	shared_ptr<float> imuDataArray;
};*/


} /* namespace Robocar */

#endif /* ROBOCAR_COMMON_SRC_IMUMESSAGE_H_ */
