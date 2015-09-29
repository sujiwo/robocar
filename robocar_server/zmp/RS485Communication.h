/**
 * @file
 *
 * @~english
 * @brief	RS485 communication class header.
 *
 * @author	Koji Sekiguchi
 *
 * @~japanese
 * @brief	RS485通信クラスのヘッダ.
 *
 * @author	関口 浩司
 *
 * @~
 * @date	2009-04-13
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#ifndef RS485COMMUNICATION_H_
#define RS485COMMUNICATION_H_

#include <pthread.h>
#include <termios.h>
#include <poll.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/ioctl.h>
#include <errno.h>
#include "BaseboardCom.h"

extern int errno;

namespace zmp {
	namespace zrc {
class CRingBuffer;


/**
 * @~english
 * Serial communication class.
 * This is supports the SW controls and monitoring of the power level and circuit current.
 * This is supports the serial device control and message send and receive.
 * @~japanese
 * 電源管理クラス.
 * シリアル通信デバイスの制御とメッセージの送受信を行う。
 */
class RS485Communication {
public:
	/**
	 * @~english
	 * RS485 communication class Constructor.
	 * @~japanese
	 * RS485通信クラスのコンストラクタ
	 */
	RS485Communication();
	/**
	 * @~english
	 * RS485 communication class Destructor.
	 * @~japanese
	 * RS485通信クラスのデストラクタ
	 */
	virtual ~RS485Communication();

private:
	static const int _DEFAULT_BUFFER_DEPTH;
	char temp1[128];
	int _RS485fd;
	char temp2[128];
	bool	_b_on_RS485rcv_thread;
	struct termios _RS485oldtio;
	struct termios _RS485newtio;
	struct pollfd _RS485client;
	char temp3[128];
	pthread_t _RS485thread;
	char temp[1024];
	SerialReceiveHandler* _callback_handler;
	CRingBuffer*	_RS485rcvBuffer;
public:

	/**
	 * @~english
	 * RS485 Message send processing.
	 * @param[in]		msg		Send message address.
	 * @param[in]		len		Send message length.
	 * @~japanese
	 * メッセージ送信処理
	 * @param[in]		msg		送信メッセージアドレス
	 * @param[in]		len		送信メッセージ長
	 */
	BASEBOARD_ERROR_KIND Send485Message(unsigned char* msg, int len);

	/**
	 * @~english
	 * Serial communication class initialization.
	 * @retval	true		Initialization success.
	 * @retval	false		Initialization failure.
	 * @~japanese
	 * シリアル通信クラスの初期化処理
	 * @retval	true		初期化処理成功
	 * @retval	false		初期化処理失敗
	 */
	BASEBOARD_ERROR_KIND RS485Init();


	/**
	 * @~english
	 * Setting of reception handler.
	 * @param[in]		handler	Reception handler.
	 * @~japanese
	 * 受信ハンドル設定
	 * @param[in]		handler	受信ハンドル
	 */
	BASEBOARD_ERROR_KIND SetRS485ReceiveHandle(SerialReceiveHandler *handler);

	/**
	 * @~english
	 * Acquisition data.
	 * @param[out]	msg		Acquisition data address.
	 * @retval	true		Message transmission success.
	 * @retval	false		Message transmission failure.
	 * @~japanese
	 * データ取得
	 * @param[out]	msg		取得データのアドレス.
	 * @retval	true		メッセージ送信成功
	 * @retval	false		メッセージ送信失敗
	 */
	BASEBOARD_ERROR_KIND GetRS485Data(char* msg);

	/**
	 * @~english
	 * Start of receive processing.
	 * @~japanese
	 * 受信処理開始
	 */
	void RS485Start();

	/**
	 * @~english
	 * Stop of receive processing.
	 * @~japanese
	 * 受信処理停止
	 */
	void RS485Stop();

	/**
	 * @~english
	 * close of RS485Communication class.
	 * @~japanese
	 * RS485Communication class 停止
	 */
	void RS485Close();

private:

	BASEBOARD_ERROR_KIND RS485InitThread();
	BASEBOARD_ERROR_KIND RS485InitDevice();
	void RS485ReadThread();
	static void* RS485ReadThreadEntry(void* pParam);
	BASEBOARD_ERROR_KIND RTSOn();
	BASEBOARD_ERROR_KIND RTSOff();
	BASEBOARD_ERROR_KIND RTSCont(int control, int on);
};

	}
}
#endif /* RS485COMMUNICATION_H_ */
