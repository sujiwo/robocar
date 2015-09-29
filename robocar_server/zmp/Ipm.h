/**
 * @file
 *
 * @~english
 * @brief	Communication class header.
 *
 * @author	Masaki SegaWa
 *
 * @~japanese
 * @brief	画像処理ボードコントロールスクラスのヘッダ.
 *
 * @author	瀬川正樹
 *
 * @~
 * @date	 2009/04/02
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */


#ifndef IPM_H_
#define IPM_H_

#include "types.h"

namespace zmp {
	namespace zrc {


/**
 * @~english
 * Constant that specifies the type of algorithm.
 * @~japanese
 * アルゴリズムの種類指定する定数.
 */
enum IMAP_ALGORITHM_NAME {
	IMAP_ALG_NON = 0,
	/**
	 * @~english
	 * To　detect obstacles using stereo vision.
	 * @~japanese
	 * ステレオ視を使って障害物を検出するアルゴリズム｡レーン検出も同時に行う.
	 */
	IMAP_ALG_STEREO_OBSTACLES_1 = 1,
	/**
	 *
	 */
	//IMAP_ALG_STEREO_CAL,
};



/**
 * @~english
 * Exception of Ipm operations.
 * It throws by methods of the IpmControl class.
 * @~japanese
 * IPM操作の例外.
 * IpmControlのメソッドの例外として投げられる。
 */
class IpmException
{
public:
	/**
	 * @~english
	 * The result code.
	 * @~japanese
	 * エラーコード.
	 */
	enum IPM_RESULT_CODE {
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
		 * @~english		It failed Plx registers read.
		 * @~japanese		PLXのレジスタの読み込みに失敗した。。
		 */
		REGISTER_READ_FAILED,
		/**
		 * @~english		It failed Plx registers write.
		 * @~japanese		PLXのレジスタの書き込みに失敗した。
		 */
		REGISTER_WRITE_FAILED,
		/**
		 * @~english		Incorrect value of the register of the device.
		 * @~japanese		レジスタの値が正しくない。
		 */
		REGISTER_CHECK_NOT_MATCHED,
		/**
		 * @~english		It failed that mapping the device to local memory.
		 * @~japanese		デバイスのローカルメモリマッピングに失敗した。
		 */
		MAP_FAILED,
		/**
		 * @~english		It failed that read the object from file.
		 * @~japanese		ファイルからオブジェクトを読むのに失敗した。
		 */
		OBJECT_FILE_READ_FAILED,
		/**
		 * @~english
		 * @~japanese		割り込みのセットアップに失敗した。
		 */
		SETUP_INTERRUPT_FAILED,
		/**
		 * @~english
		 * @~japanese		ホストリクエストのウェイトの失敗。
		 */
		WAIT_NOTIFY_FAILED,
		/**
		 * @~english
		 * @~japanese		ビットマップファイルの読み込みに失敗。
		 */
		BITMAP_FILE_READ_FAILED,
		/**
		 * @~english
		 * @~japanese		タイムアウトした。
		 */
		TIMEOUT,
		/**
		 * @~english		This function not support yet.
		 * @~japanese		この機能はサポートしていない。
		 */
		NOT_SUPPORTED,
	};


public:
	/**
	 * Constructor.
	 * @~english
	 * @param		code
	 * @~japanese
	 * @param		code エラーコード
	 */
	IpmException(IPM_RESULT_CODE code);
	/**
	 * Destructor
	 */
	virtual ~IpmException();
public:
	/**
	 * @~english
	 * The error code that represent the cause of the exception.
	 * @~japanese
	 * 例外の原因を表すエラーコード.
	 */
	IPM_RESULT_CODE ErrorCode;

public:
	/**
	 * @~english
	 * Convert to string from error code.
	 * @return	A pointer of message string. It is internal constant area.
	 * @~japanese
	 * エラーコードを文字列に変換する.
	 * @return	メッセージ文字列の戦闘のポインタ。内部の定数エリアのポインタ。
	 */
	static const char *ToString(IPM_RESULT_CODE code);
};


	}
}


#endif /* IPM_H_ */
