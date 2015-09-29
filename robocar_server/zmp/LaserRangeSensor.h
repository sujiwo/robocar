/**
 * @file
 *
 * @~english
 * @brief	Laser range sensor class header.
 *
 * @author	Masaki SegaWa
 *
 * @~japanese
 * @brief	レーザーレンジセンサクラスヘッダ.
 *
 * @author	瀬川正樹
 *
 * @~
 * @date	2009-03-26
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#ifndef LASERRANGESENSOR_H_
#define LASERRANGESENSOR_H_

#include <pthread.h>
extern "C" {
#include "urg_ctrl.h"
}


namespace zmp {
	namespace zrc {


class CRingBuffer;

/**
 * @~english
 * Exception of Ipm operations.
 * It throws by methods of the IpmControl class.
 * @~japanese
 * IPM操作の例外.
 * IpmControlのメソッドの例外として投げられる。
 */
class LrsException
{
public:
	/**
	 * @~english
	 * The result code of operation of Laser range sensor.
	 * @~japanese
	 * レーザーレンジセンサのエラーコード.
	 */
	enum LRS_RESULT_CODE {
		/**
		 * @~english		Operation successfully finished.
		 * @~japanese		成功したことを示す。
		 */
		SUCCESS,
		/**
		 * @~english		Device open error. This error means the does not find the device or no drivers are loaded properly.
		 * @~japanese		デバイスがオープンできない。デバイスが認識できないか、ドライバが正しくロードできなかったことを示す。
		 */
		CAN_NOT_OPEN_DEVICE,
		/**
		 * @~english		Parameter set failed.
		 * @~japanese		デバイスへのパラメータ設定に失敗した。
		 */
		SET_PARAMETER_FAILED,
		/**
		 * @~english		Data requesterror.
		 * @~japanese		データ取得のリクエストに失敗した。
		 */
		REQUEST_DATA_FAILED,

		/**
		 * @~english		This function not support yet.
		 * @~japanese		この機能はサポートしていない。
		 */
		NOT_SUPPORTED,
	};
};






/**
 * @~english
 * Laser range sensor message handler interface.
 * This is pure virtual class. It provides the callback method of receiving data from the LRS.
 * @~japanese
 * レーザーレンジセンサメッセージハンドラインターフェイス
 * 仮想クラス。LRSからのデータ受信時のコールバックメソッドを提供する。
 */
class LaserRangeSensorReceiveHandler {
public:
	virtual void OnReceive() = 0;
	//virtual void OnError() = 0;
};

#define LSR_RESULT_MAX_DATA_LENGTH 1000

struct LrsResult {
	unsigned long magic;
	long timestamp;
	int data_length;
	double	angle[LSR_RESULT_MAX_DATA_LENGTH];
	long	data[LSR_RESULT_MAX_DATA_LENGTH];
};


/**
 * @~english
 * Laser range sensor class.
 * This class provide to access the laser range sensor.
 * @~japanese
 * レーザーレンジセンサクラス.
 * レーザーレンジセンサのアクセスクラス。
 * @~
 * Example 1: Polling.
 * @code
LaserRangeSensor lrs; // The instance.

lrs.Init(); // must initialize.
lrs.Start(); // Start device and receive thread here.
int cnt = 0;
while (cnt <= 10) {
	LrsResult res;
	if (lrs.GetData(&res)) { // Read the data if exist.
		printf("data_length = %d\n", res.data_length);
		printf("timestamp = %ld\n", res.timestamp);
		for (int i = 0; i < res.data_length; i++) {
			printf("%d %lf %ld\n", i, res.angle[i], res.data[i]);
		}
		cnt++;
	}
}
lrs.Stop(); // Stop the device and receive thread.
 * @endcode
 * Example 2: Callback.
 * @code
class UserApp : public LaserRangeSensorReceiveHandler // Inherit handler class.
{
public:
	UserApp() : _b_on_receive(false) {};
	~UserApp(){};
	void main() {
		_lrs.Init();
		_lrs.SetReceiveHander(this); // Register the callback handler.
		_lrs.Start(); // Start device and receive thread here.
		int cnt = 0;
		while (cnt < 10) {
			if (_b_on_receive) {
				_b_on_receive = false;
				LrsResult res;
				if (_lrs.GetData(&res)) {
					printf("data_length = %d\n", res.data_length);
					printf("timestamp = %ld\n", res.timestamp);
					//for (int i = 0; i < res.data_length; i++) {
					//	printf("%d %d %lf %ld\n", cnt, i, res.angle[i], res.data[i]);
					//}
					cnt++;
				}
			}
		}
		_lrs.Stop();
	}
	// Thi is call back method.
	// NOTE! It runs in the receive thread context.
	void OnReceive() {
		_b_on_receive = true;
	}
private:
	LaserRangeSensor _lrs; // The instance.
	bool _b_on_receive;
};
 * @endcode
 *
 */
class LaserRangeSensor
{

public:
	/**
	 * Constructor.
	 */
	LaserRangeSensor();
	/**
	 * Constructor.
	 * @~english
	 * with buffer depth.
	 * @~japanese
	 * バッファの深さ指定。
	 */
	LaserRangeSensor(int buffer_depth);
	/**
	 * Destructor.
	 */
	virtual ~LaserRangeSensor();

public:
	/**
	 *
	 */
	void Test();
	/**
	 * @~english
	 * Initialize all.
	 * Initialize the object and device.
	 * @~japanese
	 * 初期化.クラスとデバイスを初期化する。
	 */
	bool Init();

	/**
	 * @~english
	 * Initialize all.
	 * Initialize the object and device.
	 * Set skip line num.
	 * @param[in]	skip_line	Skip line num.
	 * @~japanese
	 * 初期化.クラスとデバイスを初期化する.
	 * 取得データの間引き数を設定する.
	 * @param[in]	skip_line	取得データの間引き数.
	 */
	bool Init(int skip_line);

	/**
	 * @~english
	 * Register the receive callback handler.
	 * @param[in]		handler The callback class that inherited the interface LaserRangeSensorReceiveHandler.
	 * @~japanese
	 * 受信用のコールバックハンドラを登録する.
	 * @param[in]		handler コールバックされるクラス.LaserRangeSensorReceiveHandlerインターフェイスを継承する。
	 */
	void SetReceiveHander(LaserRangeSensorReceiveHandler *handler);
	/**
	 * @~english
	 * Start the device and begin the receive thread.
	 * @~japanese
	 * デバイスの測定動作の開始と、受信スレッドの開始.
	 */
	bool Start();
	/**
	 * @~english
	 * Stop the device and finish the receive thread and wait the thread end.
	 * @~japanese
	 * デバイスと受信スレッドを停止.
	 */
	bool Stop();
	/**
	 * @~english
	 * Get the result from buffer.
	 * @param[out]		res Area to store the result
	 * @retval	true	There are data and got well.
	 * @retval	false	There is no data.
	 * @~japanese
	 * バッファから結果の取得.
	 * @param[out]		res 結果をストアする領域。
	 * @retval	true	データ取得成功。
	 * @retval	false	データなし。
	 */
	bool GetData(LrsResult *res);

protected:
	/**
	 * @~english
	 * Reciver thread.
	 * @~japanese
	 * デバイスからの入力を監視しコールバックするスレッド.
	 */
	void ReceiveThread();
	/**
	 * @~english
	 * The entrypoint of thread.
	 * @param[in]		arg myself.
	 * @~japanese
	 * スレッドエントリー
	 * @param[in]		arg 自分を渡す.
	 */
	static void *ReceiveThreadEntry(void *arg);

	bool connectDevice();
	bool setupDevice();
	int getLengthDevice();
	void disconnectDevice();

private:
	urg_t  				*_urg;
	CRingBuffer			*_rcvBuffer;
	int 					_data_length_a_scan;
	int						_buffer_depth;
	LrsException::LRS_RESULT_CODE _err_code;

	pthread_t 			_receive_thread;
	bool 					_b_active_thread;
	bool					_b_connect;
	bool					_b_req_stop_thread;

	static const int 	_DEFAULT_BUFFER_DEPTH;
	static const char 	*_DEVICE_NAME;
	static const long 	_BAUDRATE;
	LaserRangeSensorReceiveHandler	*_callback_handler;

};




	} // namespace zrc
} // namespace zmp

#endif /* RASERRANGESENSOR_H_ */
