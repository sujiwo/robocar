/**
 * @file
 *
 * @~english
 * @brief	RS232 communication class header.
 *
 * @author	Koji Sekiguchi
 *
 * @~japanese
 * @brief	RS232通信クラスのヘッダ.
 *
 * @author	関口 浩司
 *
 * @~
 * @date	2009-04-13
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#ifndef RS232COMMUNICATION_H_
#define RS232COMMUNICATION_H_

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

//extern int errno;

namespace zmp {
	namespace zrc {
class CRingBuffer;

/**
 * @~english
 * Serial message handler interface.
 * This is pure virtual class. It provides the callback method of receiving data from the serial.
 * @~japanese
 * シリアルメッセージハンドラインタフェース.
 * 仮想クラス。シリアルメッセージ受診時のコールバックメソッドを提供する。
 */
/*class SerialReceiveHandler{
public:
	virtual void OnReceive232()	= 0;
	virtual void OnReceive485()	= 0;
};*/

/**
 * @~english
 * RS232 communication class.
 * This is supports the SW controls and monitoring of the power level and circuit current.
 * This is supports the serial device control and message send and receive.
 * @~japanese
 * 電源管理クラス.
 * RS232通信デバイスの制御とメッセージの送受信を行う。
 */
class RS232Communication {
public:
	/**
	 * @~english
	 * RS232 communication class Constructor.
	 * @~japanese
	 * RS232通信クラスのコンストラクタ
	 */
	RS232Communication();
	/**
	 * @~english
	 * RS232 communication class Destructor.
	 * @~japanese
	 * RS232通信クラスのデストラクタ
	 */
	virtual ~RS232Communication();

private:
	static const int _DEFAULT_BUFFER_DEPTH;
	char temp1[128];
	bool	_b_on_RS232rcv_thread;
	char temp2[128];
	int _RS232fd;
	pthread_t _RS232thread;

	struct termios _RS232oldtio;
	struct termios _RS232newtio;
	struct pollfd _RS232client;
	char temp[512];
	SerialReceiveHandler* _callback_handler;
	CRingBuffer*	_RS232rcvBuffer;

public:

	/**
	 * @~english
	 * Message send processing.
	 * @param[in]		msg		Send message address.
	 * @param[in]		len		Send message length.
	 * @~japanese
	 * メッセージ送信処理
	 * @param[in]		msg		送信メッセージアドレス
	 * @param[in]		len		送信メッセージ長
	 */

	BASEBOARD_ERROR_KIND Send232Message(unsigned char* msg, int len);
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
	BASEBOARD_ERROR_KIND RS232Init();

	/**
	 * @~english
	 * Setting of reception handler.
	 * @param[in]		handler	Reception handler.
	 * @~japanese
	 * 受信ハンドル設定
	 * @param[in]		handler	受信ハンドル
	 */
	BASEBOARD_ERROR_KIND SetRS232ReceiveHandle(SerialReceiveHandler *handler);

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
	BASEBOARD_ERROR_KIND GetRS232Data(char* msg);

	/**
	 * @~english
	 * Start of receive processing.
	 * @~japanese
	 * 受信処理開始
	 */
	void RS232Start();

	/**
	 * @~english
	 * Stop of receive processing.
	 * @~japanese
	 * 受信処理停止
	 */
	void RS232Stop();

	/**
	 * @~english
	 * Stop of RS232Communication class.
	 * @~japanese
	 * RS232Communication class処理停止
	 */
	void RS232Close();

private:

	BASEBOARD_ERROR_KIND RS232InitThread();
	BASEBOARD_ERROR_KIND RS232InitDevice();
	void RS232ReadThread();
	static void* RS232ReadThreadEntry(void* pParam);
	unsigned char calc_sum(const unsigned char *data, int len);

};

	}
}
#endif /* RS232COMMUNICATION_H_ */
