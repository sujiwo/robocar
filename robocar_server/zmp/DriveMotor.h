/**
 * @file
 *
 * @~english
 * @brief	Drive motor class header.
 *
 * @author	Koji Sekiguchi
 *
 * @~japanese
 * @brief	駆動用モータクラスのヘッダ.
 *
 * @author	関口 浩司
 *
 * @~
 * @date	2009-04-01
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#ifndef DRIVEMOTOR_H_
#define DRIVEMOTOR_H_

#include "BaseboardCom.h"
#include "RS232Communication.h"


namespace zmp {
	namespace zrc {

	/**
	 * @~english
	 * Drive motor Speed setting message structure.
	 * @~japanese
	 * ドライブモータの速度設定メッセージ構造体
	 */
	struct CPU_BASE_SET_MOTOR_VELOCITY {
		/**
		 * @~english	RS232 message header. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 * @~japanese	RS232 メッセージヘッダ. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 */
		char header[2];
		/**
		 * @~english	message length. MSG_LEN_SET_MOTOR_VELOCITY 0x03.
		 * @~japanese	メッセージ長. MSG_LEN_SET_MOTOR_VELOCITY 0x03.
		 */
		char len;
		/**
		 * @~english	message symbol. MSG_SYM_MOTOR_VELOCITY 'V'.
		 * @~japanese	メッセージシンボル. MSG_SYM_MOTOR_VELOCITY 'V'.
		 */
		char sym;
		/**
		 * @~english	setting value. -2800 ～ 2800[mm/sec].
		 * @~japanese	設定値. -2800 ～ 2800[mm/sec].
		 */
		char veloc[2];
		/**
		 * @~english check sum.
		 * @~japanese	チェックsum.
		 */
		char sum;
	};

	/**
	 * @~english
	 * Drive motor enable message structure.
	 * @~japanese
	 * ドライブモータON/OFFメッセージ構造体
	 */
	struct CPU_BASE_SET_MOTOR_ENABLE {
		/**
		 * @~english	RS232 message header. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 * @~japanese	RS232 メッセージヘッダ. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 */
		char header[2];
		/**
		 * @~english	message length. MSG_LEN_SET_MOTOR_STATE 0x02.
		 * @~japanese	メッセージ長. MSG_LEN_SET_MOTOR_STATE 0x02.
		 */
		char len;
		/**
		 * @~english	message symbol. MSG_SYM_MOTOR_STATE 'M'.
		 * @~japanese	メッセージシンボル. MSG_SYM_MOTOR_STATE 'M'.
		 */
		char sym;
		/**
		 * @~english	setting value. 0=Drive motor FREE. 1=Drive motor ON. 2=Drive motor BRAKE.
		 * @~japanese	設定値. 0=ドライブモータ Free. 1=ドライブモータON. 2=ドライブモータBRAKE.
		 */
		char enable;
		/**
		 * @~english check sum.
		 * @~japanese	チェックsum.
		 */
		char sum;
	};

	/**
	 * @~english
	 * Drive Motor torque setting message structure.
	 * @~japanese
	 * ドライブモータトルクメッセージ構造体
	 */
	struct CPU_BASE_SET_MOTOR_TORQUE {
		/**
		 * @~english	RS232 message header. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 * @~japanese	RS232 メッセージヘッダ. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 */
		char header[2];
		/**
		 * @~english	message length. MSG_LEN_SET_MOTOR_CONTROL 0x02.
		 * @~japanese	メッセージ長. MSG_LEN_SET_MOTOR_CONTROL 0x02.
		 */
		char len;
		/**
		 * @~english	message symbol. MSG_SYM_MOTOR_CONTROL 'C'.
		 * @~japanese	メッセージシンボル. MSG_SYM_MOTOR_CONTROL 'C'.
		 */
		char sym;
		/**
		 * @~english	proportional value. 0 ～ 255.
		 * @~japanese	Pゲイン. 0 ～ 255.
		 */
		char proportional;
		/**
		 * @~english	integral value. 0 ～ 255.
		 * @~japanese	Iゲイン. 0 ～ 255.
		 */
		char integral;
		/**
		 * @~english	differential value. 0 ～ 255.
		 * @~japanese	Dゲイン. 0 ～ 255.
		 */
		char differential;
		/**
		 * @~english	width value. Unused.
		 * @~japanese	width. 未使用.
		 */
		char width;
		/**
		 * @~english check sum.
		 * @~japanese	チェックsum.
		 */
		char sum;
	};

/**
 * @~english
 * Drive motor class.
 * This class provide the access to the DC motor for drive the car.
 * @~japanese
 * 駆動用モータクラス.
 * RCカーを走らせるためのDCモータへのアクセスを行う。
 */
class DriveMotor {
public:
	/**
	 * @~english
	 * Drive motor class Constructor.
	 * @~japanese
	 * ドライブモータクラスのコンストラクタ
	 */
	DriveMotor();
	/**
	 * @~enblish
	 * Drive motor class Destructor.
	 * @~japanese
	 * ドライブモータクラスのデストラクタ
	 */
	virtual ~DriveMotor();

	/**
	 * @~english
	 * Motor drive class initialization.
	 * @param[in]		serial_com	Address of serial communication class.
	 * @~japanese
	 * モータ駆動クラスの初期化処理
	 * @param[in]		serial_com	シリアル通信クラスのアドレス.
	 */
	void Init(RS232Communication* serial_com);

	/**
	 * @~english
	 * Motor drive speed setting request.
	 * @param[in]		velocity	Motor drive speed.
	 * @retval	true		Message transmission success.
	 * @retval	false		Message transmission failure.
	 * @~japanese
	 * モータ駆動速度設定要求
	 * @param[in]		velocity	モータ駆動速度.
	 * @retval	true		メッセージ送信成功
	 * @retval	false		メッセージ送信失敗
	 */
	BASEBOARD_ERROR_KIND SetMotorVelocityReq(int velocity);

	/**
	 * @~english
	 * Motor enable setting request.
	 * @param[in]		enable 	Motor enable.
	 * @retval	true		Message transmission success.
	 * @retval	false		Message transmission failure.
	 * @~japanese
	 * モータON/OFF設定要求
	 * @param[in]		enable		モータON/OFF.
	 * @retval	true		メッセージ送信成功
	 * @retval	false		メッセージ送信失敗
	 */
	BASEBOARD_ERROR_KIND SetMotorEnableReq(char enable);

	/**
	 * @~english
	 * Motor torque setting request.
	 * @param[in]		p		Proportional.
	 * @param[in]		i		Integral.
	 * @param[in]		d		Differential.
	 * @param[in]		w		Width. Unused.
	 * @retval	true		Message transmission success.
	 * @retval	false		Message transmission failure.
	 * @~japanese
	 * モータトルク設定要求
	 * @param[in]		p		P(比例動作).
	 * @param[in]		i		I(積分動作).
	 * @param[in]		d		D(微分動作).
	 * @param[in]		w		width. 未使用.
	 * @retval	true		メッセージ送信成功
	 * @retval	false		メッセージ送信失敗
	 */
	BASEBOARD_ERROR_KIND SetMotorTorqueReq(char p, char i, char d, char w);

	/**
	 * @~english
	 * Receive handler setting request.
	 * @param[in]		handler	receive handler.
	 * @~japanese
	 * モータ駆動速度設定要求
	 * @param[in]		handler	受信ハンドラ.
	 */
	BASEBOARD_ERROR_KIND SetReceiveHandler(SerialReceiveHandler* handler);

private:
	RS232Communication* _RS232;
};


	}
}

#endif /* DRIVEMOTOR_H_ */
