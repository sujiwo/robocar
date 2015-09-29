/**
 * @file
 *
 * @~english
 * @brief	Steering servo motor class header.
 *
 * @author	Koji Sekiguchi
 *
 * @~japanese
 * @brief	操舵用サーボモータクラスのヘッダ.
 *
 * @author	関口 浩司
 *
 * @~
 * @date	2009-04-13
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#ifndef STEERINGSERVOMOTOR_H_
#define STEERINGSERVOMOTOR_H_

//#include "BaseboardCom.h"
#include "RS485Communication.h"

namespace zmp {
	namespace zrc {

	/**
	 * @~english	Steering servo Memory map address.
	 * @~japanese	サーボモータ メモリマップアドレス.
	 */
	enum SERVO_INFO_ADR{
		// 変更不可領域
		/**
		 * @~english	model number low byte. read only.
		 * @~japanese	モデル番号 下位 byte. read only.
		 */
		MODEL_NUMBER_L	 	= 0x00,
		/**
		 * @~english	model number high byte. read only.
		 * @~japanese	モデル番号 上位 byte. read only.
		 */
		MODEL_NUMBER_H 		= 0x01,
		/**
		 * @~english	Firmware version. read only.
		 * @~japanese	ファームウェアバージョン. read only.
		 */
		FIRM_VERSION			= 0x02,
		// ROM領域
		/**
		 * @~english	Servo ID. default=1
		 * @~japanese	サーボID. default=1
		 */
		SERVO_ID				= 0x04,
		/**
		 * @~english	Direction of rotation.
		 * @~japanese	回転方向.
		 */
		REVERSE				= 0x05,
		/**
		 * @~english	RS485 transmission rate. default=115200bps.
		 * @~japanese	RS485通信速度. default=115200bps.
		 */
		BAUD_RATE				= 0x06,
		/**
		 * @~english	return delay. 100+50*RETURN_DELAY=delay time(us).
		 * @~japanese	応答遅延. 100+50*RETURN_DELAY=遅延時間(us).
		 */
		RETURN_DELAY			= 0x07,
		/**
		 * @~english	CW angle limit low byte.
		 * @~japanese	CW 角度リミット下位byte.
		 */
		CW_ANGLE_LIMIT_L		= 0x08,
		/**
		 * @~english	CW angle limit high byte.
		 * @~japanese	CW 角度リミット上位byte.
		 */
		CW_ANGLE_LIMIT_H		= 0x09,
		/**
		 * @~english	CCW angle limit low byte.
		 * @~japanese	CCW 角度リミット下位byte.
		 */
		CCW_ANGLE_LIMIT_L	= 0x0a,
		/**
		 * @~english	CCW angle limit high byte.
		 * @~japanese	CCW 角度リミット上位byte.
		 */
		CCW_ANGLE_LIMIT_H	= 0x0b,
		/**
		 * @~english	Temperature limit low byte.
		 * @~japanese	温度リミット 下位byte.
		 */
		TEMP_LIMIT_L			= 0x0e,
		/**
		 * @~english	Temperature limit high byte.
		 * @~japanese	温度リミット 上位byte.
		 */
		TEMP_LIMIT_H			= 0x0f,
		/**
		 * @~english	CW compliance margin.
		 * @~japanese	CW 停止位置許容範囲.
		 */
		CW_COMP_MARGIN		= 0x18,
		/**
		 * @~english	CCW compliance margin.
		 * @~japanese	CCW 停止位置許容範囲.
		 */
		CCW_COMP_MARGIN		= 0x19,
		/**
		 * @~english	CW compliance slope.
		 * @~japanese	CW 目標位置へ戻るトルクを制御する範囲.
		 */
		CW_COMP_SLOPE			= 0x1a,
		/**
		 * @~english	CCW compliance slope.
		 * @~japanese	CCW 目標位置へ戻るトルクを制御する範囲.
		 */
		CCW_COMP_SLOPE		= 0x1b,
		/**
		 * @~english	Minimum current when driving low byte.
		 * @~japanese	駆動時の最小電流 下位byte.
		 */
		PUNCH_L				= 0x1c,
		/**
		 * @~english	Minimum current when driving high byte.
		 * @~japanese	駆動時の最小電流 上位byte.
		 */
		PUNCH_H				= 0x1d,
		// RAM領域
		/**
		 * @~english	Goal position low byte.
		 * @~japanese	目標位置 下位byte.
		 */
		GOAL_POSITION_L		= 0x1e,
		/**
		 * @~english	Goal position high byte.
		 * @~japanese	目標位置 上位byte.
		 */
		GOAL_POSITION_H		= 0x1f,
		/**
		 * @~english	Transition time low byte.
		 * @~japanese	移動時間 下位byte.
		 */
		GOAL_TIME_L			= 0x20,
		/**
		 * @~english	Transition time high byte.
		 * @~japanese	移動時間 上位byte.
		 */
		GOAL_TIME_H			= 0x21,
		/**
		 * @~english	Maximum torque(%).
		 * @~japanese	最大トルク(%).
		 */
		MAX_TORQUE			= 0x23,
		/**
		 * @~english	Torque ON/OFF/BRAKE.
		 * @~japanese	トルク ON/OFF/BRAKE.
		 */
		TORQUE_ENABLE			= 0x24,
		/**
		 * @~english	Present position low byte.
		 * @~japanese	現在位置 下位byte.
		 */
		PRESENT_POSITION_L	= 0x2a,
		/**
		 * @~english	Present position high byte.
		 * @~japanese	現在位置 上位byte.
		 */
		PRESENT_POSITION_H	= 0x2b,
		/**
		 * @~english	Elapsed time low byte.
		 * @~japanese	経過時間 下位byte.
		 */
		PRESENT_TIME_L		= 0x2c,
		/**
		 * @~english	Elapsed time high byte.
		 * @~japanese	経過時間 上位byte.
		 */
		PRESENT_TIME_H		= 0x2d,
		/**
		 * @~english	Rotational speed low byte. (deg/sec).
		 * @~japanese	回転速度 下位byte.(deg/sec).
		 */
		PRESENT_SPEED_L		= 0x2e,
		/**
		 * @~english	Rotational speed high byte. (deg/sec).
		 * @~japanese	回転速度 上位byte.(deg/sec).
		 */
		PRESENT_SPEED_H		= 0x2f,
		/**
		 * @~english	Present current low byte. (mA).
		 * @~japanese	現在負荷 下位byte.(mA).
		 */
		PRESENT_CURRENT_L	= 0x30,
		/**
		 * @~english	Present current high byte. (mA).
		 * @~japanese	現在負荷 上位byte.(mA).
		 */
		PRESENT_CURRENT_H	= 0x31,
		/**
		 * @~english	Present temperature low byte. (℃).
		 * @~japanese	現在温度 下位byte.(℃).
		 */
		PRESENT_TEMP_L		= 0x32,
		/**
		 * @~english	Present temperature high byte. (℃).
		 * @~japanese	現在温度 上位byte.(℃).
		 */
		PRESENT_TEMP_H		= 0x33,
		/**
		 * @~english	Present volts low byte. (1=10mv).
		 * @~japanese	現在温度 下位byte.(1=10mv).
		 */
		PRESENT_VOLTS_L		= 0x34,
		/**
		 * @~english	Present volts high byte. (1=10mv).
		 * @~japanese	現在温度 上位byte.(1=10mv).
		 */
		PRESENT_VOLTS_H		= 0x35,
		//
		RAM_AREA_ALL			= 0xff,	// RAM領域
	};

	/**
	 * @~english	Steering servo ROM control kind.
	 * @~japanese	サーボモータ ROM操作種別.
	 */
	enum ROM_OPERAT_KIND{
		/**
		 * @~english	Reboot servo motor.
		 * @~japanese	サーボモータの再起動.
		 */
		SERVO_REBOOT			= 0x01,
		/**
		 * @~english	Write ROM.
		 * @~japanese	ROM書込み.
		 */
		WRITE_ROM				= 0x02,
		/**
		 * @~english	Write ROM.
		 * @~japanese	ROM書込み.
		 */
		WRITE_ROM_REBOOT		= 0x03,
		/**
		 * @~english	ROM refresh.
		 * @~japanese	ROMを工場出荷状態へ戻す.
		 */
		REFRESH_ROM			= 0x04
		};

/*	struct RS301CR_MEMORY_MAP_04_29{
		char id;
		char reverse;
		char baud_rate;
		char return_delay;
		char cw_limit_L;
		char cw_limit_H;
		char ccw_limit_L;
		char ccw_limit_H;
		char reserved1[2];
		char temp_limit_L;
		char temp_limit_H;
		char reserved2[8];
		char cw_comp_mrg;
		char ccw_comp_mrg;
		char cw_cmp_slope;
		char ccw_cmp_slope;
		char punch_L;
		char punch_H;
	};

	struct RS301CR_MEMORY_MAP_20_29{
		char reserved[4];
		char cw_comp_mrg;
		char ccw_comp_mrg;
		char cw_cmp_slope;
		char ccw_cmp_slope;
		char punch_L;
		char punch_H;
	};


	struct RS301CR_MEMORY_MAP_30_59{
		char goal_position_L;
		char goal_position_H;
		char goal_time_L;
		char goal_time_H;
		char reserved0;
		char max_torque;
		char torque_enable;
		char reserved1[5];
		char present_position_L;
		char present_position_H;
		char present_time_L;
		char presetn_time_H;
		char present_speed_L;
		char present_speed_H;
		char present_current_L;
		char present_current_H;
		char present_temperature_L;
		char present_temperature_H;
		char present_volts_L;
		char present_volts_H;
		char reserved2[6];
	};

	struct RS301CR_MEMORY_MAP_30_41{
		char goal_position_L;
		char goal_position_H;
		char goal_time_L;
		char goal_time_H;
		char reserved0;
		char max_torque;
		char torque_enable;
		char reserved1[5];
	};

	struct RS301CR_MEMORY_MAP_42_59{
		char present_position_L;
		char present_position_H;
		char present_time_L;
		char presetn_time_H;
		char present_speed_L;
		char present_speed_H;
		char present_current_L;
		char present_current_H;
		char present_temperature_L;
		char present_temperature_H;
		char present_volts_L;
		char present_volts_H;
		char reserved2[6];
	};*/

	/**
	 * @~english	Steering servo message format.
	 * @~japanese	サーボモータ メッセージフォーマット
	 */
	struct CPU_SERVO_SEND_INFO {
		/**
		 * @~english	RS485 message header. 0xfa, 0xaf.
		 * @~japanese	RS485 メッセージヘッダ. 0xfa, 0xaf.
		 */
		char header[2];
		/**
		 * @~english	servo ID (default=1).
		 * @~japanese	サーボID (default=1).
		 */
		char id;
		/**
		 * @~english	control flags. bit7=Unused, bit6=ROM write, bit5=reboot, bit4=refresh, bit3～0=return address select.
		 * @~japanese	制御フラグ. bit7=未使用, bit6=ROM書込み, bit5=再起動, bit4=工場出荷状態に戻す, bit3～0=リターンアドレス設定.
		 */
		char flg;
		/**
		 * @~english	Memory Map address.
		 * @~japanese	メモリマップアドレス.
		 */
		char adr;
		/**
		 * @~english	Data length.
		 * @~japanese	データ長.
		 */
		char len;
		/**
		 * @~english	Servo number.
		 * @~japanese	サーボ数.
		 */
		char cnt;
	};

	/**
	 * @~english	Steering servo request message format.
	 * @~japanese	サーボモータ リクエストメッセージフォーマット
	 */
	struct CPU_SERVO_REQ_INFO {
		/**
		 * @~english	RS485 message header. 0xfa, 0xaf.
		 * @~japanese	RS485 メッセージヘッダ. 0xfa, 0xaf.
		 */
		char header[2];
		/**
		 * @~english	servo ID (default=1).
		 * @~japanese	サーボID (default=1).
		 */
		char id;
		/**
		 * @~english	control flags. bit7=Unused, bit6=ROM write, bit5=reboot, bit4=refresh, bit3～0=return address select.
		 * @~japanese	制御フラグ. bit7=未使用, bit6=ROM書込み, bit5=再起動, bit4=工場出荷状態に戻す, bit3～0=リターンアドレス設定.
		 */
		char flg;
		/**
		 * @~english	Memory Map address.
		 * @~japanese	メモリマップアドレス.
		 */
		char adr;
		/**
		 * @~english	Data length.
		 * @~japanese	データ長.
		 */
		char len;
		/**
		 * @~english	Servo number.
		 * @~japanese	サーボ数.
		 */
		char cnt;
		/**
		 * @~english check sum.
		 * @~japanese	チェックsum.
		 */
		char sum;
	};

	/**
	 * @~english	Steering servo response message format.
	 * @~japanese	サーボモータ 応答メッセージフォーマット
	 */
	struct CPU_SERVO_RES_INFO {
		/**
		 * @~english	RS485 message header. MSG_HEADER_485_0 0xfd. MSG_HEADER_485_1 0xdf.
		 * @~japanese	RS485 メッセージヘッダ. MSG_HEADER_485_0 0xfd. MSG_HEADER_485_1 0xdf.
		 */
		char header[2];
		/**
		 * @~english	servo ID (default=1).
		 * @~japanese	サーボID (default=1).
		 */
		char id;
		/**
		 * @~english	control flags. bit7=Unused, bit6=ROM write, bit5=reboot, bit4=refresh, bit3～0=return address select.
		 * @~japanese	制御フラグ. bit7=未使用, bit6=ROM書込み, bit5=再起動, bit4=工場出荷状態に戻す, bit3～0=リターンアドレス設定.
		 */
		char flg;
		/**
		 * @~english	Memory Map address.
		 * @~japanese	メモリマップアドレス.
		 */
		char adr;
		/**
		 * @~english	Data length.
		 * @~japanese	データ長.
		 */
		char len;
		/**
		 * @~english	Servo number.
		 * @~japanese	サーボ数.
		 */
		char cnt;
	};

	/**
	 * @~english
	 * Servo message format struct
	 * @~japanese
	 * メッセージフォーマット構造体
	 */
//	struct CPU_SERVO_FORM {
		/**
		 * @~english	RS485 message header. MSG_HEADER_485_0 0xfd. MSG_HEADER_485_1 0xdf.
		 * @~japanese	RS485 メッセージヘッダ. MSG_HEADER_485_0 0xfd. MSG_HEADER_485_1 0xdf.
		 */
/*		char header[2];
		char len;
		char sym;
		char* data;
	};*/

/**
 * @~english
 * Steering serovo motor class.
 * Controls the steering servo motor and obtains the servo status.
 * @~japanese
 * 操舵用サーボモータクラス.
 * 操舵操作と、現在のサーボの取得。
 */
class SteeringServoMotor {
public:
	/**
	 * @~english
	 * Steering servo motor class Constructor.
	 * @~japanese
	 * 操舵用サーボモータクラスのコンストラクタ
	 */
	SteeringServoMotor();
	/**
	 * @~english
	 * Steering servo motor class Destructor.
	 * @~japanese
	 * 操舵用サーボモータクラスのデストラクタ
	 */
	virtual ~SteeringServoMotor();

	/**
	 * @~english
	 * Steering servo motor class initialization.
	 * @param[in]		serial_com	Serial communication class address.
	 * @~japanese
	 * 操舵用サーボモータクラスの初期化
	 * @param[in]		serial_com	シリアル通信クラスのアドレス.
	 */
	void Init(RS485Communication* serial_com);

/*	void Start();
	void Stop();
	void Close();*/

	/**
	 * @~english
	 * Setting of reception handler.
	 * @param[in]		handler	Reception handler.
	 * @~japanese
	 * 受信ハンドル設定
	 * @param[in]		handler	受信ハンドル
	 */
	BASEBOARD_ERROR_KIND SetReceiveHandler(SerialReceiveHandler* handler);

	/**
	 * @~english
	 * Set servo information.
	 * @param[in]		id		servo ID.
	 * @param[in]		adr		servo map address.
	 * @param[in]		value	set value.
	 * @param[in]		len		value lenght.
	 * @retval	true		Message transmission success.
	 * @retval	false		Message transmission failure.
	 * @~japanese
	 * サーボ情報の設定
	 * @param[in]		id		サーボID.
	 * @param[in]		adr		サーボ情報マップアドレス.
	 * @param[in]		value	設定値.
	 * @param[in]		len		設定値の長さ.
	 * @retval	true		メッセージ送信成功
	 * @retval	false		メッセージ送信失敗
	 */
	BASEBOARD_ERROR_KIND SetServoInfo(int id, SERVO_INFO_ADR adr, unsigned char* value, int len);

	/**
	 * @~english
	 * Send ROM operation request.
	 * @param[in]		id		servo motor ID.
	 * @param[in]		kind	ROM operation kind.
	 * @retval	true		Message transmission success.
	 * @retval	false		Message transmission failure.
	 * @~japanese
	 * ROM操作要求送信
	 * @param[in]		id		サーボモータID.
	 * @param[in]		kind	ROM操作種別.
	 * @retval	true		メッセージ送信成功
	 * @retval	false		メッセージ送信失敗
	 */
	BASEBOARD_ERROR_KIND SendROMOperatReq(int id, ROM_OPERAT_KIND kind);

	/**
	 * @~english
	 * Get servo information request.
	 * @param[in]		servo_id	servo motor ID.
	 * @param[in]		info_adr	Get information address.
	 * @retval	true		Message transmission success.
	 * @retval	false		Message transmission failure.
	 * @~japanese
	 * サーボ情報取得要求
	 * @param[in]		servo_id	サーボモータID.
	 * @param[in]		info_adr	取得情報アドレス.
	 * @retval	true		メッセージ送信成功
	 * @retval	false		メッセージ送信失敗
	 */
	BASEBOARD_ERROR_KIND GetServoInfoReq(int servo_id, SERVO_INFO_ADR info_adr);

	/**
	 * @~english
	 * Get servo information request.
	 * @param[in]		servo_id	servo ID.
	 * @param[in]		info_adr	Get information address.
	 * @param[in]		len			Get information length.
	 * @retval	true		Message transmission success.
	 * @retval	false		Message transmission failure.
	 * @~japanese
	 * サーボ情報取得要求
	 * @param[in]		servo_id	サーボID.
	 * @param[in]		info_adr	取得情報アドレス.
	 * @param[in]		len			取得情報の長さ.
	 * @retval	true		メッセージ送信成功
	 * @retval	false		メッセージ送信失敗
	 */
	BASEBOARD_ERROR_KIND GetServoInfoReq(int servo_id, SERVO_INFO_ADR info_adr, int len);

private:
	RS485Communication* _RS485;

};

	}
}


#endif /* STEERINGSERVOMOTOR_H_ */


