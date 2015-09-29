/**
 * @file
 *
 * @~english
 * @brief	Baseboard class header.
 *
 * @author	Koji Sekiguchi
 *
 * @~japanese
 * @brief	Baseboardクラスのヘッダ.
 *
 * @author	関口 浩司
 *
 * @~
 * @date	2009-04-20
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#ifndef BASEBOARD_H_
#define BASEBOARD_H_

#include "DriveMotor.h"
#include "InternalSensor.h"
#include "IrObstacle.h"
#include "PowerControl.h"
#include "SteeringServoMotor.h"
#include "RS232Communication.h"
#include "RS485Communication.h"
#include "BaseboardCom.h"

namespace zmp {
	namespace zrc {

	/**
	 * @~english
	 * Setting response flag message structure between CPU and Base board.
	 * @~japanese
	 * CPU=>ベースボード間の繰り返し通知フラグ設定要求メッセージ構造体
	 */
	struct CPU_BASE_SET_FLG_REQ {
		/**
		 * @~english	RS232 message header. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 * @~japanese	RS232メッセージヘッダ. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 */
		char header[2];
		/**
		 * @~english	message length. MSG_LEN_REQ_FLAG 0x02.
		 * @~japanese	メッセージ長. MSG_LEN_REQ_FLAG 0x02.
		 */
		char len;
		/**
		 * @~english	message symbol. MSG_SYM_RES_FLAG 'F'.
		 * @~japanese	メッセージシンボル. MSG_SYM_RES_FLAG 'F'.
		 */
		char sym;
		/**
		 * @~english	setting value. bit0=Sensor. bit1=Obstacle. bit2=Power. bit3～7=reserve.
		 * @~japanese	設定値. bit0=Sensor. bit1=Obstacle. bit2=Power. bit3～7=reserve.
		 */
		char flg;
		/**
		 * @~english check sum.
		 * @~japanese	チェックsum.
		 */
		char sum;
	};

/**
 * @~english
 * Baseboard class.
 * This class accesses the SteeringServoMotor class, SerialCommunication class, PowerControl class IrObstacle class, InternalSensor class, DriveMotor class.
 * @~japanese
 * ベースボードクラス.
 * SteeringServoMotorクラス、SerialCommunicationクラス、PowerControlクラス、IrObstacleクラス、InternalSensorクラス、DriveMotorクラスへアクセスする。
 */
class Baseboard {
public:
	/**
	 * @~english
	 * Baseboard class Constructor.
	 * @~japanese
	 * ベースボードクラスのコンストラクタ
	 */
	Baseboard();

	/**
	 * @~english
	 * Baseboard class Destructor.
	 * @~japanese
	 * ベースボードクラスのデストラクタ
	 */
	virtual ~Baseboard();

	/**
	 * @~english
	 * Baseboard class initialization.
	 * @retval	BASE_OK					Initialization success.
	 * @retval	BASE_BASE_232_INIT_ERR	RS232 port Initialization failure.
 	 * @retval	BASE_BASE_485_INIT_ERR	RS485 port Initialization failure.
	 * @~japanese
	 * Baseboardクラスの初期化処理
	 * @retval	BASE_OK	初期化処理成功
	 * @retval	BASE_BASE_232_INIT_ERR	RS232ポート初期化失敗
	 * @retval	BASE_BASE_485_INIT_ERR	RS485ポート初期化失敗
	 */
	BASEBOARD_ERROR_KIND Init();

	/**
	 * @~english
	 * Baseboard class Start.
	 * @retval	BASE_OK	Start success.
	 * @~japanese
	 * Baseboardクラスの処理開始
	 * @retval	BASE_OK	処理開始成功
	 */
	BASEBOARD_ERROR_KIND Start();

	/**
	 * @~english
	 * Baseboard class Stop.
	 * @retval	BASE_OK	Stop success.
	 * @~japanese
	 * Baseboardクラスの処理停止
	 * @retval	BASE_OK	処理停止成功
	 */
	BASEBOARD_ERROR_KIND Stop();

	/**
	 * @~english
	 * Baseboard class Close.
	 * @retval	BASE_OK	Close success.
	 * @~japanese
	 * Baseboardクラスのclose
	 * @retval	BASE_OK	close処理成功
	 */
	BASEBOARD_ERROR_KIND Close();

	/**
	 * @~english
	 * Acquisition RS232 data.
	 * @param[out]	msg		Acquisition serial data address.
	 * @retval	BASE_OK						RS232data getting success.
	 * @retval	BASE_BASE_232_GETDATA_ERR	RS232data getting failure.
	 * @~japanese
	 * RS232データ取得
	 * @param[out]	msg		取得データのアドレス.
	 * @retval	BASE_OK						RS232データ取得成功
	 * @retval	BASE_BASE_232_GETDATA_ERR	RS232データ取得失敗
	 */
	BASEBOARD_ERROR_KIND GetRS232Data(char* msg);

	/**
	 * @~english
	 * Acquisition RS485 data.
	 * @param[out]	msg		Acquisition serial data address.
	 * @retval	BASE_OK						RS485data getting success.
	 * @retval	BASE_BASE_485_GETDATA_ERR	RS485data getting failure.
	 * @~japanese
	 * RS485データ取得
	 * @param[out]	msg		取得データのアドレス.
	 * @retval	BASE_OK						RS485データ取得成功
	 * @retval	BASE_BASE_485_GETDATA_ERR	RS485データ取得失敗
	 */
	BASEBOARD_ERROR_KIND GetRS485Data(char* msg);

	/**
	 * @~english
	 * Setting of reception handler.
	 * @param[in]		handler	Reception handler.
	 * @retval	BASE_OK		Reception handler setting success.
	 * @~japanese
	 * 受信ハンドル設定
	 * @param[in]		handler	受信ハンドル
	 * @retval	BASE_OK		受信ハンドル設定成功
	 */
	BASEBOARD_ERROR_KIND SetReceiveHandler(SerialReceiveHandler* handler);

	/**
	 * @~english
	 * Set servo information.
	 * @param[in]		id		servo ID.
	 * @param[in]		adr		servo map address.
	 * @param[in]		msg		set value.
	 * @param[in]		len		value lenght.
	 * @retval	BASE_OK	Servo information setting success.
	 * @~japanese
	 * サーボ情報設定
	 * @param[in]		id		サーボID.
	 * @param[in]		adr		サーボ情報マップアドレス.
	 * @param[in]		msg		設定値.
	 * @param[in]		len		設定値の長さ.
	 * @retval	BASE_OK	サーボ情報設定成功.
	 */
	BASEBOARD_ERROR_KIND SetServoInfo(int id, SERVO_INFO_ADR adr, unsigned char* msg, int len);

	/**
	 * @~english
	 * Send ROM operation request.
	 * @param[in]		id		servo ID.
	 * @param[in]		kind	ROM operation kind.
	 * @retval	BASE_OK	Servo ROM operation success.
	 * @~japanese
	 * ROM操作要求送信
	 * @param[in]		id		サーボID.
	 * @param[in]		kind	ROM操作種別.
	 * @retval	BASE_OK	サーボROM操作成功.
	 */
	BASEBOARD_ERROR_KIND SendROMOperatReq(int id, ROM_OPERAT_KIND kind);

	/**
	 * @~english
	 * Get servo information request.
	 * @param[in]		id		servo ID.
	 * @param[in]		adr		Get information address.
	 * @param[in]		len		Get information length.
	 * @retval	BASE_OK	Servo information getting success.
	 * @~japanese
	 * サーボ情報取得要求
	 * @param[in]		id		サーボID.
	 * @param[in]		adr		取得情報アドレス.
	 * @param[in]		len		取得情報の長さ.
	 * @retval	BASE_OK	サーボ情報取得成功.
	 */
	BASEBOARD_ERROR_KIND GetServoInfoReq(int id, SERVO_INFO_ADR adr, int len);

	/**
	 * @~english
	 * Power information acquisition request.
	 * @retval	BASE_OK	Power information getting success.
	 * @~japanese
	 * 電源情報取得要求
	 * @retval	BASE_OK	電源情報取得成功.
	 */
	BASEBOARD_ERROR_KIND GetPowerInfoReq();

	/**
	 * @~english
	 * Ir Obstacle sensor information acquisition request.
	 * @retval	BASE_OK	Obstacle information getting success.
	 * @~japanese
	 * 赤外線障害物センサ情報取得要求
	 * @retval	BASE_OK	障害物センサ情報取得成功.
	 */
	BASEBOARD_ERROR_KIND GetObstacleInfoReq();

	/**
	 * @~english
	 * Sensor information acquisition request.
	 * @retval	BASE_OK	Sensor information getting success.
	 * @~japanese
	 * センサ情報取得要求
	 * @retval	BASE_OK	内部センサ情報取得成功.
	 */
	BASEBOARD_ERROR_KIND GetSensorInfoReq();

	/**
	 * @~english
	 * Motor drive speed setting request.
	 * @param[in]		velocity	Motor drive speed.
	 * @retval	BASE_OK	Drive speed setting success.
	 * @~japanese
	 * モータ駆動速度設定要求
	 * @param[in]		velocity	モータ駆動速度.
	 * @retval	BASE_OK	モータ駆動速度設定成功.
	 */
	BASEBOARD_ERROR_KIND SetMotorVelocityReq(int velocity);

	/**
	 * @~english
	 * report flag setting request.
	 * @param[in]		flg 	setting flg.
	 * bit0=Sensor.
	 * bit1=Obstacle.
	 * bit2=Power.
	 * bit3～bit7=reserve.
	 * @retval	BASE_OK	Report flag setting success.
	 * @~japanese
	 * 繰り返し通知設定要求
	 * 10ms毎に通知するかどうかを設定する.
	 * @param[in]		flg 	通知設定フラグ.
	 * bit0=Sensor.
	 * bit1=Obstacle.
	 * bit2=Power.
	 * bit3～bit7=reserve.
	 * @retval	BASE_OK	繰り返し通知設定成功.
	 */
	BASEBOARD_ERROR_KIND SetReportFlagReq(char flg);

	/**
	 * @~english
	 * Motor Enable setting request.
	 * @param[in]		enable 	Motor enable.
	 * @retval	BASE_OK	Motor Enable setting success.
	 * @~japanese
	 * モータON/OFF設定要求
	 * @param[in]		enable 	モータON/OFF.
	 * @retval	BASE_OK	モータON/OFF設定成功.
	 */
	BASEBOARD_ERROR_KIND SetMotorEnableReq(char enable);

	/**
	 * @~english
	 * Drive Motor torque setting request.
	 * @param[in]		p		Proportional.
	 * @param[in]		i		Integral
	 * @param[in]		d		Differential
	 * @param[in]		w		Width
	 * @retval	BASE_OK	Motor torque setting success.
	 * @~japanese
	 * ドライブモータトルク設定要求.
	 * @param[in]		p		P(比例動作).
	 * @param[in]		i		I(積分動作).
	 * @param[in]		d		D(微分動作).
	 * @param[in]		w		width.
	 * @retval	BASE_OK	ドライブモータトルク設定成功.
	 */
	BASEBOARD_ERROR_KIND SetMotorTorqueReq(char p, char i, char d, char w);

private:
	SteeringServoMotor	_Steer;
	PowerControl			_Power;
	IrObstacle			_Obstacle;
	InternalSensor		_Sensor;
	DriveMotor			_Drive;

public:
	RS232Communication	_RS232;
	RS485Communication	_RS485;
};

	}
}

#endif /* BASEBOARD_H_ */
