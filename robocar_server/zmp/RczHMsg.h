#ifndef __RCZ_HMSG_H__
#define __RCZ_HMSG_H__

#include "types.h"



#define IMAGE_BLOCK_SIZE_MAX	(1024)


enum RCZHMSG_ID {
	RCZHMSG_ID_LOAD_PROGRAM = 1,
	RCZHMSG_ID_SET_IMAGE_REPORT_FLAG, 
	RCZHMSG_ID_SET_RESULT_REPORT_FLAG, 
	RCZHMSG_ID_SET_IPM_STEREO_PARAM, 
	RCZHMSG_ID_UPDATE_DATAFILE, 
	RCZHMSG_ID_SET_INT_INTERVAL, 

	RCZHMSG_ID_SET_TORQUE_ENABLE, 
	RCZHMSG_ID_SET_DRIVE_SPEED, 
	RCZHMSG_ID_SET_STEER_ANGLE, 
	RCZHMSG_ID_SET_CONTROL_MODE, 
	RCZHMSG_ID_SET_ANGLE_ZERO_OFFSET,
	RCZHMSG_ID_SET_LANE_KEEPING_PARAM, 

	RCZHMSG_ID_SET_SERVO_ONOFF,
    RCZHMSG_ID_SET_MOTOR_ONOFF,
    RCZHMSG_ID_SET_CAMBER_ONOFF,
    RCZHMSG_ID_SET_CAMBER_ANGLE,
    RCZHMSG_ID_GET_SENSOR_INFO,
    RCZHMSG_ID_GET_SENSOR_INFO_RES,
    RCZHMSG_ID_GET_OBSTACLE_INFO,
    RCZHMSG_ID_GET_OBSTACLE_INFO_RES,
    RCZHMSG_ID_GET_POWER_INFO,
    RCZHMSG_ID_GET_POWER_INFO_RES,
    RCZHMSG_ID_GET_LRS_INFO,
    RCZHMSG_ID_GET_LRS_INFO_RES,
    RCZHMSG_ID_SET_CURRENT_OFFSET,
    RCZHMSG_ID_SET_GYRO_OFFSET,
    RCZHMSG_ID_GET_CAMBER_INFO_RES,
    RCZHMSG_ID_GET_SERVO_INFO,
    RCZHMSG_ID_GET_SERVO_INFO_RES,
	RCZHMSG_ID_SET_STEER_OFFSET,
	RCZHMSG_ID_SET_CAMBER_OFFSET,

	RCZHMSG_ID_BEGIN_MOTION, 
	RCZHMSG_ID_SET_OBSTACLE_AVOIDANCE_PARAM, 

	RCZHMSG_ID_SET_DRIVE_TORQUE,
	RCZHMSG_ID_SET_DRIVE_MODE,
	RCZHMSG_ID_SET_COMMUNICATION_CONFIG,
    RCZHMSG_ID_SET_CONTROL_CONFIG,
	RCZHMSG_ID_START_VIDEO_LOG,
    RCZHMSG_ID_STOP_VIDEO_LOG,
	RCZHMSG_ID_START_SENSOR_LOG,
	RCZHMSG_ID_STOP_SENSOR_LOG,
	
	
    RCZHMSG_ID_TEST = 128,
    RCZHMSG_ID_IMAGE,
    RCZHMSG_ID_LANE_RESULT,
    RCZHMSG_ID_STEREO_RESULT_HIST,
    RCZHMSG_ID_STEREO_RESULT_HOUGH,
    RCZHMSG_ID_STEREO_RESULT_LABELING,
    RCZHMSG_ID_TEXT_MESSAGE,

	RCZHMSG_ID_IMAGE_JPEG,
	
	RCZHMSG_ID_DISPARITY_AVERAGE, 

    RCZHMSG_ID_RC_COMMAND_BEG = RCZHMSG_ID_SET_TORQUE_ENABLE,

};

enum COMM_ENCODE {
    ENCODE_YUV = 1,
    ENCODE_GRAY = 2,
    ENCODE_JPEG =3,
};

enum COMM_RATE {
    RATE_15 = 1,
    RATE_30 = 2,
};

enum COMM_RESOLUTION {
    RESOLT_QVGA = 1,
    RESOLT_VGA = 2,
};

#pragma pack(push, 1)

struct RczHMsg {
	uchar	header[2];
	ulong	length;
	uchar	msg_id;
};


// RCZHMSG_ID_LOAD_PROGRAM
struct RczHMsgLoadProgram : public RczHMsg
{
	uchar	program_id;
};

// RCZHMSG_ID_SET_IMAGE_REPORT_FLAG
struct RczHMsgSetImageReportFlag : public RczHMsg
{
	uchar	image_id;
};

// RCZHMSG_ID_SET_RESULT_REPORT_FLAG
struct RczHMsgSetResultReportFlag : public RczHMsg
{
	uchar	result_flag;
};

// RCZHMSG_ID_SET_IPM_STEREO_PARAM
struct RczHMsgSetIpmStereoParam : public RczHMsg
{
	uchar	param_id;
	ushort	value;
};

// RCZHMSG_ID_SET_INT_INTERVAL
struct RczHMsgSetIntInterval : public RczHMsg
{
	uchar	intreq_interval;
	uchar	imageout_interval;
};

// RCZHMSG_ID_UPDATE_DATAFILE
struct RczHMsgUpdateDatafile : public RczHMsg
{
	uchar	file_id;
	ushort	location_path[32];
};





// RCZHMSG_ID_SET_TORQUE_ENABLE
struct RczHMsgSetTorqueEnable : public RczHMsg
{
	int		enable;
};

// RCZHMSG_ID_SET_DRIVE_SPEED
struct RczHMsgSetDriveSpeed : public RczHMsg
{
	int		speed;
};

// RCZHMSG_ID_SET_STEER_ANGLE
struct RczHMsgSetSteerAngle : public RczHMsg
{
	float	angle;
};

// RCZHMSG_ID_SET_CONTROL_MODE
struct RczHMsgSetControlMode : public RczHMsg
{
	// 0:zero
	// 1:manual
	// 2:lane-keeping
	uchar	mode;
};

// RCZHMSG_ID_SET_ANGLE_ZERO_OFFSET
struct RczHMsgSetAngleZeroOffset : public RczHMsg
{
	float	offset;
};

// RCZHMSG_ID_SET_LANE_KEEPING_PARAM
struct RczHMsgSetLaneKeepingParam : public RczHMsg
{
	int		index_beg;
	int		index_end;
	int		valid_count_th;
	float	valid_value_th;
	float	pos_target;
	float	a_target;
	float	angle_min;
	float	angle_max;
	float	k_pos;
	float	k_a;
	float	error_angle;
	float	angular_step;
};

// RCZHMSG_ID_BEGIN_MOTION
struct RczHMsgBeginMotion : public RczHMsg
{
	int		motion_id;
};

// RCZHMSG_ID_SET_OBSTACLE_AVOIDANCE_PARAM
struct RczHMsgSetObstacleAvoidanceParam : public RczHMsg
{
	float param[10];
};


// RCZHMSG_ID_TEST
struct RczHMsgTest : public RczHMsg
{
	uchar	data[10];
};

// RCZHMSG_ID_IMAGE
//#define IMAGE_BLOCK_SIZE_MAX	(1 * 1024)
struct RczHMsgImage : public RczHMsg
{
	uchar	image_id;
	uchar	ch;
	ushort  width;
	ushort  height;
	
	ushort	total_index;
	ushort	index;
	ushort	block_size;

	uchar   data[1];
};

// RCZHMSG_ID_LANE_RESULT
struct RczHMsgLaneResult : public RczHMsg
{
	short	xpos_l[8];
	short	xpos_r[8];
	short	ypos_l[8];
	short	ypos_r[8];
};

// RCZHMSG_ID_STEREO_RESULT_HIST
struct RczHMsgStereoResultHist : public RczHMsg
{
	uchar	value[213 * 20];
	uchar	index[213 * 20];
};

// RCZHMSG_ID_STEREO_RESULT_HOUGH
struct RczHMsgStereoResultHough : public RczHMsg
{
	ushort npoint;
	ushort point_x0[512];
	ushort point_x1[512];
	uchar  point_y0[512];
	uchar  point_y1[512];
};

// RCZHMSG_ID_STEREO_RESULT_LABELING
struct RczHMsgStereoResultLabeling : public RczHMsg
{
	ushort npoint;
	ushort point_x0[512];
	ushort point_x1[512];
	uchar  point_y0[512];
	uchar  point_y1[512];
};

// RCZHMSG_ID_TEXT_MESSAGE
struct RczHMsgTextMessage : public RczHMsg
{
	char	message_text[256];
};

#define LSR_RESULT_MAX_DATA_LENGTH 1000

struct LRSResult {
	unsigned long magic;
	long timestamp;
	int data_length;
	double	angle[LSR_RESULT_MAX_DATA_LENGTH];
	long	data[LSR_RESULT_MAX_DATA_LENGTH];
};

// RCZHMSG_ID_SET_CAMBER_ANGLE
struct RczHMsgSetCamberAngle : public RczHMsg
{
	int		servo_id;
	float	angle;
};

// RCZHMSG_ID_SET_SERVO_ONOFF
struct RczHMsgSetServoOnOff : public RczHMsg
{
	int onOff;
};

// RCZHMSG_ID_SET_CAMBER_ONOFF
struct RczHMsgSetCamberOnOff : public RczHMsg
{
	int servo_id;
	int onOff;
};

// RCZHMSG_ID_SET_MOTOR_ONOFF
struct RczHMsgSetMotorOnOff : public RczHMsg
{
	int onOff;
};

//	RCZHMSG_ID_GET_SENSOR_INFO_RES
struct RczHMsgGetSensorRes : public RczHMsg
{
	float gyro;
	float acc_x;
	float acc_y;
	float acc_z;
	float motor_enc;
	float wheel_enc1;
	float wheel_enc2;
	float wheel_enc3;
	float wheel_enc4;
};

// RCZHMSG_ID_GET_OBSTACLE_INFO_RES
struct RczHMsgGetObstacleRes : public RczHMsg
{
	ushort ir_obstacle[8];
};

// RCZHMSG_ID_GET_POWER_INFO_RES
struct RczHMsgGetPowerRes : public RczHMsg
{
	float motor_current;
	float motor_battery;
};

// RCZHMSG_ID_GET_LRS_INFO_RES
struct RczHMsgGetLRSRes : public RczHMsg
{
	LRSResult lrs_data;
};

// RCZHMSG_ID_GET_SERVO_INFO_RES
struct RczHMsgGetServoRes : RczHMsg
{
	int servo_id;
	float present_position;
	int present_speed;
	int present_current;
	int present_temperature;
	int present_volts;
};

// RCZHMSG_ID_GET_CAMBER_INFO_RES
struct RczHMsgGetCamberRes : RczHMsg
{
	RczHMsgGetServoRes camber_data[5];
};

// RCZHMSG_ID_SET_GYRO_OFFSET
struct RczHMsgSetGyroOffset : RczHMsg
{
	float offset;
};

//RCZHMSG_ID_SET_CURRENT_OFFSET
struct RczHMsgSetCurrentOffset : RczHMsg
{
	float offset;
};

//RCZHMSG_ID_SET_STEER_OFFSET
struct RczHMsgSetSteerOffset : RczHMsg
{
	float offset;
};

//RCZHMSG_ID_SET_CAMBER_OFFSET
struct RczHMsgSetCamberOffset : RczHMsg
{
	int		servo_id;
	float	offset;
};

// RCZHMSG_ID_SET_DRIVE_TORQUE
struct RczHMsgSetDriveTorque : public RczHMsg
{
	int		torque;
};

// RCZHMSG_ID_SET_DRIVE_MODE
struct RczHMsgSetDriveMode : public RczHMsg
{
	uchar		mode;
};

//RCZHMSG_ID_SET_COMMUNICATION_CONFIG
struct RczHMsgSetCommunicationConfig : RczHMsg
{
    int controlDelay;      // 通信遅れのシミュレーション[ms]i
    int sensorFrequency;   // センサの通信間隔[ms]
	COMM_ENCODE encode;           // MJPEG or Raw
    COMM_RATE rate;             // 30[Hz] or 15[Hz]
    COMM_RESOLUTION resolution;       // VGA or QVGA
};

//RCZHMSG_ID_SET_CONTROL_CONFIG
struct RczHMsgSetControlConfig : RczHMsg
{
    float thresholdG;   // 横Gの閾値[G]
    int slowDownSec;    // 減速時間[ms]
    float slowDownG;    // 減速G[G]
    int thresholdSec;	// 通信断閾値[ms]
    int slowDownSec2;	// 停止時間[ms]
};

//RCZHMSG_ID_START_VIDEO_LOG
struct RczHMsgStartVideoLog : RczHMsg
{
	int len;
    char logName[64];  // ファイル名(*.avi)
};

//RCZHMSG_ID_STOP_VIDEO_LOG
struct RczHMsgStopVideoLog : RczHMsg
{
};

//RCZHMSG_ID_START_SENSOR_LOG
struct RczHMsgStartSensorLog : RczHMsg
{
	int len;
    char logName[64];  // ファイル名(*.avi)
};

//RCZHMSG_ID_STOP_SENSOR_LOG
struct RczHMsgStopSensorLog : RczHMsg
{
};

struct RczHMsgDisparityAverage : RczHMsg
{
	uchar value[8 * 6];
};



#pragma pack(pop)


#endif // __RCZ_HMSG_H__



