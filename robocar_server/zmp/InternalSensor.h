/**
 * @file
 *
 * @~english
 * @brief	Internal sensor class header.
 *
 * @author	Koji Sekiguchi
 *
 * @~japanese
 * @brief	内部センサクラスのヘッダ.
 *
 * @author	関口 浩司
 *
 * @~
 * @date	2009-04-01
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#ifndef INTERNALSENSOR_H_
#define INTERNALSENSOR_H_

//#include "BaseboardCom.h"
#include "RS232Communication.h"

namespace zmp {
	namespace zrc {

	/**
	 * @~english
	 * Sensor information request message structure between CPU and Base board.
	 * @~japanese
	 * CPU=>ベースボード間のセンサ情報要求メッセージ構造体
	 */
	struct CPU_BASE_SENSOR_REQ {
		/**
		 * @~english	RS232 message header. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 * @~japanese	RS232 メッセージヘッダ. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 */
		char header[2];
		/**
		 * @~english	message length. MSG_LEN_REQ_SENSOR 0x01.
		 * @~japanese	メッセージ長. MSG_LEN_REQ_SENSOR 0x01.
		 */
		char len;
		/**
		 * @~english	message symbol. MSG_SYM_SENSOR 'S'.
		 * @~japanese	メッセージシンボル. MSG_SYM_SENSOR 'S'.
		 */
		char sym;
		/**
		 * @~english check sum.
		 * @~japanese	チェックsum.
		 */
		char sum;
	};

	/**
	 * @~english
	 * Sensor information response message structure.
	 * @~japanese
	 * センサ情報応答メッセージ構造体
	 */
	struct CPU_BASE_SENSOR_RES {
		/**
		 * @~english	RS232 message header. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 * @~japanese	RS232 メッセージヘッダ. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 */
		char header[2];
		/**
		 * @~english	message length. MSG_LEN_RES_SENSOR 0x13.
		 * @~japanese	メッセージ長. MSG_LEN_RES_SENSOR 0x13.
		 */
		char len;
		/**
		 * @~english	message symbol. MSG_SYM_SENSOR 'S'.
		 * @~japanese	メッセージシンボル. MSG_SYM_SENSOR 'S'.
		 */
		char sym;
		/**
		 * @~english	Gyro sensor value [deg/sec].
		 * @~japanese	ジャイロセンサ出力 [deg/sec].
		 */
		char gyro[2];
		/**
		 * @~english	Acceleration(X axis) sensor value [G].
		 * @~japanese	加速度(X軸)センサ出力 [G].
		 */
		char acc_x[2];
		/**
		 * @~english	Acceleration(Y axis) sensor value [G].
		 * @~japanese	加速度(Y軸)センサ出力 [G].
		 */
		char acc_y[2];
		/**
		 * @~english	Acceleration(Z axis) sensor value [G].
		 * @~japanese	加速度(Z軸)センサ出力 [G].
		 */
		char acc_z[2];
		/**
		 * @~english	motor encoder value [cycle/sec].
		 * @~japanese	モータエンコーダ出力 [cycle/sec].
		 */
		char enc_0[2];
		/**
		 * @~english	wheel encoder1 value [mm/sec].
		 * @~japanese	wheel エンコーダ1 出力 [mm/sec].
		 */
		char enc_1[2];
		/**
		 * @~english	wheel encoder2 value [mm/sec].
		 * @~japanese	wheel エンコーダ2 出力 [mm/sec].
		 */
		char enc_2[2];
		/**
		 * @~english	wheel encoder3 value [mm/sec].
		 * @~japanese	wheel エンコーダ3 出力 [mm/sec].
		 */
		char enc_3[2];
		/**
		 * @~english	wheel encoder4 value [mm/sec].
		 * @~japanese	wheel エンコーダ4 出力 [mm/sec].
		 */
		char enc_4[2];
		/**
		 * @~english check sum.
		 * @~japanese	チェックsum.
		 */
		char sum;
	};

/**
 * @~english
 * Internal sensor class.
 * This class accesses the base board to acquire sensor information.
 * @~japanese
 * 内部センサクラス.
 * センサ情報を取得するためにベースボードへのアクセスを行う。
 */
class InternalSensor {
public:
	/**
	 * @~english
	 * Internal sensor class Constructor.
	 * @~japanese
	 * 内部センサクラスのコンストラクタ
	 */
	InternalSensor();
	/**
	 * @~english
	 * Internal sensor class Destructor.
	 * @~japanese
	 * 内部センサクラスのデストラクタ
	 */
	virtual ~InternalSensor();

	/**
	 * @~english
	 * Internal sensor class initialization.
	 * @param[in]		serial_com	Address of serial communication class.
	 * @~japanese
	 * 内部センサ初期化処理
	 * @param[in]		serial_com	シリアル通信クラスのアドレス
	 */
	void Init(RS232Communication* serial_com);

	BASEBOARD_ERROR_KIND SetReceiveHandler(SerialReceiveHandler* handler);

	/**
	 * @~english
	 * Sensor information acquisition request.
	 * @retval	true		Message transmission success.
	 * @retval	false		Message transmission failure.
	 * @~japanese
	 * センサ情報取得要求
	 * @retval	true		メッセージ送信成功
	 * @retval	false		メッセージ送信失敗
	 */
	BASEBOARD_ERROR_KIND GetSensorInfoReq();

private:
	RS232Communication* _RS232;

};

	}
}

#endif /* INTERNALSENSOR_H_ */
