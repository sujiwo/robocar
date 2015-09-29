/**
 * @file
 *
 * @~english
 * @brief	Power control class header.
 *
 * @author	Koji Sekiguchi
 *
 * @~japanese
 * @brief	電源管理クラスのヘッダ.
 *
 * @author	関口 浩司
 *
 * @~
 * @date	2009-04-13
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */


#ifndef POWERCONTROL_H_
#define POWERCONTROL_H_

//#include "BaseboardCom.h"
#include "RS232Communication.h"

namespace zmp {
	namespace zrc {

	/**
	 * @~english
	 * Power information request message structure between CPU and Base board.
	 * @~japanese
	 * CPU=>ベースボード間の電源情報要求メッセージ構造体
	 */
	struct CPU_BASE_POWER_REQ {
		/**
		 * @~english	RS232 message header. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 * @~japanese	RS232 メッセージヘッダ. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 */
		char header[2];
		/**
		 * @~english	message length. MSG_LEN_REQ_POWER 0x01.
		 * @~japanese	メッセージ長. MSG_LEN_REQ_POWER 0x01.
		 */
		char len;
		/**
		 * @~english	message symbol. MSG_SYM_POWER 'P'.
		 * @~japanese	メッセージシンボル. MSG_SYM_POWER 'P'.
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
	 * Power information response message structure between CPU and Base board.
	 * @~japanese
	 * CPU<=ベースボード間の電源情報応答メッセージ構造体
	 */
	struct CPU_BASE_POWER_RES {
		/**
		 * @~english	RS232 message header. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 * @~japanese	RS232 メッセージヘッダ. MSG_HEADER_232_0 0xc5. MSG_HEADER_232_1 0x5c.
		 */
		char header[2];
		/**
		 * @~english	message length. MSG_LEN_RES_POWER 0x03.
		 * @~japanese	メッセージ長. MSG_LEN_RES_POWER 0x03.
		 */
		char len;
		/**
		 * @~english	message symbol. MSG_SYM_POWER 'P'.
		 * @~japanese	メッセージシンボル. MSG_SYM_POWER 'P'.
		 */
		char sym;
		/**
		 * @~english	motor current value [mA].
		 * @~japanese	Ir モータ電流出力 [mA].
		 */
		char motor_current;
		/**
		 * @~english	motor battery value [V].
		 * @~japanese	Ir モータ電圧出力 [V].
		 */
		char battery_level;
		/**
		 * @~english check sum.
		 * @~japanese	チェックsum.
		 */
		char sum;
	};

/**
 * @~english
 * Power control class.
 * This is supports the SW controls and monitoring of the power level and circuit current.
 * @~japanese
 * 電源管理クラス.
 * 電源スイッチと、電圧、電流のモニタを行う。
 */
class PowerControl {
public:
	/**
	 * @~english
	 * Power control class Constructor.
	 * @~japanese
	 * 電源制御クラスのコンストラクタ
	 */
	PowerControl();
	/**
	 * @~english
	 * Power control class Destructor.
	 * @~japanese
	 * 電源制御クラスのデストラクタ
	 */
	virtual ~PowerControl();
	/**
	 * @~english
	 * Power control class initialization.
	 * @param[in]		serial_com	Address of serial communication class.
	 * @~japanese
	 * 電源制御クラスの初期化処理
	 * @param[in]		serial_com	シリアル通信クラスのアドレス
	 */
	void Init(RS232Communication* serial_com);

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
	 * Power information acquisition request.
	 * @retval	true		Message transmission success.
	 * @retval	false		Message transmission failure.
	 * @~japanese
	 * 電源情報取得要求
	 * @retval	true		メッセージ送信成功
	 * @retval	false		メッセージ送信失敗
	 */
	BASEBOARD_ERROR_KIND GetPowerInfoReq();

private:
	RS232Communication* _RS232;
};



	}
}

#endif /* POWERCONTROL_H_ */
