/**
 * @file
 *
 * @~english
 * @brief			Baseboard common header.
 *
 * @author		Koji Sekiguchi
 *
 * @~japanese
 * @brief			Baseボード共通ヘッダ
 *
 * @author		関口 浩司
 *
 * @~
 * @date			2009-04-01
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 */
#ifndef BASEBOARDCOM_H_
#define BASEBOARDCOM_H_

#include "RingBuffer.h"
#include <stdio.h>

//#define DEBUG_RS232SND
//#define DEBUG_RS232RCV
//#define DEBUG_RS232PUT
//#define DEBUG_RS485SND
//#define DEBUG_RS485RCV
//#define DEBUG_RS485PUT

#define DEVICE_NAME232		"/dev/ttyS3"
#define RS232_BAUDRATE		B115200
#define RS232_RECEIVE_SIZE	32
#define MSG_HEADER_232_0 0xc5
#define MSG_HEADER_232_1 0x5c

#define DEVICE_NAME485		"/dev/ttyS1"
#define RS485_BAUDRATE		B115200
#define RS485_RECEIVE_SIZE	32
#define MSG_HEADER_485_0 0xfd
#define MSG_HEADER_485_1 0xdf

#define MSG_SYM_MOTOR_VELOCITY	'V'
#define MSG_SYM_SENSOR				'S'
#define MSG_SYM_OBSTACLE_SENSOR	'O'
#define MSG_SYM_POWER				'P'
#define MSG_SYM_RES_FLAG			'F'
#define MSG_SYM_MOTOR_STATE		'M'
#define MSG_SYM_MOTOR_CONTROL		'C'
#define MSG_LEN_SET_MOTOR_VELOCITY	3
#define MSG_LEN_SET_MOTOR_STATE		2
#define MSG_LEN_SET_MOTOR_CONTROL		5
#define MSG_LEN_REQ_SENSOR				1
#define MSG_LEN_REQ_OBSTACLE_SENSOR	1
#define MSG_LEN_REQ_POWER				1
#define MSG_LEN_REQ_FLAG				2

#define MSG_LEN_RES_SENSOR				19
#define MSG_LEN_RES_OBSTACLE_SENSOR	9
#define MSG_LEN_RES_POWER				3


#define SERIAL_READ_SIZE 256
#define NUM_OF_ADC2DIST_TABLE 15
//#define CURRENT_COUNT 	3.875
#define CURRENT_COUNT	0.0645
#define BATTERY_COUNT 	0.0386
#define ACC_COUNT		0.009765625
//#define GYRO_COUNT		0.214285
#define GYRO_COUNT		0.536585
//#define WHEEL_COUNT		20;
#define WHEEL_COUNT		19.328154296875
#define MOTOR_COUNT		0.195338
#define SPEED2COUNT		3.5
#define SET_SERVO_ANGLEMAX	30
#define SET_SERVO_ANGLEMIN	-30
#define SET_MOTOR_SPEEDMAX	1750
#define SET_MOTOR_SPEEDMIN	-1750
#define SET_SERVO_DEFAULTDELAY 58		// 3ms = 100us+(50us*58)

namespace zmp {
	namespace zrc {

	/**
	 * @~english
	 * Message handler kind.
	 * @~japanese
	 * メッセージハンドラ種別定義.
	 */
	enum HANDLER_KIND{
		/**
		 * @~english	Steering servo handler.
		 * @~japanese	ステアリングサーボハンドラ.
		 */
		H_STEER 		= 1,
		/**
		 * @~english	Power infomation handler.
		 * @~japanese	電源情報ハンドラ.
		 */
		H_POWER		= 2,
		/**
		 * @~english	nternal sensor information handler.
		 * @~japanese	内部センサ情報ハンドラ.
		 */
		H_SENSOR		= 3,
		/**
		 * @~english	Drive motor handler.
		 * @~japanese	ドライブモータハンドラ.
		 */
		H_DRIVE		= 4,
		/**
		 * @~english	Obstacle sensor information handler.
		 * @~japanese	障害物センサ情報ハンドラ.
		 */
		H_OBSTACLE	= 5,
		/**
		 * @~english	other.
		 * @~japanese	その他.
		 */
		H_OTHER		= 6,
		/**
		 * @~english	All.
		 * @~japanese	全部.
		 */
		H_ALL			= 7,
	};

	/**
	 * @~english
	 * Receive information kind.
	 * @~japanese
	 * 受信情報種別定義.
	 */
	enum RECEIVE_INFO_KIND {
		/**
		 * @~english	RS232 data.
		 * @~japanese	RS232 データ.
		 */
		RS232,
		/**
		 * @~english	RS485 data.
		 * @~japanese	RS485 データ.
		 */
		RS485,
	};

	/**
	 * @~english
	 * Baseboard error kind.
	 * @~japanese
	 * ベースボードエラー種別.
	 */
	enum BASEBOARD_ERROR_KIND{
		/**
		 * @~english	Success.
		 * @~japanese	成功.
		 */
		BASE_OK,
		/**
		 * @~english	Failure.
		 * @~japanese	失敗.
		 */
		BASE_NG,
		/**
		 * @~english	RS232 port open error.
		 * @~japanese	RS232ポートオープン失敗.
		 */
		BASE_RS232_PORT_OPEN_ERR,
		/**
		 * @~english	RS232 receive thread create error.
		 * @~japanese	RS232 受信スレッド生成失敗.
		 */
		BASE_RS232_THREAD_CREATE_ERR,
		/**
		 * @~english	RS232 data getting error.
		 * @~japanese	RS232 データ取得失敗.
		 */
		BASE_RS232_GET_DATA_ERR,
		/**
		 * @~english	RS232 handle setting error.
		 * @~japanese	RS232 ハンドル設定失敗.
		 */
		BASE_RS232_SET_HANDLE_ERR,
		/**
		 * @~english	RS485 port open error.
		 * @~japanese	RS485ポートオープン失敗.
		 */
		BASE_RS485_PORT_OPEN_ERR,
		/**
		 * @~english	RS485 receive thread create error.
		 * @~japanese	RS485 受信スレッド生成失敗.
		 */
		BASE_RS485_THREAD_CREATE_ERR,
		/**
		 * @~english	RS485 data getting error.
		 * @~japanese	RS485 データ取得失敗.
		 */
		BASE_RS485_GET_DATA_ERR,
		/**
		 * @~english	RS485 handle setting error.
		 * @~japanese	RS485 ハンドル設定失敗.
		 */
		BASE_RS485_SET_HANDLE_ERR,
		/**
		 * @~english	RS485 RTS ON change error.
		 * @~japanese	RS485 RTS ON 切替え失敗.
		 */
		BASE_RS485_CNG_RTSON_ERR,
		/**
		 * @~english	RS485 RTS OFF change error.
		 * @~japanese	RS485 RTS OFF 切替え失敗.
		 */
		BASE_RS485_CNG_RTSOFF_ERR,
		/**
		 * @~english	RS485 RTS control error.
		 * @~japanese	RS485 RTS 制御失敗.
		 */
		BASE_RS485_CNG_RTSCONT_ERR,
		/**
		 * @~english	Steer servo setting error.
		 * @~japanese	ステアリングサーボ設定失敗.
		 */
		BASE_STEER_SET_INFOREQ_ERR,
		/**
		 * @~english	Steer servo ROM control error.
		 * @~japanese	ステアリングサーボROM操作失敗.
		 */
		BASE_STEER_SEND_ROMOPERATREQ_ERR,
		/**
		 * @~english	Steer servo information getting error.
		 * @~japanese	ステアリングサーボ情報取得失敗.
		 */
		BASE_STEER_GET_INFOREQ_ERR,
		/**
		 * @~english	Power information getting error.
		 * @~japanese	電源情報取得失敗.
		 */
		BASE_POWER_GET_INFOREQ_ERR,
		/**
		 * @~english	IR Obstacle sensor information getting error.
		 * @~japanese	IR 障害物センサ情報取得失敗.
		 */
		BASE_OBSTACLE_GET_INFOREQ_ERR,
		/**
		 * @~english	Internal sensor information getting error.
		 * @~japanese	内部センサ情報取得失敗.
		 */
		BASE_SENSOR_GET_INFOREQ_ERR,
		/**
		 * @~english	Drive speed setting error.
		 * @~japanese	ドライブスピード設定失敗.
		 */
		BASE_DRIVE_SET_VELOCITYREQ_ERR,
		/**
		 * @~english	Drive motor on/off/brake/ setting error.
		 * @~japanese	ドライブモータ on/off/brake 設定失敗.
		 */
		BASE_DRIVE_SET_ENABLEREQ_ERR,
		/**
		 * @~english	Drive motor torque setting error.
		 * @~japanese	ドライブモータトルク設定失敗.
		 */
		BASE_DRIVE_SET_TORQUEREQ_ERR,
	};

	/**
	 * @~english
	 * Internal sensor information structure.
	 * @~japanese
	 * 内部センサ情報構造体
	 */
	struct SENSOR_VALUE {
		/**
		 * @~english
		 * Gyro sensor [deg/sec].
		 * @~japanese
		 * ジャイロセンサ [deg/sec].
		 */
		float gyro;
		/**
		 * @~english
		 * Acceleration sensor(X axis) [G].
		 * @~japanese
		 * 加速度センサ(X軸) [G].
		 */
		float acc_x;
		/**
		 * @~english
		 * Acceleration sensor(Y axis) [G].
		 * @~japanese
		 * 加速度センサ(Y軸) [G].
		 */
		float acc_y;
		/**
		 * @~english
		 * Acceleration sensor(Z axis) [G].
		 * @~japanese
		 * 加速度センサ(Z軸) [G].
		 */
		float acc_z;
		/**
		 * @~english
		 * Motor Encoder [cycle/sec].
		 * @~japanese
		 * モータ エンコーダ [cycle/sec].
		 */
		float enc_0;
		/**
		 * @~english
		 * Wheel Encoder1 [mm/sec].
		 * @~japanese
		 * Wheel エンコーダ1 [mm/sec].
		 */
		float enc_1;
		/**
		 * @~english
		 * Wheel Encoder2 [mm/sec].
		 * @~japanese
		 * Wheel エンコーダ2 [mm/sec].
		 */
		float enc_2;
		/**
		 * @~english
		 * Wheel Encoder3 [mm/sec].
		 * @~japanese
		 * Wheel エンコーダ3 [mm/sec].
		 */
		float enc_3;
		/**
		 * @~english
		 * Wheel Encoder4 [mm/sec].
		 * @~japanese
		 * Wheel エンコーダ4 [mm/sec].
		 */
		float enc_4;
	};

	/**
	 * @~english
	 * Obstacle sensor information structure.
	 * @~japanese
	 * 障害物センサ情報構造体
	 */
	struct OBSTACLE_VALUE {
		/**
		 * @~english
		 * obstacle sensor[8] [mm].
		 * @~japanese
		 * 障害物センサ[8] [mm].
		 */
		unsigned short obstacle[8];
	};

	/**
	 * @~english
	 * Power information structure.
	 * @~japanese
	 * 電源情報構造体
	 */
	struct POWER_VALUE {
		/**
		 * @~english
		 * motor current [mA].
		 * @~japanese
		 * モータ電流 [mA].
		 */
		double motor_current;
		/**
		 * @~english
		 * battery level [V].
		 * @~japanese
		 * バッテリレベル [V].
		 */
		double battery_level;
	};

	/**
	 * @~english
	 * Drive information structure.
	 * @~japanese
	 * ドライブ情報構造体
	 */
	struct DRIVE_VALUE {
		/**
		 * @~english
		 * servo ID.
		 * @~japanese
		 * サーボID.
		 */
		char	id;
		/**
		 * @~english
		 * servo reverse.
		 * @~japanese
		 * サーボ回転方向.
		 */
		char	reverse;
		/**
		 * @~english
		 * baud rate.
		 * @~japanese
		 * 通信速度.
		 */
		char	baud_rate;
		/**
		 * @~english
		 * return delay.
		 * @~japanese
		 * 返信遅延.
		 */
		char	return_delay;
		/**
		 * @~english
		 * CW angle limit.
		 * @~japanese
		 * CW 可動リミット.
		 */
		float	cw_limit;
		/**
		 * @~english
		 * CCW angle limit.
		 * @~japanese
		 * CCW 可動リミット.
		 */
		float	ccw_limit;
		/**
		 * @~english
		 * temperature limit.
		 * @~japanese
		 * 可動温度リミット.
		 */
		int		temp_limit;
		char	cw_comp_mrg;
		char	ccw_comp_mrg;
		char	cw_comp_slope;
		char	ccw_comp_slope;
		/**
		 * @~english
		 * Punch.
		 * @~japanese
		 * Punch.
		 */
		float	punch;
		/**
		 * @~english
		 * Goal position.
		 * @~japanese
		 * 指定角度.
		 */
		float	goal_position;
		/**
		 * @~english
		 * goal time.
		 * @~japanese
		 * 指定時間.
		 */
		int		goal_time;
		/**
		 * @~english
		 * max torque.
		 * @~japanese
		 * 最大トルク.
		 */
		char 	max_torque;
		/**
		 * @~english
		 * torque enable.
		 * @~japanese
		 * トルク状態.
		 */
		char 	torque_enable;
		/**
		 * @~english
		 * present position.
		 * @~japanese
		 * 現在角度.
		 */
		float	present_position;
		/**
		 * @~english
		 * present time.
		 * @~japanese
		 * 現在時間.
		 */
		int		present_time;
		/**
		 * @~english
		 * present speed.
		 * @~japanese
		 * 現在速度.
		 */
		int		present_speed;
		/**
		 * @~english
		 * present current.
		 * @~japanese
		 * 現在負荷(電流).
		 */
		int		present_current;
		/**
		 * @~english
		 * present temperature.
		 * @~japanese
		 * 現在温度.
		 */
		int		present_temperature;
		/**
		 * @~english
		 * present volts.
		 * @~japanese
		 * 現在電圧.
		 */
		int		present_volts;
	};

	struct SET_CAMBER_ANGLES {
		int 	id[4];
		float	angle[4];
	};

	/**
	 * @~english
	 * Serial message handler interface.
	 * This is pure virtual class. It provides the callback method of receiving data from the serial.
	 * @~japanese
	 * シリアルメッセージハンドラインタフェース.
	 * 仮想クラス。シリアルメッセージ受診時のコールバックメソッドを提供する。
	 */
	class SerialReceiveHandler{
		public:
			virtual void On485Receive()	= 0;
			virtual void On232Receive()	= 0;
	};

	}
}
#endif /* BASEBOARDCOM_H_ */
