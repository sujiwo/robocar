/**
 * @file
 *
 * @~english
 * @brief	Ir Obstacle sensor class header.
 *
 * @author	Koji Sekiguchi
 *
 * @~japanese
 * @brief	赤外線障害物センサクラスのヘッダ.
 *
 * @author	関口 浩司
 *
 * @~
 * @date	2009-04-13
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#ifndef IROBSTACLE_H_
#define IROBSTACLE_H_

//#include "BaseboardCom.h"
#include "RS232Communication.h"

namespace zmp {
	namespace zrc {
	/**
	 * @~english
	 * Ir Obstacle sensor information request message structure.
	 * @~japanese
	 * Ir障害物センサ情報要求メッセージ構造体
	 */
	struct CPU_BASE_OBSTACLE_REQ {
		/**
		 * @~english	RS232 message header. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 * @~japanese	RS232 メッセージヘッダ. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 */
		char header[2];
		/**
		 * @~english	message length. MSG_LEN_REQ_OBSTACLE_SENSOR 0x01.
		 * @~japanese	メッセージ長. MSG_LEN_REQ_OBSTACLE_SENSOR 0x01.
		 */
		char len;
		/**
		 * @~english	message symbol. MSG_SYM_OBSTACLE_SENSOR 'O'.
		 * @~japanese	メッセージシンボル. MSG_SYM_OBSTACLE_SENSOR 'O'.
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
	 * Ir Obstacle sensor information response message structure.
	 * @~japanese
	 * Ir障害物センサ情報応答メッセージ構造体
	 */
	struct CPU_BASE_OBSTACLE_RES {
		/**
		 * @~english	RS232 message header. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 * @~japanese	RS232 メッセージヘッダ. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 */
		char header[2];
		/**
		 * @~english	message length. MSG_LEN_RES_OBSTACLE_SENSOR 0x09.
		 * @~japanese	メッセージ長. MSG_LEN_RES_OBSTACLE_SENSOR 0x09.
		 */
		char len;
		/**
		 * @~english	message symbol. MSG_SYM_OBSTACLE_SENSOR 'O'.
		 * @~japanese	メッセージシンボル. MSG_SYM_OBSTACLE_SENSOR 'O'.
		 */
		char sym;
		/**
		 * @~english	Ir obstacle sensor value [mm].
		 * @~japanese	Ir 障害物センサ出力 [mm].
		 */
		char Ir[8];
		/**
		 * @~english check sum.
		 * @~japanese	チェックsum.
		 */
		char sum;
	};


/**
 * @~english
 * Ir obstacle sensor class.
 * This class accesses the base board to acquire Ir obstacle sensor information.
 * @~japanese
 * 赤外線障害物センサクラス.
 * 赤外線障害物センサ情報を取得するためにベースボードへのアクセスを行う。
 */
class IrObstacle {
public:
	/**
	 * @~english
	 * Ir Obstacle class Constructor.
	 * @~japanese
	 * 赤外線障害物クラスのコンストラクタ
	 */
	IrObstacle();
	/**
	 * @~english
	 * Ir Obstacle class Destructor.
	 * @~japanese
	 * 赤外線障害物クラスのデストラクタ
	 */
	virtual ~IrObstacle();
	/**
	 * @~english
	 * Ir Obstacle sensor class initialization.
	 * @param[in]		serial_com	Address of serial communication class.
	 * @~japanese
	 * 赤外線障害物センサクラスの初期化処理
	 * @param[in]		serial_com	シリアル通信クラスのアドレス
	 */
	void Init(RS232Communication* serial_com);

	BASEBOARD_ERROR_KIND SetReceiveHandler(SerialReceiveHandler* handler);

	/**
	 * @~english
	 * Ir Obstacle sensor information acquisition request.
	 * @retval	true		Message transmission success.
	 * @retval	false		Message transmission failure.
	 * @~japanese
	 * 赤外線障害物センサ情報取得要求
	 * @retval	true		メッセージ送信成功
	 * @retval	false		メッセージ送信失敗
	 */
	BASEBOARD_ERROR_KIND GetObstacleInfoReq();

private:
	RS232Communication* _RS232;
};

	}
}

#endif /* IROBSTACLE_H_ */
