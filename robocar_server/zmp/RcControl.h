/**
 * @file
 *
 * @~english
 * @brief	RcControl class header.
 *
 * @author	Koji Sekiguchi
 *
 * @~japanese
 * @brief	RC制御クラスヘッダ.
 *
 * @author	関口 浩司
 *
 * @~
 * @date	2009-04-20
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#ifndef RCCONTROL_H_
#define RCCONTROL_H_

#include "Baseboard.h"

namespace zmp {
	namespace zrc {

	const static ushort adc_values[NUM_OF_ADC2DIST_TABLE] = {
			713, 512, 418, 341, 279, 251, 229, 204, 186, 170, 155, 145, 139, 130, 124,
	};

	const static ushort distance_values[NUM_OF_ADC2DIST_TABLE] = {
			10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80,
	};

	enum RC_ERROR_KIND{
		RC_BASE_INIT_ERR	= 0x100,
		RC_BASE_START_ERR		,
		RC_BASE_STOP_ERR			,
		RC_BASE_GET232DATA_ERR	,

	};

class DataReceiveHandler {
public:
	virtual void OnReceiveServo(char* data) = 0;
	virtual void OnReceiveBase(char* data, int kind) = 0;
};

/**
 * @~english
 * RC control class.
 * This class accesses the Baseboard class to control RC.
 * @~japanese
 * RCコントロールクラス.
 * RCをコントロールするためにBaseboardクラスへのアクセスを行う。
 */
class RcControl:public SerialReceiveHandler {
public:
	RcControl();
	virtual ~RcControl();

	bool init();

	bool Start();
	bool Stop();
	bool Close();

	bool GetRS232Data(char* msg);
	bool GetRS485Data(char* msg);

	/**
	 * @~english
	 * Setting of reception handler.
	 * @param[in]		handler	reception handler.
	 * @param[in]		kind		handler kind.
	 * @retval	true	Information setting success.
	 * @retval	false	Information setting failure.
	 * @~japanese
	 * 受信ハンドルの設定.
	 * @param[in]		handler	受信ハンドル.
	 * @retval	true	情報設定成功
	 * @retval	false	情報設定失敗
	 */
	void SetReceiveHandler(SerialReceiveHandler* handler);

	/**
	 * @~english
	 * Setting of driving speed.
	 * @param[in]		speed	driving speed(mm/sec).Every 1 mm. Between from -2800 to 2800.
	 * @retval	true	Information setting success.
	 * @retval	false	Information setting failure.
	 * @~japanese
	 * 駆動速度の設定.
	 * @param[in]		speed	駆動速度(mm/sec). 1mm単位で設定範囲は-2800～2800.
	 * @retval	true	情報設定成功
	 * @retval	false	情報設定失敗
	 */
	bool SetDriveSpeed(int speed);

	/**
	 * @~english
	 * Setting of Servo Reverse.
	 * @param[in]		reverse	Servo Reverse. Initial value=0. 0=normal, 1=reverse.
	 * @retval	true	Information setting success.
	 * @retval	false	Information setting failure.
	 * @~japanese
	 * サーボ回転方向の設定.
	 * @param[in]		reverse	回転方向  初期値=0. 0=正転, 1=反転.
	 * @retval	true	情報設定成功
	 * @retval	false	情報設定失敗
	 */
	bool SetServoReverse(bool reverse);

	/**
	 * @~english
	 * Setting of Servo Return Delay.
	 * @param[in]		delay	Servo return delay. Initial value=58(5ms). 	return delay = 50 + (delay * 50) micro second.
	 * @retval	true	Information setting success.
	 * @retval	false	Information setting failure.
	 * @~japanese
	 * サーボ応答遅延の設定.
	 * @param[in]		delay	遅延時間  初期値=58(5ms). 遅延時間 = 50 + (delay * 50) マイクロ秒.
	 * @retval	true	情報設定成功
	 * @retval	false	情報設定失敗
	 */
	bool SetServoReturnDelay(int delay);

	/**
	 * @~english
	 * Setting of Steering angle.
	 * @param[in]		angle	Steering angle.Every 0.1 degrees. Between from -30.0 to 30.0.
	 * @retval	true	Information setting success.
	 * @retval	false	Information setting failure.
	 * @~japanese
	 * 操舵角の設定.
	 * @param[in]		angle	操舵角. 0.1度単位で設定範囲は-30.0～30.0.
	 * @retval	true	情報設定成功
	 * @retval	false	情報設定失敗
	 */
	bool SetSteerAngle(float angle);

	/**
	 * @~english
	 * Setting of max torque.
	 * @param[in]		torque		max torque. Every 1 percent. Between from 0 to 100%.
	 * @retval	true	Information setting success.
	 * @retval	false	Information setting failure.
	 * @~japanese
	 * 最大トルクの設定.
	 * @param[in]		torque		最大トルク. 1%単位で設定範囲は0(0%)～100(100%).
	 * @retval	true	情報設定成功
	 * @retval	false	情報設定失敗
	 */
	bool SetMaxTorque(int torque);

	/**
	 * @~english
	 * Setting of On-off of steering servo.
	 * @param[in]		enable		On-off OFF=0, ON=1, BRAKE=2.
	 * @retval	true	Information setting success.
	 * @retval	false	Information setting failure.
	 * @~japanese
	 * サーボモータのON/OFF.
	 * @param[in]		enable		ON/OFF OFF=0, ON=1, BRAKE=2.
	 * @retval	true	情報設定成功
	 * @retval	false	情報設定失敗
	 */
	bool SetServoEnable(int enable);

	/**
	 * @~english
	 * Getting of On-off of servo motor.
	 * @param[out]	reverse	reverse. 0=normal, 1=reverse.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * サーボモータのON/OFF状態の取得.
	 * @param[out]	reverse	reverse. 0=normal, 1=reverse.
	 * @retval	true	情報取得成功
	 * @retval	false	情報取得失敗
	 */
	bool GetServoReverse(char* reverse);

	/**
	 * @~english
	 * Getting of servo baud rate.
	 * @param[out]	rate	baud rate.
	 * 0=9,600bps 	1=14,400bps	2=19,200bps	3=28,800bps
	 * 4=38,400bps	5=57,600bps	6=76,800bps	7=115,200bps
	 * 8=153,600bps	9=230,400bps	a=460,800bps
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * サーボモータの通信速度の取得.
	 * @param[out]	rate	通信速度.
	 * 0=9,600bps 	1=14,400bps	2=19,200bps	3=28,800bps
	 * 4=38,400bps	5=57,600bps	6=76,800bps	7=115,200bps
	 * 8=153,600bps	9=230,400bps	a=460,800bps
	 * @retval	true	情報取得成功
	 * @retval	false	情報取得失敗
	 */
	bool GetServoBaudRate(char* rate);

	/**
	 * @~english
	 * Getting of temperature limit.
	 * @param[out]	temp	temperature limit. Every 1℃.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * 可動限界温度の取得.
	 * @param[out]	temp	可動限界温度. 1℃単位.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetTempLimit(int* temp);

	/**
	 * @~english
	 * Getting of goal angle.
	 * param[out]		angle	goal angle. Every 0.1 degree.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * 目標角度の取得.
	 * @param[out]	angle	目標角度. 0.1度単位.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetGoalAngle(float* angle);

	/**
	 * @~english
	 * Getting of transition time.
	 * @param[out]	time	transition time. Every 10ms Example(1)  100=1000ms.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * 指定時間の取得.
	 * @param[out]	time	指定時間. 10ms単位  例(1)  100=1000ms.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetGoalTime(int* time);

	/**
	 * @~english
	 * Getting of max torque.
	 * @param[out]	torque		max torque. Every 1%.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * 最大トルクの取得.
	 * @param[out]	torque		最大トルク. 1％単位.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetMaxTorque(char* torque);

	/**
	 * @~english
	 * Getting of torque enable.
	 * @param[out]	enable		torque enable. 0=OFF,  1=ON,  2=BRAKE.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * トルク状態の取得.
	 * @param[out]	enable		トルク状態. 0=OFF,  1=ON,  2=BRAKE.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetTorqueEnable(char* enable);

	/**
	 * @~english
	 * Getting of present angle.
	 * @param[out]	angle		present angle. Every 0.1 degree.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * サーボの現在位置の取得.
	 * @param[out]	angle		present angle. 0.1度単位
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetPresentAngle(float* angle);

	/**
	 * @~english
	 * Getting of present time.
	 * @param[out]	time	present time. Every 10ms  Example(1) 567=5670ms.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * サーボの移動開始からの経過時間取得.
	 * @param[out]	time	現在時間. 10ms単位  例(1)  567=5670ms.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetPresentTime(int* time);

	/**
	 * @~english
	 * Getting of present speed.
	 * @param[out]	speed	present speed. degree/second.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * サーボの現在の回転速度取得.
	 * @param[out]	speed	present speed. deg/sec単位.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetPresentSpeed(int* speed);

	/**
	 * @~english
	 * Getting of present current.
	 * @param[out]	current	present speed. Every 1mA.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * サーボの現在の負荷(電流)取得.
	 * @param[out]	current	present speed. 1mA単位.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetPresentCurrent(int* current);

	/**
	 * @~english
	 * Getting of present temperature.
	 * @param[out]	temp	present current. Every 1℃.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * サーボの現在の温度取得.
	 * @param[out]	temp	present current. 1℃単位.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetPresentTemp(int* temp);

	/**
	 * @~english
	 * Getting of present volts.
	 * @param[out]	volts	present volts. Every 10mV. Example(1)  740=7.4V.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * サーボの現在電圧取得.
	 * @param[out]	volts	現在電圧. 10mV単位. 例(1)   740=7.4V.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetPresentVolts(int* volts);

	/**
	 * @~english
	 * Get servo information request.
	 * @param[in]		id		servo ID.
	 * @param[in]		adr		Get information address.
	 * @param[in]		len		Get information length.
	 * @param[out]	value	Structure address where servo information is set.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * サーボ情報取得要求
	 * BaseBoardに対してServo情報取得メッセージを送信して、現在保持しているServo情報を返す
	 * @param[in]		id		サーボID.
	 * @param[in]		adr		取得情報アドレス.
	 * @param[in]		len		取得情報の長さ.
	 * @param[out]	value	サーボ情報が設定される構造体アドレス.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetServoInfoReq(int id, SERVO_INFO_ADR adr, int len, DRIVE_VALUE* value);

	/**
	 * @~english
	 * Get servo information.
	 * @param[out]	value	Structure address where servo information is set.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * サーボ情報取得
	 * 現在保持しているServo情報を返す
	 * @param[out]	value	サーボ情報が設定される構造体アドレス.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetServoInfo(DRIVE_VALUE* value);

	/**
	 * @~english
	 * Getting of Sensor Information.
	 * @param[out]	value	Structure address where sensor information is set.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * センサ情報の取得要求.
	 * @param[out]	value	センサ情報が設定される構造体アドレス.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetSensorInfoReq(SENSOR_VALUE* value);

	/**
	 * @~english
	 * Getting of power information.
	 * @param[out]	value	Structure address where power information is set.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * 電源情報の取得要求
	 * @param[out]	value	電源情報が設定される構造体アドレス.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetPowerInfoReq(POWER_VALUE* value);

	/**
	 * @~english
	 * Getting of Obstacle sensor information.
	 * @param[out]	value	Structure address where obstacle sensor information is set.
	 * @retval	true	Information acquisition success.
	 * @retval	false	Information acquisition failure.
	 * @~japanese
	 * 障害物センサ情報の取得要求.
	 * @param[out]	value	障害物センサ情報が設定される構造体アドレス.
	 * @retval	true	情報取得成功.
	 * @retval	false	情報取得失敗.
	 */
	bool GetObstacleSensorInfoReq(OBSTACLE_VALUE* value);

	/**
	 * @~english
	 * Setting of report flag.
	 * @param[in]		flag		Report information flag. bit0=Sensor. bit1=Obstacle. bit2=Power. bit3～bit4=reserve.
	 * @~japanese
	 * 通知情報フラグ設定要求.
	 * @param[in]	flag		通知する情報を設定するフラグ. bit0=Sensor. bit1=Obstacle. bit2=Power. bit3～bit4=reserve.
	 */
	void SetReportFlagReq(char flag);

	/**
	 * @~english
	 * Setting of Motor enable.
	 * @param[in]		enable		Motor enable.
	 * @~japanese
	 * モータON/OFF設定要求.
	 * @param[in]	enable		モータON/OFF.
	 */
	void SetMotorEnableReq(char enable);

	/**
	 * @~english
	 * Setting of Motor torque.
	 * @param[in]		p		Proportional.
	 * @param[in]		i		Integral
	 * @param[in]		d		Differential
	 * @param[in]		w		Width
	 * @~japanese
	 * モータトルク設定要求.
	 * @param[in]		p		P(比例動作).
	 * @param[in]		i		I(積分動作).
	 * @param[in]		d		D(微分動作).
	 * @param[in]		w		width.
	 */
	void SetMotorTorqueReq(char p, char i, char d, char w);

	/**
	 * @~english
	 * Setting of Current offset.
	 * @param[in]		offset		Current offset(A).
	 * @~japanese
	 * 電流オフセット設定.モータ電流のゼロ点設定
	 * @param[in]		offset		電流オフセット(A).
	 */
	void SetMotorCurrentOffset(float offset);

	/**
	 * @~english
	 * Setting of steering offset.
	 * @param[in]		offset		steering offset(deg).
	 * @~japanese
	 * ステアリングオフセット.ステアリング角度のゼロ点設定.
	 * @param[in]		offset		ステアリングオフセット(deg).
	 */
	void SetSteerAngleOffset(float offset);

	/**
	 * @~english
	 * Setting of gyro offset.
	 * @param[in]		offset		gyro offset(deg/s).
	 * @~japanese
	 * ジャイロオフセット.ジャイロセンサ出力のゼロ点設定.
	 * @param[in]		offset		ジャイロオフセット(deg/s).
	 */
	void SetGyroOffset(float offset);

	bool SetCamberAngle(int id, float angle);
	bool SetCamberAngle4(SET_CAMBER_ANGLES angles);
	bool SetCamberReturnDelay(int id, int delay);
	bool SetCamberMaxTorque(int id, int torque);
	bool SetCamberEnable(int id, int enable);
	bool SendROMOperat(int id, ROM_OPERAT_KIND kind);
	void SetCamberOffset(int id, float offset);
	void SetServoID(int oldID, int newID);

	/**
	 * @~ english
	 * Setting of data receive handler.
	 * @param[in]	handler		data receive handler.
	 * @~ japanese
	 * データ受信ハンドラ設定. Baseボードからメッセージを受信したタイミングで呼ばれるコールバック関数のハンドル設定.
	 * @param[in]	handler		データ受信ハンドラ.
	 */
	void SetDataReceiveHandler(DataReceiveHandler* handler);

	/**
	 * @~ english
	 * sensor output data -> distance.
	 * @param[in]	value		sensor output data.
	 * @retval			distance(mm).
	 * @~ japanese
	 * 障害物センサの距離変換処理.センサから出力された値を距離(mm)に変換する.
	 * @param[in]	value		センサ出力値.
	 * @retval			距離(mm).
	 */
	ushort IrAdcToDistance(unsigned char value);

	/**
	 * @~ english
	 * Getting of gyro offset.
	 * @param[out]	offset		gyro offset(deg/s).
	 * @~ japanese
	 * ジャイロオフセットの取得.
	 * @param[out]	offset		ジャイロオフセット(deg/s).
	 */
	void GetGyroOffset(float* offset);

	/**
	 * @~ english
	 * Getting of steer offset.
	 * @param[out]	offset		steering offset(deg).
	 * @~ japanese
	 * ステアリングオフセットの取得.
	 * @param[out]	offset		ステアリングオフセット(deg).
	 */
	void GetSteerOffset(float* offset);

	/**
	 * @~ english
	 * Getting of current offset.
	 * @param[out]	offset		current offset(A).
	 * @~japanese
	 * @param[out]	offset		電流オフセット(A).
	 */
	void GetCurrentOffset(float* offset);

	/**
	 * @~ english
	 * Getting of Baseboard class pointer.
	 * @param[out]	pointer		Baseboard class pointer.
	 * @~japanese
	 * Baseboard クラスのポインタ取得.
	 * @param[out]	pointer		Baseboardクラスポインタ.
	 */
	void GetBaseboardPointer(Baseboard* pointer);

private:
	struct READ_STATE{
		bool	sensor;
		bool	obstacle;
		bool	power;
		bool	drive;
	};

	enum READ_KIND{
		READ_SENSOR,
		READ_OBSTACLE,
		READ_POWER,
		READ_DRIVE
	};

	void ReceiveServoMessage(char* data);
	void ReceiveBaseBoardMessage(char* data);
	bool ChkReadState(READ_KIND kind, bool state);
	void SetReadState(READ_KIND kind, bool state);
//	ushort IrAdcToDistance(unsigned char value);
	bool ReadOffsetFile();
	bool WriteOffsetFile();

	Baseboard	_Base;
	int		_ServoID;
	SENSOR_VALUE	_SensorValue;
	OBSTACLE_VALUE	_ObstacleValue;
	POWER_VALUE	_PowerValue;
	DRIVE_VALUE	_DriveValue[5];
	READ_STATE	_readState;

	float 		_motorCurrent_offset;
	float		_steerAngle_offset;
	float		_gyro_offset;
	float		_camber1_offset;
	float		_camber2_offset;
	float		_camber3_offset;
	float		_camber4_offset;

	int		_rcv_kind;
	DataReceiveHandler* _callback_handler;
//	void SetDataReceiveHandler(DataReceiveHandler* handle);
	void On485Receive();
	void On232Receive();

};

	}
}

#endif /* RCCONTROL_H_ */
