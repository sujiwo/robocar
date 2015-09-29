/**
 * @file
 *
 * @~english
 * @brief	RC IMAP program object reader class header.
 *
 * @author	Masaki SegaWa
 *
 * @~japanese
 * @brief	RCのIMAPプログラムローダクラス　ヘッダ
 *
 * @author	瀬川正樹
 *
 * @~
 * @date	 2009/04/01
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#ifndef OBJLOADER_H_
#define OBJLOADER_H_


#include "Ipm.h"

namespace zmp {
	namespace zrc {



/**
 * @~english
 * Object loader class.
 * Load from file (*.ro)
 * @~japanese
 * オブジェクトローダ.
 * ファイルからオブジェクトファイル(*.ro)を読み込む。
 */
class ObjLoader
{
	/**
	 * @~english
	 * Class IpmControl can access me fully.
	 * @~japanese
	 * IpmControlクラスからはこのクラスの内部すべてにアクセスできる.
	 */
	friend class IpmControl;

private:
	/**
	 * @~english
	 * Object file header.
	 * @~japanese
	 * オブジェクトファイルヘッダ.
	 */
	struct RcobjHeader {
		unsigned long	magic;
		char title[32];
		unsigned long	ver;
		unsigned long	offset;
		unsigned long	size;
		unsigned char	padding[128 - (32 + sizeof(unsigned long) * 4)];
	} __attribute__ ((packed));


public:
	/**
	 * Constructor
	 */
	ObjLoader();
	/**
	 * Destructor
	 */
	virtual ~ObjLoader();
public:
	/**
	 * @~english
	 * Load object from file.
	 * Load the binary object from file depend on specified name in argument.
	 * @param[in]		fname The file name of the object file.
	 * @retval	true Successful.
	 * @retval	fail Failed. The file could not open or format incorrect.
	 * @~japanese
	 * ファイルからオブジェクトを読み込む.
	 * @param[in]		fname オブジェクトファイル名
	 * @retval	true 成功
	 * @retval	false 失敗. ファイルが開けないか、ファイルフォーマットが間違っている。
	 */
	bool LoadFromFile(const char *fname);

private:
	/**** CODE SIZE ***/
	unsigned long _TEXT_SIZE;
	unsigned long _IDATA_SIZE;
	unsigned long _DDATA_SIZE;
	unsigned long _EDATA_SIZE;
	unsigned long _IBSS_SIZE;
	unsigned long _DBSS_SIZE;
	unsigned long _EBSS_SIZE;

	/**** CODE ADDRESS ***/
	unsigned long _TEXT_ADDR;
	unsigned long _IDATA_ADDR;
	unsigned long _DDATA_ADDR;
	unsigned long _EDATA_ADDR;
	unsigned long _IBSS_ADDR;
	unsigned long _DBSS_ADDR;
	unsigned long _EBSS_ADDR;

	/**** CODE DATA ***/
	unsigned char *_TEXT;
	unsigned char *_IDATA;
	unsigned char *_DDATA;
	unsigned char *_EDATA;

	/**** STARTING INFO ***/
	unsigned long _V0;
	unsigned long _V1;
	unsigned long _V2;
	unsigned long _V3;
	unsigned long _V4;
	unsigned long _V5;
	unsigned long _V6;
	unsigned long _V7;
	unsigned long _V8;
	unsigned long _V9;
	unsigned long _C25;
	unsigned long _C24;
	unsigned long _C21;
	unsigned long _C23;
	unsigned long _C22;
	unsigned long _PC;
	unsigned long _PEND;
	unsigned long _DEND;
};







	}
}

#endif /* OBJLOADER_H_ */
