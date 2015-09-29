/**
 * @file
 *
 * @~english
 * @brief
 *
 * @author	Masaki SegaWa
 *
 * @~japanese
 * @brief		IPMボードシリアル通信のマネージクラス　ヘッダ
 *
 * @author	瀬川正樹
 *
 * @~
 * @date	2009-07-01
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */


#ifndef __IPM_SERIAL_H__
#define __IPM_SERIAL_H__

#include "types.h"

#include <termios.h>
#include <unistd.h>

namespace zmp {
	namespace zrc {


/**
 * @namespace zmp
 * @~english
 * @~japanese
 * 外部プログラム"ipm_serial"を内部から使いやすくするためのラッパクラス.
 */
class IpmSerial
{
public:
	/**
	 * @~english
	 *
	 * @~japanese
	 * リセット('R'コマンド)のパラメータ値の定義.
	 */
	enum {
		/**
		 * @~english
		 * @~japanese		IMAPのリセット
		 */
		IPM_RESET_IMAP = 0x01,
		/**
		 * @~english
		 * @~japanese		PCIリセット
		 */
		IPM_RESET_PCI  = 0x02,
		/**
		 * @~english
		 * @~japanese		ビデオ系のリセット
		 */
		IPM_RESET_VD12 = 0x04,
		/**
		 * @~english
		 * @~japanese		PCボードのリセット
		 */
		IPM_RESET_PC   = 0x08,
	};
	/**
	 * @~english
	 *
	 * @~japanese
	 * 電源管理('S'コマンド)のパラメータ値1の定義.
	 */
	enum {
		/**
		 * @~english
		 * @~japanese		レーザーレンジセンサ(5V or 12V)
		 */
		IPM_POWCONT_LRF  = 0x01,
		/**
		 * @~english
		 * @~japanese
		 */
		IPM_POWCONT_A12V = 0x02,
		/**
		 * @~english
		 * @~japanese		ベースボード
		 */
		IPM_POWCONT_BASE = 0x04,
		/**
		 * @~english
		 * @~japanese		IMAPCARプロセッサ
		 */
		IPM_POWCONT_IMAP = 0x08,
	};
	/**
	 * @~english
	 *
	 * @~japanese
	 * 電源管理('S'コマンド)のパラメータ値2の定義.
	 */
	enum {
		/**
		 * @~english
		 * @~japanese		電源をONする
		 */
		IPM_POWCOMMAND_ON  = 0x01,
		/**
		 * @~english
		 * @~japanese		電源をOFFする
		 */
		IPM_POWCOMMAND_OFF = 0x00,
	};

public:
	/**
	 * Constructor.
	 */
	IpmSerial();
	/**
	 * Destructor.
	 */
	virtual ~IpmSerial();

public:
	/**
	 * @~english
	 *
	 * @~japanese
	 * リセットコマンドを送信する.
	 * @param		flags	リセットする対象のbitを立てる。
	 */
	bool SendReset(uchar flags);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 電源コントロールコマンドの送信.
	 * @param		flags	電源管理コマンド送信対象のbitを立てる。
	 * @param		cmd		ONかOFFを指定する。
	 */
	bool SendPowerControl(uchar flags, int cmd);
	/**
	 * @~english
	 *
	 * @~japanese
	 * ビデオデコーダ(NTSCデコーダ)へのパラメータ設定の送信.
	 * @param		ch		LchかRchかを指定。
	 * @param		addr	レジスタアドレスを指定。
	 * @param		data	セットする値.
	 */
	bool SendVideoDecoderParams(int ch, uchar addr, uchar data);

protected:
	uchar sum(uchar *p, int n);
	bool sendMessage(uchar *msg, int length);
	bool openDevice();
	bool closeDevice();

private:
	int _fd;
	struct termios _oldtio;

	static const char *_dev_name;


};

	}

}

#endif



