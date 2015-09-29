/**
 * @file
 *
 * @~english
 * @brief	Image processor board interface class header.
 *
 * @author	Masaki SegaWa
 *
 * @~japanese
 * @brief	画像処理ボードインターフェイスクラスのヘッダ.
 *
 * @author	瀬川正樹
 *
 * @~
 * @date	2009-03-26
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#ifndef IPMDEVICE_H_
#define IPMDEVICE_H_

#include "types.h"

#include "Ipm.h"



#define SW_NOT_SUPPORT_8 1



struct _PLX_DEVICE_KEY;
struct _PLX_DEVICE_OBJECT;
struct _PLX_NOTIFY_OBJECT;

/**
 * @namespace zmp
 * @~english
 * @brief	The namespace zmp. It's from ZMP Inc.
 * @~japanese
 * @brief	ZMP Inc.　のトップレベル
 */
namespace zmp {
	/**
	 * @namespace zmp::zrc
	 * @~english
	 * @brief	The RC-Z project's namespace.
	 * @~japanese
	 * @brief	RC-Zプロジェクト
	 */
	namespace zrc {




/**
 * @~english
 * Image processor board interface class.
 * This class provide the interfaces to the Image processor board.
 * It requires the kernel mode device driver 'Plx9030.ko'.
 * To access to the device, the class uses PlxApi library internally that linked statically.
 * @~japanese
 * 画像処理ボードへインターフェイスクラス.
 * 画像処理ボードへのインターフェイスを提供する。
 * この機能を利用するには、デバイスドライバ'Plx9030.ko'がインストールされている必要がある。
 * デバイスにアクセスするために、クラスの内部で、静的にリンクさPlxApiライブラリを使用している。
 *
 * ReqdX/WriteXのアクセスメソッドは、上位のアクセスメソッドである。必要に応じてベースアドレスを変更して
 * 値を読み書きする。IMAPボード内のすべてのアドレス空間が対象。
 *
 * ReadFromDeviceX/WriteToDeviceXメソッドは、下位のアクセスメソッドである。
 * 設定されているベースアドレスにより、実際に読み書きするデバイスアドレスは異なる。
 * 指定できるアドレスは、0x0～0x00100000の範囲である。ベースアドレスからのオフセットが実デバイスアドレスとなる。
 *
 */
class IpmDevice {
public:

private:
	/**
	 * @~english
	 * The set of address and value of PLX registers. It used internal only.
	 * @~japanese
	 * PLXのアドレスと値のセット.内部で使用される。
	 */
	struct PlxRegSet {
		uchar offset;
		ulong value;
	};

public:
	/**
	 * Constructor.
	 */
	IpmDevice();
	/**
	 * Destructor.
	 */
	virtual ~IpmDevice();

public:
	/**
	 * @~english
	 * Initialize.
	 * Initialize all of internal data and device driver.
	 * @retval	true It nitialized successful.
	 * @retval	false Failed.
	 * @~japanese
	 * 初期化.
	 * オブジェクト内部と、デバイスドライバを初期化する。
	 * @retval	true 初期化成功
	 * @retval	false  失敗
	 */
	bool Init();
	/**
	 * @~english
	 * Terminate.
	 * Terminate the device communication.
	 * @retval	true It nitialized successful.
	 * @retval	false Failed.
	 * @~japanese
	 * 終了処理.
	 * デバイスとの通信を終了する。
	 * @retval	true 初期化成功
	 * @retval	false  失敗
	 */
	bool Term();
	/**
	 * @~english
	 *  Return the error code last occurred.
	 *  @return	@see IPM_RESULT_CODE
	 * @~japanese
	 *  最後に発生したエラーコードを返す。
	 *  @return	@see IPM_RESULT_CODE
	 */
	IpmException::IPM_RESULT_CODE GetLastErrorCode() const;
	/**
	 * @~english
	 * @~japanese
	 * IMAPCARプログラムからホストリクエストが通知されるのを待つ.
	 * @param 	timeout_ms 	タイムアウト[ms]
	 * @return	時間内にホストリクエストの割り込みが検出されればtureで返る。
	 * 失敗するか、タイムアウトだとfalse.
	 */
	bool WaitNotify(ulong timeout_ms);
	/**
	 * @~english
	 * Setup the base adddress.
	 * @param		addr Device base address.
	 * @~japanese
	 * ベースアドレスを指定する。
	 * @param		addr デバイスアドレス
	 */
	bool SetBaseAddress(ulong addr);

	/**
	 * @~english
	 *
	 * @~japanese
	 * 32bitデータを指定されたアドレスに書き込む.
	 * @param		addr デバイスアドレス
	 * @param		data 値
	 */
	void Write32(ulong addr, ulong data);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 32bitデータを指定されたアドレスから読み込む.
	 * @param		addr デバイスアドレス
	 * @return	読み込んだ値
	 */
	ulong Read32(ulong addr);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 16bitデータを指定されたアドレスに書き込む.
	 * @param		addr デバイスアドレス
	 * @param		data 値
	 */
	void Write16(ulong addr, ushort data);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 16bitデータを指定されたアドレスから読み込む.
	 * @param		addr デバイスアドレス
	 * @return	読み込んだ値
	 */
	ushort Read16(ulong addr);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 8bitデータを指定されたアドレスに書き込む.
	 * @param		addr デバイスアドレス
	 * @param		data 値
	 */
	void Write8(ulong addr, uchar data);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 8bitデータを指定されたアドレスから読み込む.
	 * @param		addr デバイスアドレス
	 * @return	読み込んだ値
	 */
	uchar Read8(ulong addr);

	/**
	 * @~english
	 *
	 * @~japanese
	 * 32bitデータを指定されたアドレスに書き込む.lengthは書き込むデータの長さ(byte数ではない)。
	 * @param		addr デバイスアドレス
	 * @param		pData 書き込む値の先頭ポインタ
	 * @param		length データ長
	 */
	void Write32(ulong addr, const ulong *pData, int length);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 32bitデータを指定されたアドレスにから読み込む.lengthは読み込むデータの長さ(byte数ではない)。
	 * @param		addr デバイスアドレス
	 * @param		pData 取得した値をストアす領域
	 * @param		length データ長
	 */
	void Read32(ulong addr, ulong *pData, int length);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 16bitデータを指定されたアドレスに書き込む.lengthは書き込むデータの長さ(byte数ではない)。
	 * @param		addr デバイスアドレス
	 * @param		pData 書き込む値の先頭ポインタ
	 * @param		length データ長
	 */
	void Write16(ulong addr, const ushort *pData, int length);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 16bitデータを指定されたアドレスにから読み込む.lengthは読み込むデータの長さ(byte数ではない)。
	 * @param		addr デバイスアドレス
	 * @param		pData 取得した値をストアす領域
	 * @param		length データ長
	 */
	void Read16(ulong addr, ushort *pData, int length);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 8bitデータを指定されたアドレスに書き込む.lengthは書き込むデータの長さ。
	 * @param		addr デバイスアドレス
	 * @param		pData 書き込む値の先頭ポインタ
	 * @param		length データ長
	 */
	void Write8(ulong addr, const uchar *pData, int length);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 8bitデータを指定されたアドレスにから読み込む.lengthは読み込むデータの長さ。
	 * @param		addr デバイスアドレス
	 * @param		pData 取得した値をストアす領域
	 * @param		length データ長
	 */
	void Read8(ulong addr, uchar *pData, int length);

	/**
	 * @~english
	 * Write data to specified address of the IPM device.
	 * @param		offset Device address.
	 * @param		data Value to write.
	 * @~japanese
	 * デバイスに値を書き込む。アドレスと書き込むデータへのバッファを指定する。
	 * @param		offset デバイスアドレス
	 * @param		data 書き込む値
	 */
	void WriteToDevice8(ulong offset, uchar data);
	/**
	 * @~english
	 * Read data from specified address of the IPM device.
	 * @param		offset Device address.
	 * @return 	Value red from device.
	 * @~japanese
	 * デバイスから値を読み込む。アドレスを指定する。
	 * @param		offset デバイスアドレス
	 * @return	デバイスから読んだ値を返す。
	 */
	uchar ReadFromDevice8(ulong offset);
	/**
	 * @~english
	 * Write data to specified address of the IPM device.
	 * @param		addr Device address.
	 * @param		data Value to write.
	 * @~japanese
	 * デバイスに値を書き込む。アドレスと書き込むデータへのバッファを指定する。
	 * @param		addr デバイスアドレス
	 * @param		data 書き込む値
	 */
	void WriteToDevice16(ulong addr, ushort data);
	/**
	 * @~english
	 * Read data from specified address of the IPM device.
	 * @param		addr Device address.
	 * @return 	Value red from device.
	 * @~japanese
	 * デバイスから値を読み込む。アドレスを指定する。
	 * @param		addr デバイスアドレス
	 * @return	デバイスから読んだ値を返す。
	 */
	ushort ReadFromDevice16(ulong addr);
	/**
	 * @~english
	 * Write data to specified address of the IPM device.
	 * @param		addr Device address.
	 * @param		data Value to write.
	 * @~japanese
	 * デバイスに値を書き込む。アドレスと書き込むデータへのバッファを指定する。
	 * @param		addr デバイスアドレス
	 * @param		data 書き込む値
	 */
	void WriteToDevice32(ulong addr, ulong data);
	/**
	 * @~english
	 * Read data from specified address of the IPM device.
	 * @param		addr Device address.
	 * @return 	Value red from device.
	 * @~japanese
	 * デバイスから値を読み込む。アドレスを指定する。
	 * @param		addr デバイスアドレス
	 * @return	デバイスから読んだ値を返す。
	 */
	ulong ReadFromDevice32(ulong addr);

	/**
	 * @~english
	 * Write data to specified address of the IPM device.
	 * @param		offset Device address.
	 * @param[in]		pData Pointer to data.
	 * @param		length Length of data.
	 * @~japanese
	 * デバイスに値を書き込む。アドレスと書き込むデータへのバッファを指定する。
	 * @param		offset デバイスアドレス
	 * @param[in]		pData 書き込むデータのアドレス
	 * @param		length データのバイト数
	 */
	void WriteToDevice8(ulong offset, const uchar *pData, int length);
	/**
	 * @~english
	 * Read data from specified address of the IPM device.
	 * @param		offset Device address.
	 * @param[out]		pData Pointer to data.
	 * @param		length Length of data.
	 * @~japanese
	 * デバイスから値を読み込む。アドレスとデータをストアするアドレスを指定する。
	 * @param		offset デバイスアドレス
	 * @param[out]		pData データ保存先のアドレス
	 * @param		length データのバイト数
	 */
	void ReadFromDevice8(ulong offset, uchar *pData, int length);
	/**
	 * @~english
	 * Write data to specified address of the IPM device.
	 * @param		addr Device address.
	 * @param[in]		pData Pointer to data.
	 * @param		length Length of data.
	 * @~japanese
	 * デバイスに値を書き込む。アドレスと書き込むデータへのバッファを指定する。
	 * @param		addr デバイスアドレス
	 * @param[in]		pData 書き込むデータのアドレス
	 * @param		length データのバイト数
	 */
	void WriteToDevice16(ulong addr, const ushort *pData, int length);
	/**
	 * @~english
	 * Read data from specified address of the IPM device.
	 * @param		addr Device address.
	 * @param[out]		pData Pointer to data.
	 * @param		length Length of data.
	 * @~japanese
	 * デバイスから値を読み込む。アドレスとデータをストアするアドレスを指定する。
	 * @param		addr デバイスアドレス
	 * @param[out]		pData データ保存先のアドレス
	 * @param		length データのバイト数
	 */
	void ReadFromDevice16(ulong addr, ushort *pData, int length);
	/**
	 * @~english
	 * Write data to specified address of the IPM device.
	 * @param		addr Device address.
	 * @param[in]		pData Pointer to data.
	 * @param		length Length of data.
	 * @~japanese
	 * デバイスに値を書き込む。アドレスと書き込むデータへのバッファを指定する。
	 * @param		addr デバイスアドレス
	 * @param[in]		pData 書き込むデータのアドレス
	 * @param		length データのバイト数
	 */
	void WriteToDevice32(ulong addr, const ulong *pData, int length);
	/**
	 * @~english
	 * Read data from specified address of the IPM device.
	 * @param		addr Device address.
	 * @param[out]		pData Pointer to data.
	 * @param		length Length of data.
	 * @~japanese
	 * デバイスから値を読み込む。アドレスとデータをストアするアドレスを指定する。
	 * @param		addr デバイスアドレス
	 * @param[out]		pData データ保存先のアドレス
	 * @param		length データのバイト数
	 */
	void ReadFromDevice32(ulong addr, ulong *pData, int length);


protected:
	/**
	 * @~english
	 * Open the IPM device.
	 * @retval	true Success.
	 * @retval	false Failed. To know the cause, see the error code.
	 * @~japanese
	 * デバイスをオープンする.
	 * @retval	true 成功.
	 * @retval	false 失敗。原因を知るためにはエラーコードを参照する.
	 */
	bool openDevice();
	/**
	 * @~english
	 * Set initial value to registers of IMAPCAR
	 * @retval	true Success.
	 * @retval	false Failed. To know the cause, see the error code.
	 * @~japanese
	 * 初期値をレジスタにセットする.
	 * @retval	true 成功.
	 * @retval	false 失敗。原因を知るためにはエラーコードを参照する.
	 */
	bool setupDevice();
	/**
	 * @~english
	 * Map the device address to virtual local address.
	 * @retval	true Success.
	 * @retval	false Failed. To know the cause, see the error code.
	 * @~japanese
	 * デバイスをローカルアドレスにマップする.
	 * @retval	true 成功.
	 * @retval	false 失敗。原因を知るためにはエラーコードを参照する.
	 */
	bool setInterrupt();
	/**
	 * @~english
	 * Map the device address to virtual local address.
	 * @retval	true Success.
	 * @retval	false Failed. To know the cause, see the error code.
	 * @~japanese
	 * デバイスをローカルアドレスにマップする.
	 * @retval	true 成功.
	 * @retval	false 失敗。原因を知るためにはエラーコードを参照する.
	 */
	bool mapDevice();

	/**
	 * @~english
	 * Unmap the device memory.
	 * @~japanese
	 * ローカルにマップしたデバイスのメモリを開放する。
	 */
	void unmapDevice();
	bool isInRange(ulong addr);
	bool setBaseAddress(ulong addr);
	/**
	 * @~english
	 * Close the device.
	 * @~japanese
	 * デバイスをクローズする.
	 */
	void closeDevice();

private:
	const static PlxRegSet	setup_config_reg_table[];
	const static PlxRegSet	verify_pci_reg_table[];

	_PLX_DEVICE_KEY			*_device_key;
	_PLX_DEVICE_OBJECT		*_device;
	//PLX_INTERRUPT			*_interrupt;
	_PLX_NOTIFY_OBJECT		*_notify_object;

	enum IpmException::IPM_RESULT_CODE	_err_code;
	uchar 				*_Va;

	ulong				_base_addr;
};



	}
}

#endif /* IPMDEVICE_H_ */


