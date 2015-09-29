/**
 * @file
 *
 * @~english
 * @brief	Image processor board control class header.
 *
 * @author	Masaki SegaWa
 *
 * @~japanese
 * @brief	画像処理ボードコントロールスクラスのヘッダ.
 *
 * @author	瀬川正樹
 *
 * @~
 * @date	2009-03-30
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#ifndef IPMCONTROL_H_
#define IPMCONTROL_H_


#include "Ipm.h"

#define SW_SRAMSEL 0



namespace zmp {
	namespace zrc {


class IpmDevice;
class ObjLoader;



/**
 * @~english
 * Image processor board control class.
 * This class functions as follows, reset the board, send the command, retrieve the status,
 * program loaded, obtain the result of image processing.
 * @~japanese
 * 画像処理ボードのコントロールクラス.
 * ボードのリセット、コマンドの送信、状態の取得、プログラムのロード、画像処理結果の取得などを行う。
 */
class IpmControl
{
private:
	enum IMAP_REGISTER_ADDRESS {
		#if SW_SRAMSEL
		IBASE =         0x3f00000,
		#else
		IBASE =         0x0700000,
		#endif
		IMAP_V0 = 	IBASE | 0xff130,
		IMAP_V1 = 	IBASE | 0xff134,
		IMAP_V2 = 	IBASE | 0xff138,
		IMAP_V3 = 	IBASE | 0xff13c,
		IMAP_V4 = 	IBASE | 0xff140,
		IMAP_V5 = 	IBASE | 0xff144,
		IMAP_V6 = 	IBASE | 0xff148,
		IMAP_V7 = 	IBASE | 0xff14c,
		IMAP_V8 = 	IBASE | 0xff150,
		IMAP_V9 = 	IBASE | 0xff154,
		IMAP_V9U = 	IBASE | 0xff156,
		IMAP_C21 = 	IBASE | 0xff054,
		IMAP_C22 = 	IBASE | 0xff058,
		IMAP_C23 = 	IBASE | 0xff05c,
		IMAP_C24 = 	IBASE | 0xff060,
		IMAP_C25 = 	IBASE | 0xff064,
		IMAP_PC = 	IBASE | 0xe5000,
		IMAP_RUNSTATE = IBASE | 0xff100,
		IMAP_BREAK = 	IBASE | 0xff104,
		IMAP_RESET = 	IBASE | 0xff10c,
		IMAP_ERROUT = 	IBASE | 0xe0004,
		IMAP_SSRAMSEL = IBASE | 0xe000c,
		IMAP_VINTMODE = IBASE | 0xe001c,
		IMAP_SRMODE = 	IBASE | 0xff0a8,
		IMAP_PEND = 	IBASE | 0xe0014,
		IMAP_DEND = 	IBASE | 0xe0018,
		IMAP_BER0 = 	IBASE | 0xff0a0,
		IMAP_BER1 = 	IBASE | 0xff0a4,
		IMAP_VLINES = 	IBASE | 0xff0d0,
		IMAP_PIXOFF = 	IBASE | 0xff0d4,
		IMAP_LINOFF = 	IBASE | 0xff0d8,
		IMAP_PIXPLN = 	IBASE | 0xff0dc,
		IMAP_P0 = 	IBASE | 0xff0ac,
		IMAP_PM0 = 	IBASE | 0xff0b4,
		IMAP_DCACHE = 	IBASE | 0xe1000,
		IMAP_PCACHE = 	IBASE | 0xe8000,
		IMAP_STACK = 	IBASE | 0xfe000,
		IMAP_SETUP =    IBASE | 0xff110,

		IMAPBASE = 	0x00000000,
		IMEMBASE = 	IBASE | 0x80000,
		IMEMSIZE = 	0x00040000,

		SRAM_0_BEG = 	0x00000000,
		SRAM_0_END = 	0x00400000,
		SRAM_1_BEG = 	0x01000000,
		SRAM_1_END = 	0x01400000,

		SUMWRITEADDR = 	0x013FFFFC,


		IMAP_HOST_BASE = 	0x03f00000,
		IMAP_SSRAMSEL_INI = 0x007e000c,

	};

	#define NOP			0x7e000000	/* g=0, m=0 */
	#define HALT			0xd7800000	/* g=1 */
	#define CNOP			0xff000000	/* g=0 */
	#define BRI			0xc5800000	/* g=1 */


public:
	/**
	 * Constructor.
	 */
	IpmControl();
	/**
	 * Destructor.
	 */
	virtual ~IpmControl();

public:
	/**
	 * @~english
	 * Initialze
	 * @~japanese
	 * 初期化.
	 */
	void Init() throw (IpmException);
	/**
	 * @~english
	 * Terminate.
	 * @~japanese
	 * 終了処理、後始末.
	 */
	void Term() throw (IpmException);
	/**
	 * @~english
	 * Reset.
	 * Reset the IPM. All state of the board and internal state of this object will initialized.
	 * @~japanese
	 * 初期化.
	 * IPMボードがリセットされ、このオブジェクト自身も初期化される。
	 */
	void Reset() throw (IpmException);
	/**
	 * @~english
	 *
	 *
	 * @~japanese
	 * 開始.
	 * IPMボードの処理開始。
	 */
	void Run() throw (IpmException);
	/**
	 * @~english
	 *
	 *
	 * @~japanese
	 * 開始.
	 * IPMボードプログラムを停止する。
	 */
	void Stop() throw (IpmException);
	/**
	 * @~english
	 * Load program binary to the IMAPCAR.
	 * It function load the firmware to the IMAPCAR processor on the IPM board.
	 * The IMAPCAR context is initialized.
	 * @~japanese
	 * IMAPPCARにプログラムをロードする.
	 * この関数で画像処理ボード上のIMAPCARにファームウェアを転送する。IMAPCARの内部状態は初期化される。
	 */
	void LoadProgram() throw (IpmException);

	/**
	 * @~english
	 * Load bitmap file from disk to IMAPCAR memory.
	 * It function load the data to the IMAPCAR processor on the IPM board.
	 * @~japanese
	 * IMAPPCARにビットマップデータをロードする.
	 * 画像データをIMACARメモリにロードする。レンズゆがみ補正用のデータ
	 * (画像データ)を転送するのに使用する。
	 * @param addr	転送先アドレス.
	 * @param filename	ファイル名
	 */
	void LoadBitmap(ulong addr, const char *filename) throw (IpmException);
	/**
	 * @~english
	 * Open and read the program binary file.
	 * @param alg The algorithm name. @see IMAP_ALGORITHM_NAME.
	 * @~japanese
	 * ファイルからプログラムを読み込む.
	 * @param alg 引数で指定されたアルゴリズムに相当するファイルを読み込む。
	 */
	void ReadProgramFile(IMAP_ALGORITHM_NAME alg) throw (IpmException);
	/**
	 * @~english
	 * Open and read the program binary file.
	 * @param path The algorithm file.
	 * @~japanese
	 * ファイルからプログラムを読み込む.
	 * @param path 引数で指定されたファイルを読み込む。
	 */
	void ReadProgramFile(const char *path) throw (IpmException);
	/**
	 * @~english
	 * @~japanese
	 * IMAPCARプログラムからホストリクエストが通知されるのを待つ.
	 * @param 	timeout_ms 	タイムアウト[ms]
	 * @return	時間内にホストリクエストの割り込みが検出されればtureで返る。
	 * 失敗するか、タイムアウトだとfalse.
	 */
	bool WaitNotify(ulong timeout_ms) throw (IpmException);
	/**
	 * @~english
	 * @~japanese
	 * IpmDeviceインスタンスへのポインタを返す.
	 */
	IpmDevice *GetDev();

protected:
	bool loadBitmap(ulong addr, const char *filename);
	void initImap();
	void writeImapProgram();
	void softResetImap();
	void runImap();
	void stopImap();
	void resetImap();
	void initDCache();
	void initPCache();
	void initStkm();
	void writeImapProg(ulong u4WriteAddr, const uchar* pu1DataBuff, ulong u4Size);
	void writeImapProg32(ulong u4WriteAddr, const uchar* pu1DataBuff, ulong u4Size);
	void writeImapProg3216(ulong u4WriteAddr, const uchar* pu1DataBuff, ulong u4Size);
	void writeImapProg16(ulong u4WriteAddr, const uchar* pu1DataBuff, ulong u4Size);
	void writeImapProgImem(ulong u4WriteAddr, const uchar* pu1DataBuff, ulong u4Size);
	ulong readImapMem32(ulong u4ReadAddr);
	void writeImapMem32(ulong u4WriteAddr, ulong u4Data);
	ushort readImapMem16(ulong u4ReadAddr);
	void writeImapMem16(ulong u4WriteAddr, ushort u2Data);
	uchar readImapMem8(ulong u4ReadAddr);
	void writeImapMem8(ulong u4WriteAddr, uchar u1WriteData);
	void fillHaltText();
	void fillBriText();
	void fillZeroDmem();
	void writeSumData();

private:
	IpmDevice *_dev;
	ObjLoader *_obj;

};




	}
}

#endif /* IPMCONTROL_H_ */


