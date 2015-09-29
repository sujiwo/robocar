/*
 * Odometer.h
 *
 *  Created on: Jan 15, 2015
 *      Author: sujiwo
 */

#ifndef ROBOCAR_CLIENT_SRC_ODOMETER_H_
#define ROBOCAR_CLIENT_SRC_ODOMETER_H_

#include "Eigen/Core"
#include "Eigen/Geometry"
#include "boost/date_time/posix_time/posix_time.hpp"
#include "ros/ros.h"
#include "geometry_msgs/Quaternion.h"


using Eigen::Vector3f;
using Eigen::Vector3d;
using Eigen::Quaterniond;
using boost::posix_time::ptime;

typedef Vector3d Vector3;
typedef geometry_msgs::Quaternion Quat;


#define START_G 1.0
const double standard_g = 9.8065;


namespace Robocar {

class Odometer {
public:
	Odometer ()
	{ Odometer (Vector3(0, 0, 0)); }

	Odometer (Vector3 origin);

	void updateAcceleration (Vector3 &acc);
	void updateAcceleration (Vector3 &acc, ptime tm);

	void updateAttitude (float gyroSpeed, ptime tm);

	// In meter
	Vector3& getPosition () { return position; }
	// In meter/second
	Vector3& getVelocity () { return velocity; }

	Quat getAttitude ();

	ros::Time getRosTime ()
	{
		return ros::Time::fromBoost(lastUpdate);
	}

	virtual ~Odometer() {}

private:
	Vector3 position;
	Vector3 velocity;
	double yaw;
	ptime lastUpdate;

	double updateTime (ptime tm);
};

} /* namespace Robocar */

#endif /* ROBOCAR_CLIENT_SRC_ODOMETER_H_ */
