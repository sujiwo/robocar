#include <Eigen/Core>
#include <iostream>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <unistd.h>


using Eigen::Vector3f;
using std::cout;
using std::endl;
using boost::posix_time::ptime;


int main (int argc, char *argv[])
{
	Vector3f v1 (0.1, 1e-3, 0), v2 (-3.1, -1.76e-6, -1), v3;
	v3 = v1 + v2;

	ptime p_local_1 = boost::posix_time::microsec_clock::local_time();
	usleep (1.237776231e6);
	ptime p_local_2 = boost::posix_time::microsec_clock::local_time();
	boost::posix_time::time_duration px = p_local_2 - p_local_1;
	long ns = px.total_nanoseconds();
	float sec = ns * 1e-9;

	cout << "Nanosecond: " << ns << endl;
	cout << "Second: " << sec << endl;
}
