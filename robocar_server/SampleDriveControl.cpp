/**
 * @file
 *
 * @~english
 * @brief	DriveControl Sample implementation.
 *
 * @author	Koji Sekiguchi
 *
 * @~japanese
 * @brief	DriveControlサンプルの実装.
 *
 * @author	関口 浩司
 *
 * @~
 * @date	2009-05-12
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#include <iostream>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "RcControl.h"

using namespace zmp::zrc;

int main(){
  
    system("ipm_serial S 4 0");
    sleep(1);
    system("ipm_serial S 4 1"); 
    sleep(1);    
    
    char buf[20];
    float angle = 0;
    int speed = 0;
    int set_v = 0;
    int set_t = 0;
    bool sign = false;
    float set_a = 0;
    bool period = false;
    bool loop = true;
    RcControl  _RcControl;
    _RcControl.init();
    _RcControl.Start();
 
    _RcControl.SetReportFlagReq(7);
    _RcControl.SetServoEnable(1);
    _RcControl.SetMotorEnableReq(1);
    _RcControl.SetDriveSpeed(0);
    _RcControl.SetSteerAngle(0);


    while(loop){
        fgets(buf, 20, stdin);
	// Get sensor information
/*	SENSOR_VALUE sensor;
	_RcControl.GetSensorInfoReq(&sensor);
	printf("e0=%3.2fcycle/s, e1=%3.0fmm/s, e2=%3.0fmm/s, e3=%3.0fmm/s, e4=%3.0fmm/s\n",
		sensor.enc_0,
		sensor.enc_1,
		sensor.enc_2,
		sensor.enc_3,
		sensor.enc_4);*/

        switch(buf[0]){
        // steering right
        case 'r':
       	    if(angle < 30)
       	        angle += 3;
       	    printf("send steer angle = %2.1f\n", angle);
       	    _RcControl.SetSteerAngle(angle);
       	    break;
        // steering left
        case 'l':
       	    if(angle > -30)
       	        angle -= 3;
       	    printf("send steer angle = %2.1f\n", angle);
       	    _RcControl.SetSteerAngle(angle);
       	    break;
      	// drive speed forward
        case 'f':
       	    if(speed < 0)
       	        speed = 0;
       	    if(speed < 400)
       	        speed += 10;
       	    printf("send drive speed = %d\n", speed);
            _RcControl.SetDriveSpeed(speed);
       	    break;
      	// drive speed backward
        case 'b':
       	    if(speed > 0)
       	        speed = 0;
       	    if(speed > -400)
       	        speed -= 10;
       	    printf("send drive speed = %d\n", speed);
       	    _RcControl.SetDriveSpeed(speed);
       	    break;
      	// drive stop
        case 's':
            printf("send steer angle = 0.0\n");
            printf("send drive speed = 0\n");
       	    _RcControl.SetDriveSpeed(0);
       	    _RcControl.SetSteerAngle(0);
       	    speed = 0;
       	    break;
      	// parking
        case 'p':
            printf("send drive motor enable = brake\n");
       	    _RcControl.SetMotorEnableReq(2);
       	break;
      	// motor off
        case 'o':
       	    printf("send drive motor enable = off\n");
       	    _RcControl.SetMotorEnableReq(0);
       	    break;
      	// motor on
        case 'g':
            printf("send drive motor enable = on\n");
       	    _RcControl.SetMotorEnableReq(1);
       	    break;
      	// drive velocity set
        case 'v':
       	    set_v = 0;
       	    sign = false;
       	    for(int k=1; k<6; k++){
       	        if(buf[k] == 0x2d) 		// '-'
                    sign = true;
                else if((buf[k] >= 0x30) && (buf[k] <= 0x39)){
                    if(set_v == 0)
                        set_v = buf[k] - 0x30;
                    else
                        set_v = set_v*10 + (buf[k] - 0x30);
                }
       	        else
                    break;
            }
       	    if(sign == true)
       	        set_v *= -1;
       	    printf("send drive speed = %d\n", set_v);
       	    _RcControl.SetDriveSpeed(set_v);
       	    for(int j=0; j<6; j++){
       	        buf[j]=0;
	    }
       	    break;
      	// steer angle set
        case 'a':
       	    set_a = 0;
       	    period = false;
       	    sign = false;
       	    for(int l=1; l<7; l++){
       	        if(buf[l] == 0x2d) 		// '-'
       	            sign = true;
       	        else if(buf[l] == 0x2e)	// '.'
       	            period = true;
       	        else if((buf[l] >= 0x30) && (buf[l] <= 0x39)){
       		    if(set_a == 0)
       	                set_a = buf[l] - 0x30;
       	            else{
       	                if(period == false)
       	                    set_a = set_a*10 +(buf[l] - 0x30);
       	                else
       	                    set_a = set_a + ((float)(buf[l] - 0x30))/10;
                    }
                }
       	        else
                break;
            }
       	    if(sign == true)
       	        set_a *= -1;

       	    printf("send steer angle = %f\n", set_a);
       	    _RcControl.SetSteerAngle(set_a);
       	    for(int m=0; m<6; m++){
       	         buf[m]=0;
	    }
       	    break;
        case 't':
       	    set_t = 0;
       	    for(int k=1; k<6; k++){
       	        if((buf[k] >= 0x30) && (buf[k] <= 0x39)){
       	            if(set_t == 0)
       	                set_t = buf[k] - 0x30;
       	            else
       	                set_t = set_t*10 + (buf[k] - 0x30);
	        }
       	        else
       	            break;
	    }
	    printf("send drive motor torque = %d\n", set_t);
       	    _RcControl.SetMotorTorqueReq(set_t,0,0,0);
       	    for(int j=0; j<6; j++){
                buf[j]=0;
	    }
       	    break;
      	// end
        case 'e':
	    printf("send drive speed = 0\n");
            printf("send steer angle = 0.0\n");
	    printf("send steer servo enable = off\n");
	    printf("send drive motor enable = off\n");
       	    _RcControl.SetDriveSpeed(0);
       	    _RcControl.SetSteerAngle(0);
       	    _RcControl.SetServoEnable(0);
	    _RcControl.SetMotorEnableReq(0);
       	    loop = false;
       	    buf[0] = 0;
       	    break;
        default: break;
        }
    }
    _RcControl.Stop();
    _RcControl.Close();
    printf("loop end\n");
    return 0;
}
