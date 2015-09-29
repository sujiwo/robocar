/*
 * Odometer.cpp
 *
 *  Created on: Jan 15, 2015
 *      Author: sujiwo
 */

#include "Odometer.h"
#include "tf/tf.h"
#include "tf/transform_datatypes.h"
#include <math.h>


using boost::posix_time::microsec_clock;
using boost::posix_time::second_clock;


namespace Robocar {

Vector3 convertG2MS (Vector3 &accel)
{
	return standard_g * accel;
}


Odometer::Odometer (Vector3 origin) :
	lastUpdate (microsec_clock::universal_time()),
	yaw (0.0)
{
	position = origin;
	velocity = Vector3 (0.0, 0.0, 0.0);
}


void Odometer::updateAcceleration (Vector3 &acc)
{
	ptime tm = microsec_clock::universal_time();
	return updateAcceleration (acc, tm);
}


double Odometer::updateTime (ptime tm)
{
	double sampleTime = (tm - lastUpdate).total_nanoseconds() * 1e-9;
	lastUpdate = tm;
	return sampleTime;
}


void Odometer::updateAcceleration (Vector3 &in_acc, ptime tm)
{
	double sampleTime = this->updateTime(tm);

	Vector3 acc = in_acc;
#ifdef START_G
	acc.z() -= START_G;
#endif
	velocity = velocity + sampleTime*convertG2MS(acc);
	position = position + sampleTime*velocity;
}


void Odometer::updateAttitude (float gyroSpeed, ptime tm)
{
	double sampleTime = this->updateTime (tm);
	double deltaYaw = sampleTime * gyroSpeed;
	yaw += deltaYaw;
	// normalize yaw
	int n = floor (yaw / (2*M_PI));
	yaw = yaw - 2*M_PI*n;
}


Quat Odometer::getAttitude ()
{
	tf::Quaternion q;
	Quat qr;
	q.setRPY(0.0, 0.0, yaw);

	qr.w = q.w();
	qr.x = q.x();
	qr.y = q.y();
	qr.z = q.z();
	return qr;
}


} /* namespace Robocar */
