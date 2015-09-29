/**
 * @file
 *
 * @~english
 * @brief	Host Communication class header.
 *
 * @author	Masaki SegaWa
 *
 * @~japanese
 * @brief	ホスト通信のサーバクラスヘッダ.
 *
 * @author	瀬川正樹
 *
 * @~
 * @date	 2009/09/10
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#ifndef RCZCOMMSERVER_H_
#define RCZCOMMSERVER_H_

#include "socket.h"
//#include "DataCollector.h"
#include "RczHMsg.h"

//class TCPSocket;
//class SocketEventHandlerInterface;



/**
 * @~english
 * The Connection status notify handler interface.
 * This interface is a collback handler function when the connection is opened or closed.
 * @~japanese
 * 接続状態通知のハンドラインターフェイス.
 * 接続のオープン時、クローズ時に呼び出される。
 */
class RczCommServerStatusHandler
{
public:
	/**
	 * @~english
	 * @~japanese
	 * コネクションオープン時のメッセージハンドラ 
	 */
	virtual void onOpen();
	/**
	 * @~english
	 * @~japanese
	 * コネクションクローズ時のメッセージハンドラ 
	 */
	virtual void onClose();
};

/**
 * @~english
 * Message hadler interface for Imaging.
 * This interface is a callback handler function when receiving messages.
 * @~japanese
 * メッセージハンドラのインターフェイス 画像処理用.
 * メッセージ受信時にコールバックされるハンドラ関数のインターフェイス。
 */
class RczCommServerMessageHandler
{
public:
	/**
	 * @~english
	 * @~japanese
	 * IMAPCARプログラムのロード要求メッセージハンドラ.
	 */
	virtual void onLoadProgram(const RczHMsgLoadProgram *msg) = 0;
	/**
	 * @~english
	 * @~japanese
	 * イメージレポートフラグの設定メッセージハンドラ.
	 */
	virtual void onSetImageReportFlag(const RczHMsgSetImageReportFlag *msg) = 0;
	/**
	 * @~english
	 * @~japanese
	 * 結果レポートフラグの設定メッセージハンドラ.
	 */
	virtual void onSetResultReportFlag(const RczHMsgSetResultReportFlag *msg) = 0;
	/**
	 * @~english
	 * @~japanese
	 * IMAPCARステレオ処理のパラメータ設定メッセージハンドラ.
	 */
	virtual void onSetIpmStereoParam(const RczHMsgSetIpmStereoParam *msg) = 0;
	/**
	 * @~english
	 * @~japanese
	 * マップファイル更新通知メッセージハンドラ.
	 */
	virtual void onUpdateDatafile(const RczHMsgUpdateDatafile *msg) = 0;
	/**
	 * @~english
	 * @~japanese
	 * ホスト通知インターバルの設定メッセージハンドラ.
	 */
	virtual void onSetIntInterval(const RczHMsgSetIntInterval *msg) = 0;
};

/**
 * @~english
 * Message hadler interface for Imaging.
 * This interface is a callback handler function when receiving messages.
 * @~japanese
 * メッセージハンドラのインターフェイス 画像処理用.
 * メッセージ受信時にコールバックされるハンドラ関数のインターフェイス。
 */
class RczCommServerMessageAdapter : public RczCommServerMessageHandler
{
public:
	virtual void onLoadProgram(const RczHMsgLoadProgram *msg) {};
	virtual void onSetImageReportFlag(const RczHMsgSetImageReportFlag *msg) {};
	virtual void onSetResultReportFlag(const RczHMsgSetResultReportFlag *msg) {};
	virtual void onSetIpmStereoParam(const RczHMsgSetIpmStereoParam *msg) {};
	virtual void onUpdateDatafile(const RczHMsgUpdateDatafile *msg) {};
	virtual void onSetIntInterval(const RczHMsgSetIntInterval *msg) {};
};

/**
 * @~english
 * Message hadler interface for Control.
 * This interface is a callback handler function when receiving messages.
 * @~japanese
 * メッセージハンドラのインターフェイス 制御用.
 * メッセージ受信時にコールバックされるハンドラ関数のインターフェイス。
 */
class RcControlCommandHandler
{
public:
	/**
	 * @~english
	 * @~japanese
	 * ステアリングサーボのトルクON/OFF切り替え通知 メッセージハンドラ.
	 */
	virtual void onSetServoOnOff(const RczHMsgSetServoOnOff *msg) = 0;
	/**
	 * @~english
	 * @~japanese
	 * ステアリングサーボの角度指令通知 メッセージハンドラ.
	 */
	virtual void onSetSteerAngle(const RczHMsgSetSteerAngle *msg) = 0;
	/**
	 * @~english
	 * @~japanese
	 * 駆動用モータのON/OFF切り替え通知 メッセージハンドラ.
	 */
	virtual void onSetMotorOnOff(const RczHMsgSetMotorOnOff *msg) = 0;
	/**
	 * @~english
	 * @~japanese
	 * 速度指令通知 メッセージハンドラ.
	 */
	virtual void onSetDriveSpeed(const RczHMsgSetDriveSpeed *msg) = 0;
	/**
	 * @~english
	 * @~japanese
	 * ジャイロセンサのオフセット設定 メッセージハンドラ.
	 */
	virtual void onSetGyroOffset(const RczHMsgSetGyroOffset *msg) = 0;
	/**
	 * @~english
	 * @~japanese
	 * モータ電流のオフセット設定 メッセージハンドラ.
	 */
	virtual void onSetCurrentOffset(const RczHMsgSetCurrentOffset *msg) = 0;
	/**
	 * @~english
	 * @~japanese
	 * ステアリングサーボのゼロオフセット設定 メッセージハンドラ.
	 */
	virtual void onSetSteerOffset(const RczHMsgSetSteerOffset *msg) = 0;
	virtual void onSetAngleZeroOffset(const RczHMsgSetAngleZeroOffset *msg) = 0;
	virtual void onSetCamberOffset(const RczHMsgSetCamberOffset *msg) = 0;
	virtual void onSetCamberOnOff(const RczHMsgSetCamberOnOff *msg) = 0;
	virtual void onSetCamberAngle(const RczHMsgSetCamberAngle *msg) = 0;
	virtual void onSetControlMode(const RczHMsgSetControlMode *msg) = 0;
	virtual void onSetLaneKeepingParam(const RczHMsgSetLaneKeepingParam *msg) = 0;
	virtual void onSetTorqueEnable(const RczHMsgSetTorqueEnable *msg) = 0;
	virtual void onSetServoTorqueEnable(const RczHMsgSetTorqueEnable *msg) = 0;
	/**
	 * @~english
	 * @~japanese
	 */
	virtual void onBeginMotion(const RczHMsgBeginMotion *msg) = 0;
	/**
	 * @~english
	 * @~japanese
	 */
	virtual void onSetObstacleAvoidanceParam(const RczHMsgSetObstacleAvoidanceParam *msg) = 0;
};

/**
 * @~english
 * Message hadler interface for Control.
 * This interface is a callback handler function when receiving messages.
 * @~japanese
 * メッセージハンドラのインターフェイス 制御用.
 * メッセージ受信時にコールバックされるハンドラ関数のインターフェイス。
 */
class RcControlCommandAdapter : public RcControlCommandHandler
{
public:
	virtual void onSetTorqueEnable(const RczHMsgSetTorqueEnable *msg) {};
	virtual void onSetDriveSpeed(const RczHMsgSetDriveSpeed *msg) {};
	virtual void onSetSteerAngle(const RczHMsgSetSteerAngle *msg) {};
	virtual void onSetControlMode(const RczHMsgSetControlMode *msg) {};
	virtual void onSetAngleZeroOffset(const RczHMsgSetAngleZeroOffset *msg) {};
	virtual void onSetLaneKeepingParam(const RczHMsgSetLaneKeepingParam *msg) {};
	virtual void onSetServoTorqueEnable(const RczHMsgSetTorqueEnable *msg) {};
	virtual void onSetServoOnOff(const RczHMsgSetServoOnOff *msg) {};
	virtual void onSetMotorOnOff(const RczHMsgSetMotorOnOff *msg) {};
	virtual void onSetGyroOffset(const RczHMsgSetGyroOffset *msg) {};
	virtual void onSetCurrentOffset(const RczHMsgSetCurrentOffset *msg) {};
	virtual void onSetCamberOnOff(const RczHMsgSetCamberOnOff *msg) {};
	virtual void onSetCamberAngle(const RczHMsgSetCamberAngle *msg) {};
	virtual void onSetSteerOffset(const RczHMsgSetSteerOffset *msg) {};
	virtual void onSetCamberOffset(const RczHMsgSetCamberOffset *msg) {};
	virtual void onBeginMotion(const RczHMsgBeginMotion *msg) {}; 
	virtual void onSetObstacleAvoidanceParam(const RczHMsgSetObstacleAvoidanceParam *msg) {};
};


/**
 * @~english
　*　Socket Communications server class.
 * This is a Socket communication class. It communicate with RczCommunication.dll that Windows DLL of PC.
 * It have implemented messages for image processing and the robocar control.
 * @~japanese
 * ソケット通信のサーバクラス.
 * PCと通信するためのソケット通信を行うクラス。WindowsDLLのRczCommunication.dllと通信を行う、
 *　画像処理用と、RoboCarのコントロール用にいくつかメッセージを実装している。
 */
class RczCommServer : public SocketEventHandlerInterface
{
public:
	/**
	 * Constructor.
	 */
	RczCommServer();
	/**
	 * Destructor.
	 */
	virtual ~RczCommServer();

public:
	/**
	 * @~english
	 * Initialze
	 * @~japanese
	 * 初期化.
	 * @param 	port_no 	使用するポート番号を指定する。
	 * @return	成功したかどうかを返す。
	 */
	bool Init(int port_no);
	/**
	 * @~english
	 *
	 * @~japanese
	 * メッセージハンドラの登録.
	 * RczCommServerMessageAdapterで、登録されたメッセージを受け取るハンドラオブジェクトを登録する。
	 * @param 	handler 	ハンドラオブジェクトへのポインタ
	 * @return	成功したかどうかを返す。
	 */
	bool SetReceiveHandler(RczCommServerMessageHandler *handler);
	/**
	 * @~english
	 *
	 * @~japanese
	 * メッセージハンドラの登録.
	 * メッセージを受け取るハンドラオブジェクトを登録する。
	 * コントロール系のメッセージのハンドラも同時に登録する。
	 * @param 	handler 	ハンドラオブジェクトへのポインタ
	 * @param 	handler_rc 	コントロール系ハンドラオブジェクトへのポインタ
	 * @return	成功したかどうかを返す。
	 */
	bool SetReceiveHandler(RczCommServerMessageHandler *handler, RcControlCommandHandler *handler_rc);
	/**
	 * @~english
	 *
	 * @~japanese
	 * ステータスハンドラの登録.
	 * @param 	handler 	ハンドラオブジェクトへのポインタ
	 * @return	成功したかどうかを返す。
	 */
	bool SetStatusHandler(RczCommServerStatusHandler *handler);
	/**
	 * @~english
	 *
	 * @~japanese
	 * サーバの開始.
	 * サーバ動作を開始する。コネクションの待機状態となる。
	 * @return	成功したかどうかを返す。
	 */
	bool Start();
	/**
	 * @~english
	 *
	 * @~japanese
	 * メッセージの送信.
	 * メッセージオブジェクトを作成して、長さといっしょに渡す。
	 * @param 	msg 	メッセージ
	 * @param 	len 	メッセージ長さ[byte]
	 * @return	成功したかどうかを返す。
	 */
	bool Send(const uchar *msg, int len);
	/**
	 * @~english
	 *
	 * @~japanese
	 * メッセージの受信確認.
	 * メッセージの受信バッファを調査して、メッセージが届いているかどうかを返す。
	 * @retval	true　メッセージあり。
	 * @retval	false メッセージなし。
	 */
	bool IsReceiveMessage() const;
	/*
	 * @~english
	 *
	 * @~japanese
	 * 受信メッセージのコールバック呼び出し処理。
	 * フレームワークからこれを呼び出すことで、ハンドラ関数が実行される。
	 * @return	成功したかどうかを返す。
	 */
	bool KickCallback();
	/*
	 *
	 */
	bool GetMessage(RczHMsg *msg);

	bool GetClientName(char *name);
	bool IsConnect();

public:
	// overrides SocketEventHandlerInterface
	virtual void ReceiveProc(RingBuffer* receive_buf);
	virtual void InitStatus() {};
	virtual void OnConnectionOpen(std::string info) {};
	virtual void OnConnectionAccept(std::string info) {};
	virtual void OnConnectionClose(std::string info) {};
	virtual void OnConnectionDisconnect(std::string info) {};

protected:
	bool OnBody();
	bool QueueMessage(const RczHMsg* msg, int len);
	bool FetchMessage(unsigned char *msg_buff, RCZHMSG_ID *msg_id, int *length);
	bool ProcCallback(RCZHMSG_ID msg_id, RczHMsg *msg);


private:
	/**
	 * @~english
	 * Constant that condition of socket.
	 * @~japanese
	 * ソケット状態の定数
	 */
	enum EN_SOCKET_RECEIVE_STAT {
		RSTAT_SOP,
		RSTAT_HEADER,
		RSTAT_BODY,
		RSTAT_RECOVER,
		RSTAT_RECOVER_STEP2,
	};


private:
	SocketServer *_sock;
	//DataCollector *_collector;
	int _port_no;
	RczCommServerStatusHandler *_status_handler;
	RczCommServerMessageHandler *_callback_handler;
	RcControlCommandHandler *_callback_handler_rc;

	EN_SOCKET_RECEIVE_STAT _sock_receive_stat;
	RczHMsg _msg_header;
	uchar _report_image_id;
	uchar *_build_buff;

	RingBuffer *_msg_buffer;
	uchar *_msg_get_buff;
};

#endif /* RCZ_COMM_SERVER_H_ */




