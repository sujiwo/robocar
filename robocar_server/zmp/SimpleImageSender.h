/**
 * @file
 *
 * @~english
 * @brief	Host Communication class header.
 *
 * @author	Masaki SegaWa
 *
 * @~japanese
 * @brief	画像送信用UDP通信クラスヘッダ.
 *
 * @author	瀬川正樹
 *
 * @~
 * @date	 2009/09/10
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 *
 */

#ifndef __SIMPLE_IMAGE_SENDER_H__
#define	__SIMPLE_IMAGE_SENDER_H__

#include "socket.h"
#include  "types.h"



/**
 * @~english
 * @~japanese
 * 画像データの送信クラス.
 * UDPで実装した画像データ送信用のクラス。
 */
class SimpleImageSender
{
public:
	typedef enum {
		IS_FLAG_JPEG = 0x0001,
	} Flags;
public:
	/**
	 * Constructor.
	 */
	SimpleImageSender();
	/**
	 * Destructor.
	 */
	virtual ~SimpleImageSender();

public:
	/**
	 * @~english
	 * Initialze
	 * @~japanese
	 * 初期化.
	 * @param 	hostname 	送信先のホストを渡す。
	 * @param 	port_no 	使用するポート番号を指定する。
	 * @return	成功したかどうかを返す。
	 */
	bool Init(const char *hostname, int port_no);
	/**
	 * @~english
	 * @~japanese
	 * 送信するデータの情報をセットする。
	 * 画像データの情報をセットしておく。一度セットアップしておけば、連続してSendImage()してよい。
	 * @param 	ch チャンネル数　1か2。
	 * @param 	width 幅 1～640
	 * @param 	height 高さ 1～640
	 * @return	成功したかどうかを返す。
	 */
	bool SetupImage(int image_id, int ch, int width, int height);
	/**
	 * @~english
	 * @~japanese
	 * 送信するデータの情報をセットする。
	 * 画像データの情報をセットしておく。一度セットアップしておけば、連続してSendImage()してよい。
	 * @param 	ch チャンネル数　1か2。
	 * @param 	width 幅 1～640
	 * @param 	height 高さ 1～640
	 * @param	flag  1: jpeg 
	 * @return	成功したかどうかを返す。
	 */
	bool SetupImage(int image_id, int ch, int width, int height, int flag);
	/**
	 * @~english
	 * @~japanese
	 * 画像データ送信.
	 * 画像データの送信。
	 * @param 	image_data データの先頭アドレス
	 * @param 	length データ長さ[byted]
	 * @return	成功したかどうかを返す。
	 */
	bool SendImage(const uchar *image_data, int length);

private:
	 bool sendRawImage(const uchar *image_data, int length);
	 bool sendJpegImage(const uchar *image_data, int length);


private:
	SocketClientUDP *_sock;
	int _image_id;
	int _ch;
	int _height;
	int _width;

	bool _jpeg;
};



#endif

