/**
 * @file
 *
 * @~english
 * @brief	Communication class header.
 *
 * @author	Masaki SegaWa
 *
 * @~japanese
 * @brief	画像処理モジュール上のプログラムのコントロールクラス　ヘッダ
 *
 * @author	瀬川正樹
 *
 * @~
 * @date	2009-06-30
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 */

#ifndef __IPM_MANAGER_H__
#define __IPM_MANAGER_H__

#include "types.h"
#include "Ipm.h"


namespace zmp {
	namespace zrc {


class IpmControl;
class IpmDevice;
class IpmSerial;

/**
 * @~english
 *
 * @~japanese
 * ステレオ処理アルゴリズムへ与える外部パラメータのID.
 */
enum STEREO_ALG_PARAM_ID {
	/**
	 * @~english
	 *
	 * @~japanese
	 *
	 */
	SPI_NON = 0,
	/**
	 * @~english
	 *
	 * @~japanese
	 * レーン検出の入力チャンネル. 0で左チャンネル1で右チャンネルの入力を使用する。
	 */
	SPI_LANE_INPUT_CH = 1,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 白線検出に用いる二値化の閾値.
	 */
	SPI_LANE_BIN_TH,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 白線検出に用いる面積に対する閾値.二値化後の白色の画素の面積で、この値より小さな領域はノイズとみなす。
	 */
	SPI_LANE_NUN_TH,
	/**
	 * @~english
	 *
	 * @~japanese
	 * ブロックマッチングの相関度に対する閾値.
	 * ブロック内の輝度差の総和(Sum of Absolute Difference)がこの値より小さいときにマッチしたとみなす。
	 */
	SPI_STEREO_SAD_TH,
	/**
	 * @~english
	 *
	 * @~japanese
	 * ブロックマッチングのエッジ量に対する閾値.
	 * ブロック内の隣接画素間の差分の和がこの値より大きいときに、結果を採用する。
	 */
	SPI_STEREO_EDGE_TH,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 有効視差範囲のシフト. 最大視差量を制限するかわりに、サブピクセルを使用して、有効距離を変化させる。未実装。
	 */
	SPI_STEREO_DIS_SHIFT,
	/**
	 * @~english
	 *
	 * @~japanese
	 * ヒストグラム処理の計算開始位置Y0.スクリーン座標。Y位置と範囲を指定することで、注目しない画面範囲を無視することができる。
	 */
	SPI_HISTOGRAM_Y0,
	/**
	 * @~english
	 *
	 * @~japanese
	 * ヒストグラム処理の計算終了位置Y0.スクリーン座標。Y位置と範囲を指定することで、注目しない画面範囲を無視することができる。
	 */
	SPI_HISTOGRAM_Y1,
	SPI_FILTER_C1,
	SPI_FILTER_C2,
	SPI_FILTER_C3,
	SPI_FILTER_C4,
	SPI_FILTER_C5,
	/**
	 * @~english
	 *
	 * @~japanese
	 * フィルタ係数の指定.
	 * <table>
	 * <tr><td>C6</td><td>C5</td><td>C4</td><td>C5</td><td>C6</td></tr>
	 * <tr><td>C5</td><td>C3</td><td>C2</td><td>C3</td><td>C5</td></tr>
	 * <tr><td>C4</td><td>C2</td><td>C1</td><td>C2</td><td>C4</td></tr>
	 * <tr><td>C5</td><td>C3</td><td>C2</td><td>C3</td><td>C5</td></tr>
	 * <tr><td>C6</td><td>C5</td><td>C4</td><td>C5</td><td>C6</td></tr>
	 * </table>
	 */
	SPI_FILTER_C6,
	/**
	 * @~english
	 *
	 * @~japanese
	 * フィルタ係数の倍率指定.
	 */
	SPI_FILTER_K,
	/**
	 * @~english
	 *
	 * @~japanese
	 * ハフ変換の前処理に用いる二値化閾値の設定.
	 */
	SPI_HOUGH_BIN_TH,
	/**
	 * @~english
	 *
	 * @~japanese
	 * ハフ変換で求められる直線の有効線長に対する閾値.
	 */
	SPI_HOUGH_MIN_COUNT,
	/**
	 * @~english
	 *
	 * @~japanese
	 * ハフ変換で求められる全体の線長に対する閾値.
	 */
	SPI_HOUGH_MIN_LENGTH,
	/**
	 * @~english
	 *
	 * @~japanese
	 * ハフ変換における、線分の途切れの長さに対する閾値.
	 */
	SPI_HOUGH_MAX_BREAK,
	/**
	 * @~english
	 *
	 * @~japanese
	 * ラベリングの前処理に用いる二値化閾値の設定.
	 */
	SPI_LABEL_BIN_TH,
	/**
	 * @~english
	 *
	 * @~japanese
	 * ラベリング時のノイズ除去閾値. ラベル付けを行う前の二値画像に対して指定回数の収縮処理を行う。
	 */
	SPI_LABEL_NOISE_TH,
	/**
	 * @~english
	 *
	 * @~japanese
	 * ラベリング時のラベル連結強度の設定. ラベル付けを行う前の二値画像に対して指定回数の膨張処理を行う。
	 */
	SPI_LABEL_DILATION,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 検出するオブジェクトの最小幅. ラベル付けされたオブジェクトに対して、Ｘ方向のサイズによりフィルタリングを行う。
	 */
	SPI_LABEL_MIN_WIDTH,
	SPI_STEREO_DIS_OFFSET, 
	SPI_STEREO_PRE_FILTER,
};

/**
 * @~english
 *
 * @~japanese
 * ステレオ処理アルゴリズムからの出力イメージを表すID.
 */
enum STEREO_ALG_OUTPUT_IMAGE_ID {
	SOF_NON = 0,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 入力画像 左ch.
	 * @~
	 * 640x240, 8bit grayscale.
	 */
	SOF_INPUT_L = 1,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 入力画像 右ch.
	 * @~
	 * 640x240, 8bit grayscale.
	 */
	SOF_INPUT_R,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 入力画像 ステレオ
	 * @~
	 * 320x240, 8bit grayscale.2ch.
	 */
	SOF_INPUT_STEREO,
	/**
	 * @~english
	 *
	 * @~japanese
	 * マップ画像 左ch,X方向用.
	 * 整数部と、小数部の2ch分。
	 * @~
	 * 256x640　(640x240 ccw90), 8bit grayscale. 2ch
	 */
	SOF_MAP_X_L,
	/**
	 * @~english
	 *
	 * @~japanese
	 * マップ画像 右ch,X方向用.
	 * 整数部と、小数部の2ch分。
	 * @~
	 * 256x640 (Effective 640x240 ccw90), 8bit grayscale. 2ch
	 */
	SOF_MAP_X_R,
	/**
	 * @~english
	 *
	 * @~japanese
	 * マップ画像 左ch,Y方向用.
	 * 整数部と、小数部の2ch分。
	 * @~
	 * 640x240, 8bit grayscale. 2ch
	 */
	SOF_MAP_Y_L,
	/**
	 * @~english
	 *
	 * @~japanese
	 * マップ画像 右ch,Y方向用.
	 * 整数部と、小数部の2ch分。
	 * @~
	 * 640x240, 8bit grayscale. 2ch
	 */
	SOF_MAP_Y_R,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 正規化画像 左ch.
	 * @~
	 * 640x240, 8bit grayscale.
	 */
	SOF_NORMALIZED_L,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 正規化画像 右ch.
	 * @~
	 * 640x240, 8bit grayscale.
	 */
	SOF_NORMALIZED_R,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 正規化画像 ステレオ.
	 * @~
	 * 340x240, 8bit grayscale. 2ch
	 */
	SOF_NORMALIZED_STEREO,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 視差画像 整数部
	 * @~
	 * 213x237, 8bit grayscale
	 */
	SOF_DISPARITY_I,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 視差画像 小数部
	 * @~
	 * 256x237(Evective 213x237), 8bit grayscale
	 */
	SOF_DISPARITY_F,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 視差画像 整数部と小数部
	 * @~
	 * 256x237(Evective 213x237), 8bit grayscale
	 */
	SOF_DISPARITY_COMP,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 視差のヒストグラム画像.
	 * @~
	 * 128x213 (Effective 213x120 ccw90), 8bit grayscale, 2ch.
	 */
	SOF_HISTOGRAM,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 視差のヒストグラム画像, フィルター後.
	 * @~
	 * 128x213 (Effective 213x120 ccw90), 8bit grayscale, 2ch.
	 */
	SOF_HISTOGRAM_FILTERED,
	SOF_INPUT_L_HALF, 
	SOF_INPUT_R_HALF, 
};

/**
 * @~english
 *
 * @~japanese
 * ステレオ処理アルゴリズムからの出力結果を表すID.
 */
enum STEREO_ALG_OUTPUT_RESULT_ID {
	/**
	 * @~english
	 *
	 * @~japanese
	 */
	SOR_NON = 0,
	/**
	 * @~english
	 *
	 * @~japanese
	 * オブジェクト抽出(ヒストグラム抽出)結果.
	 * フィルタ後の視差ヒストグラム画像から、ヒストグラム値でtop20の値とインデックスを結果として得る。
	 */
	SOR_RESULT_HIST = 0x01,
	/**
	 * @~english
	 *
	 * @~japanese
	 * オブジェクト抽出(ハフ変換)結果.
	 * フィルタ後の視差ヒストグラム画像から、ハフ変換により直線検出した結果を得る。
	 */
	SOR_RESULT_HOUGH = 0x02,
	/**
	 * @~english
	 *
	 * @~japanese
	 * オブジェクト抽出(ラベリング)結果.
	 * フィルタ後の視差ヒストグラム画像から、ラベリング処理によりグループ化されたオブジェクトの最近の座標値を得る。
	 */
	SOR_RESULT_LABELING = 0x03,
	/**
	 * @~english
	 *
	 * @~japanese
	 * ステレオ視によるオブジェクト認識処理のフラグマスク.
	 */
	SOR_RESULT_MASK_STEREO = 0x0f,
	/**
	 * @~english
	 *
	 * @~japanese
	 * 白線検出によるレーン認識結果を得る.
	 */
	SOR_RESULT_LANE = 0x10,
};


#pragma pack(push, 1)

/**
 * @~english
 *
 * @~japanese
 * レーン検出結果.
 */
struct LaneResult {
	/**
	 * @~english
	 *
	 * @~japanese
	 * 左側の白線のX座標(スクリーン座標)
	 */
	short   xpos_l[8];
	/**
	 * @~english
	 *
	 * @~japanese
	 * 右側の白線のX座標(スクリーン座標)
	 */
	short   xpos_r[8];
	/**
	 * @~english
	 *
	 * @~japanese
	 * 左側の白線のY座標(スクリーン座標)
	 */
	short   ypos_l[8];
	/**
	 * @~english
	 *
	 * @~japanese
	 * 右側の白線のY座標(スクリーン座標)
	 */
	short   ypos_r[8];
};

/**
 * @~english
 *
 * @~japanese
 * ヒストグラム抽出によるオブジェクト検知の結果.
 */
struct StereoResultHist {
	/**
	 * @~english
	 *
	 * @~japanese
	 * ヒストグラムの値、度数。
	 */
	uchar   value[213 * 20];
	/**
	 * @~english
	 *
	 * @~japanese
	 * 度数分布のインデックス値。視差の整数部を表す。
	 */
	uchar   index[213 * 20];
};

/**
 * @~english
 *
 * @~japanese
 * ハフ変換によるオブジェクト検知の結果.
 */
struct StereoResultHough {
	/**
	 * @~english
	 *
	 * @~japanese
	 * 有効アイテム数｡
	 */
	ushort	npoint;
	/**
	 * @~english
	 *
	 * @~japanese
	 * 始点のX座標(ヒストグラム画像座標)
	 */
	ushort point_x0[512];
	/**
	 * @~english
	 *
	 * @~japanese
	 * 終点のX座標(ヒストグラム画像座標)
	 */
	ushort point_x1[512];
	/**
	 * @~english
	 *
	 * @~japanese
	 * 始点のY座標(ヒストグラム画像座標)
	 */
	uchar  point_y0[512];
	/**
	 * @~english
	 *
	 * @~japanese
	 * 終点のY座標(ヒストグラム画像座標)
	 */
	uchar  point_y1[512];
};

/**
 * @~english
 *
 * @~japanese
 * ラベリングによるオブジェクト検知の結果.
 */
struct StereoResultLabeling {
	/**
	 * @~english
	 *
	 * @~japanese
	 * 有効アイテム数｡
	 */
	ushort	npoint;
	/**
	 * @~english
	 *
	 * @~japanese
	 * 始点のX座標(ヒストグラム画像座標)
	 */
	ushort point_x0[512];
	/**
	 * @~english
	 *
	 * @~japanese
	 * 終点のX座標(ヒストグラム画像座標)
	 */
	ushort point_x1[512];
	/**
	 * @~english
	 *
	 * @~japanese
	 * 始点のY座標(ヒストグラム画像座標)
	 */
	uchar  point_y0[512];
	/**
	 * @~english
	 *
	 * @~japanese
	 * 終点のY座標(ヒストグラム画像座標)
	 */
	uchar  point_y1[512];
};

#pragma pack(pop)


/**
 * @~english
 *
 * @~japanese
 * ステレオ処理アルゴリズムにたいする外部パラメータ構造体.
 */
struct StereoAlgParam  {
	/**
	 * @~english
	 *
	 * @~japanese
	 * パラメータID
	 */
	STEREO_ALG_PARAM_ID	id;
	/**
	 * @~english
	 *
	 * @~japanese
	 * パラメータの値
	 */
	ulong value;
};


/**
 * @~english
 * IPM module Management class.
 * This is the sample class.
 * @~japanese
 * 画像処理モジュールのコントロールクラス.
 * ステレオ視アルゴリズムの動作るす画像処理モジュール(IMAPCAR)に対して操作し、データを要求する。
 */
class IpmManager
{
public:
	/**
	 * Constructor.
	 */
	IpmManager();
	/**
	 * Destructor.
	 */
	virtual ~IpmManager();
public:

	/**
	 * @~english
	 * @return succeed or failed.
	 * @~japanese
	 * オブジェクトの初期化.
	 * オブジェクト内部を初期化する。
	 * @return 成功したかどうかを返す。
	 */
	bool Init();
	/**
	 * @~english
	 * Hardware reset the IPM board.
	 * It sends the 'reset' command to IPM board to hardware reset the ipm board.
	 * @return succeed or failed.
	 * @~japanese
	 * ハードウェアリセット.
	 * コマンドを送り、IPMボードのハードウェアリセットを行う。
	 * @return 成功したかどうかを返す。
	 */
	bool Reset();
	/**
	 * @~english
	 *
	 * @~japanese
	 * IMAPCARへプログラムをロードする.
	 * ディスクからオブジェクトファイルを読み込み、IMAPCARメモリにロードする。また必要なデータ(マップファイル)も
	 * ロードする。
	 * @param		alg ロードするプログラムを指定する.
	 * @return	成功したかどうかを返す.
	 */
	bool LoadProgram(IMAP_ALGORITHM_NAME alg);
	/**
	 * @~english
	 *
	 * @~japanese
	 * IMAPCARプログラムのバージョン取得.
	 * IMAPCARにロードされているプログラムの名前とバージョンを返す。
	 * @param		ver バージョンを示す4byteの数字が返る領域。
	 * @return	成功したかどうかを返す.
	 */
	bool GetImapSoftwareVersion(ulong *ver);
	/**
	 * @~english
	 *
	 * @~japanese
	 * IMAPCARプログラムのバージョン取得.
	 * IMAPCARにロードされているプログラムの名前とバージョンを返す。
	 * @return	プログラムを示す値.
	 */
	IMAP_ALGORITHM_NAME GetCurrentProgram() const;
	/**
	 * @~english
	 *
	 * @~japanese
	 * IMAPCARプログラムの開始.
	 * ロードしたプログラムをスタートさせる。
	 * @return	成功したかどうかを返す.
	 */
	bool StartImap();
	/**
	 * @~english
	 *
	 * @~japanese
	 * IMAPCARプログラムの停止.
	 * 実行状態のプログラムを停止させる。
	 * @return	成功したかどうかを返す.
	 */
	bool StopImap();
	/**
	 * @~english
	 *
	 * @~japanese
	 * IMAPCARプログラムから取得する画像を選択する.
	 * IMAPCARプログラムが出力し、素の画像をマネージャが読み込む。どの画像を取得するかの指定をここで行う。
	 * @param		sel 取得したい画像のIDを指定する.
	 * @return	成功したかどうかを返す.
	 */
	bool SelectImageOutput(STEREO_ALG_OUTPUT_IMAGE_ID sel);
	/**
	 * @~english
	 *
	 * @~japanese
	 * IMAPCARプログラムから取得する結果を選択する.レーン検出または、オブジェクト週出のどちらか、または双方を
	 * 取得することができる。オブジェクト抽出は、ヒストグラム、ハフ変換、ラベリングの3つのうちのどれか一つを指定する。
	 * @param		sel 出力を得たい結果を表すフラグ。レーン検出結果は、ほかのオブジェクト抽出のどれか一つと組み合わせることができる。
	 * @return	成功したかどうかを返す.
	 */
	bool SelectResultOutput(STEREO_ALG_OUTPUT_RESULT_ID sel);
	/**
	 * @~english
	 *
	 * @~japanese
	 * SelectImageOutputで指定した現在の出力の設定を返す.
	 * @return	現在の画像鵜出力のID。
	 */
	STEREO_ALG_OUTPUT_IMAGE_ID GetCurrentImageOutput(int *width = 0, int *height = 0, int *ch = 0) const;
	/**
	 * @~english
	 *
	 * @~japanese
	 * SelectResultOutputで指定した現在の出力の設定を返す.
	 * @return	現在の結果鵜出力のID。
	 */
	STEREO_ALG_OUTPUT_RESULT_ID GetCurrentResultOutput() const;
	/**
	 * @~english
	 *
	 * @~japanese
	 * 画像出力を画像処理ボードから読み出し、オブジェクト内部に保存する.
	 * @return	成功したかどうかを返す.
	 */
	bool CollectImage();
	/**
	 * @~english
	 *
	 * @~japanese
	 * 収集した画像の戦闘ポインタを返す.
	 * @return	オブジェクト内部のバッファへのポインタ.メソッド呼び出しによって移動上書きの可能性があるため、
	 * ポインタを保存してはいけない。読み出しのためだけに使用すること。
	 */
	const uchar *ImageData();
	/**
	 * @~english
	 *
	 * @~japanese
	 * 収集した画像のサイズを返す.バイト数。画像の具体的なフォーマットについてはリファレンスマニュアルを参照。
	 * @return	サイズ
	 */
	ulong ImageLength() const;
	/**
	 * @~english
	 *
	 * @~japanese
	 * 結果出力を画像処理ボードから読み出し、オブジェクト内部に保存する.
	 * @return	成功したかどうかを返す.
	 */
	bool CollectResult();
	/**
	 * @~english
	 *
	 * @~japanese
	 * レーン検出の結果を取得する.CollectResultで得た値をこのメソッドにより読み出す。
	 * @return	成功したかどうかを返す.
	 */
	bool GetResultLane(LaneResult *result);
	/**
	 * @~english
	 *
	 * @~japanese
	 * オブジェクト抽出(ヒストグラム抽出による)の結果を取得する.CollectResultで得た値をこのメソッドにより読み出す。
	 * @return	成功したかどうかを返す.
	 */
	bool GetResultStereoHist(StereoResultHist *result);
	/**
	 * @~english
	 *
	 * @~japanese
	 * オブジェクト抽出(ハフ変換による)の結果を取得する.CollectResultで得た値をこのメソッドにより読み出す。
	 * @return	成功したかどうかを返す.
	 */
	bool GetResultStereoHough(StereoResultHough *result);
	/**
	 * @~english
	 *
	 * @~japanese
	 * オブジェクト抽出(ラベリングによる)の結果を取得する.CollectResultで得た値をこのメソッドにより読み出す。
	 * @return	成功したかどうかを返す.
	 */
	bool GetResultStereoLabeling(StereoResultLabeling *result);
	/**
	 * @~english
	 *
	 * @~japanese
	 * IMAPCARプログラムからのリクエストを待つ.
	 * 通常は、要求するOutput,Imageの結果が揃ったときにリクエストが生じる。
	 * @return	成功したかどうかを返す.
	 */
	bool Wait();

	/**
	 * @~english
	 *
	 * @~japanese
	 * IMAPCARプログラムに対して外部パラメータを設定する.個々に設定する。
	 * @return	成功したかどうかを返す.
	 * @see STEREO_ALG_PARAM_ID
	 */
	bool SetParam(int param_id, ulong value);
	/**
	 * @~english
	 *
	 * @~japanese
	 * IMAPCARプログラムに対して外部パラメータを設定する.すべてのパラメータを一度に設定する。
	 * @return	成功したかどうかを返す.
	 * @see STEREO_ALG_PARAM_ID
	 */
	bool SetParam(const StereoAlgParam *param);
	/**
	 * @~english
	 *
	 * @~japanese
	 * @return	成功したかどうかを返す.
	 * @see STEREO_ALG_PARAM_ID
	 */
	bool SetIntInterval(int intreq_interval, int imageout_interval);



protected:
	void init();
	bool setParam(uchar size, ulong addr, ulong value);
	bool getParam(uchar size, ulong addr, ulong *value);
	bool isReadyImage();
	void runImap();
	void stopImap();
	bool load_bitmap(unsigned long addr, const char *fname);
	bool collect_half(ulong addr, ulong size, ulong offset = 0L);
	bool collect(ulong addr, ulong size, ulong offset = 0L);
	bool collect_to(ulong addr, ulong size, void *pData);


private:
	IpmControl *_ipc; // pointer to instance  of IpmControl
	IpmDevice *_dev; // pointer
	IpmSerial *_ips;

	IMAP_ALGORITHM_NAME _current_program;
	STEREO_ALG_OUTPUT_IMAGE_ID  _collect_image_id;
	STEREO_ALG_OUTPUT_IMAGE_ID  _current_collect_image_id;
	STEREO_ALG_OUTPUT_RESULT_ID _collect_result_flag;
	STEREO_ALG_OUTPUT_RESULT_ID _current_collect_result_flag;
	bool _b_ready;
	uchar *_data;
	ulong _data_size;

	LaneResult _lane_result;
	StereoResultHist _result_hist;
	StereoResultHough _result_hough;
	StereoResultLabeling _result_labeling;

};




	}
}

#endif





