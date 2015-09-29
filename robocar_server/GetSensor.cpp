/*
 * GetSensor.cpp
 *
 *  Created on: 2014/05/30
 *      Author: pdsl
 */

#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "RcControl.h"

using namespace zmp::zrc;


//シリアルポート初期化
void init_system(){

	system("ipm_serial S 4 0");
	sleep(1);
	system("ipm_serial S 4 1");
}

int main(){

	init_system();
	RcControl _RcControl;
	DRIVE_VALUE drive;
	SENSOR_VALUE sensor;
	OBSTACLE_VALUE obstacle;
	POWER_VALUE power;


	_RcControl.init(); //RcControl初期化
	_RcControl.Start();
	_RcControl.SetReportFlagReq(7); //通知情報フラッグ設定 7=?
	_RcControl.SetMotorEnableReq(0); //モータオンオフ設定 OFF=0;ON=1
	_RcControl.SetDriveSpeed(0); //速度設定

	memset(&power, 0, sizeof(POWER_VALUE)); //POWER_VALUE初期化

		sleep(2);

		//sensor情報取得
		_RcControl.GetSensorInfoReq(&sensor);
		printf("before gyro=%3.2f\n", sensor.gyro);

		//パワー情報取得
		_RcControl.GetPowerInfoReq(&power);
		printf("before current=%3.2f\n", power.motor_current);

	/*	//ジャイロオフセット
		_RcControl.SetGyroOffset(sensor.gyro);

		//モーターのオフセット
		_RcControl.SetMotorCurrentOffset(power.motor_current);
		_RcControl.SetMotorEnableReq(1);

		while(1){
			usleep(10000);
			memset(&drive, 0, sizeof(DRIVE_VALUE));
			_RcControl.GetServoInfoReq(1, PRESENT_POSITION_L, PRESENT_VOLTS_H - PRESENT_POSITION_L, &drive);
			printf("angle=%fdeg, current=%dmA, temp=%d℃, volts=%dmV\n",
					drive.present_position,
					drive.present_current,
					drive.present_temperature,
					drive.present_volts);

			// Get sensor information
			memset(&sensor, 0, sizeof(SENSOR_VALUE));
			_RcControl.GetSensorInfoReq(&sensor);
			printf("G=%3.2fdeg/s, ax=%3.2fg, ay=%3.2fg, az=%3.2fg, e0=%3.2fcycle/s, e1=%3.0fmm/s, e2=%3.0fmm/s, e3=%3.0fmm/s, e4=%3.0fmm/s\n",
					sensor.gyro,
					sensor.acc_x,
					sensor.acc_y,
					sensor.acc_z,
					sensor.enc_0,
					sensor.enc_1,
					sensor.enc_2,
					sensor.enc_3,
					sensor.enc_4);
*/
			// Get obstacle information
	/*		memset(&obstacle, 0, sizeof(OBSTACLE_VALUE));
			_RcControl.GetObstacleSensorInfoReq(&obstacle);*/
	/*		printf("0=%dmm, 1=%dmm, 2=%dmm, 3=%dmm, 4=%dmm, 5=%dmm, 6=%dmm, 7=%dmm\n",
					obstacle.obstacle[0], obstacle.obstacle[1],
					obstacle.obstacle[2], obstacle.obstacle[3],
					obstacle.obstacle[4], obstacle.obstacle[5],
					obstacle.obstacle[6], obstacle.obstacle[7]);*/
	/*		for(int i=0; i < 8; i++){
			    if(obstacle.obstacle[i] == 0)
				printf("%d=near ", i);
			    else if(obstacle.obstacle[i] == 0x1000)
				printf("%d=long ", i);
			    else
				printf("%d=%dmm ", i, obstacle.obstacle[i]);
			}
			printf("\n");
*/
			// Get power information
/*			memset(&power, 0, sizeof(POWER_VALUE));
			_RcControl.GetPowerInfoReq(&power);
			printf("current=%2.2fmA, battery=%2.2fV\n",
				power.motor_current, power.battery_level);
		}
*/
		printf("終了前\n");
		_RcControl.Stop();
		_RcControl.Close();
		printf("終了\n");

	   return 0;

}
