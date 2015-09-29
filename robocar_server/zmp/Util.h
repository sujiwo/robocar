/**
 * @file
 *
 * @~english
 * @brief	Communication class header.
 *
 * @author	Masaki SegaWa
 *
 * @~japanese
 * @brief	イメージユーティリティクラス　ヘッダ
 *
 * @author	瀬川正樹
 *
 * @~
 * @date	2009-06-30
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 */
#ifndef __RC_IMAGE_UTIL_H__
#define __RC_IMAGE_UTIL_H__


namespace zmp {
	namespace zrc {

struct StereoResultHist;
struct StereoResultHough;
struct StereoResultLabeling;

struct ObstacleMap {
	float lx;
	float lz;
	float value;
};
struct ObstacleLinseg {
	float lx0;
	float lz0;
	float lx1;
	float lz1;
};


/**
 * @~english
 * Constant that specifies the type of algorithm.
 * @~japanese
 * イメージングユーティリティクラス.
 * RcImageライブラリで得られた画像から座標変換などを行う機能を提供する。
 * キャリブレーションツールによって作成される'camera.xml'を元に、画像処理結果から実際のカメラ空間の
 * 座標へ変換する。
 */
class RcImageUtil
{
public:
	/**
	 * Constructor.
	 */
	RcImageUtil();
	/**
	 * Destructor.
	 */
	virtual ~RcImageUtil();

public:
	/**
	 * @~english
	 *
	 * @~japanese
	 * オブジェクトを初期化する.
	 */
	void Init();
	/**
	 * @~english
	 *
	 * @~japanese
	 * 変換に必要なカメラパラメータをディスクから読み込む.
	 * 環境変数`ZRC_CONFIG_PATH`で設定されたパスから、カメラパラメータファイル(camera.xml)を読み込む。
	 */
	bool LoadCameraParameterFile();

	/**
	 * @~english
	 *
	 * @~japanese
	 * 視差画像の２次元への汎用投影処理.
	 * スクリーン座標系(320x240)sx,d からカメラ座標での実空間座標XとZへ変換する。
	 * @param[in]		sx			スクリーン座標でのx.
	 * @param[in]		disparity	視差値.
	 * @param[out]	lx			カメラ座標系でのx.
	 * @param[out]	lz			カメラ座標系でのz(奥行き).
	 */
	bool Reproject2D(float sx, float disparity, float *lx, float *lz);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 視差画像の２次元への汎用投影処理.
	 * スクリーン座標系(320x240)sx,d からカメラ座標での実空間座標XとZへ変換する。
	 * 与えた数分の繰り返し処理を行う。
	 * @param[in]		sx			スクリーン座標でのx配列.
	 * @param[in]		disparity	視差値 配列.
	 * @param[in]		n 			入出力のポイント数.
	 * @param[out]	lx			カメラ座標系でのx配列.
	 * @param[out]	lz			カメラ座標系でのz(奥行き)配列.
	 */
	bool Reproject2D(const float *sx, const float *disparity, int n, float *lx, float *lz);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 視差画像の３次元への汎用投影処理.
	 * スクリーン座標系(320x240)sx,sy,d からカメラ座標での実空間座標X,YとZへ変換する。
	 * @param[in]		sx			スクリーン座標でのx.
	 * @param[in]		sy			スクリーン座標でのy.
	 * @param[in]		disparity	視差値.
	 * @param[out]	lx			カメラ座標系でのx.
	 * @param[out]	ly			カメラ座標系でのy.
	 * @param[out]	lz			カメラ座標系でのz(奥行き).
	 */
	bool Reproject3D(float sx, float sy, float disparity, float *lx, float *ly, float *lz);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 視差画像の３次元への汎用投影処理.
	 * スクリーン座標系(320x240)sx,sy,d からカメラ座標での実空間座標X,YとZへ変換する。
	 * 与えた数分の繰り返し処理を行う。
	 * @param[in]		sx			スクリーン座標でのx配列.
	 * @param[in]		sy			スクリーン座標でのy配列.
	 * @param[in]		disparity	視差値 配列.
	 * @param[in]		n			 入出力のポイント数.
	 * @param[out]	lx			カメラ座標系でのx配列.
	 * @param[out]	ly			カメラ座標系でのy配列.
	 * @param[out]	lz			カメラ座標系でのz(奥行き)配列.
	 */
	bool Reproject3D(const float *sx, const float *sy, const float *disparity, int n, float *lx, float *ly, float *lz);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 視差画像の２次元への投影処理.
	 * ResultHistの結果(視差のヒストグラム画像)からカメラ座標での実空間座標X,Zへ変換する。
	 * 出力用のデータはあらかじめ十分な領域を用意しておく必要がある。
	 * @param[in]		hist_res	視差ヒストグラム画像.
	 * @param[out]	out			スクリーン座標でのy配列.
	 * @param[in]		n			出力用最大データ数
	 */
	bool ReprojectResHistTo2D(const StereoResultHist *hist_res, ObstacleMap *out, int n);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 視差画像の２次元への投影処理.
	 * ResultHoughの結果からカメラ座標での実空間座標X,Zへ変換する。
	 * 出力用のデータはあらかじめ十分な領域を用意しておく必要がある。
	 * @param[in]		point_res	視差ヒストグラム画像..
	 * @param[out]	out			スクリーン座標でのy配列.
	 * @param[in]		n			出力用最大データ数
	 */
	bool ReprojectResHoughTo2D(const StereoResultHough *point_res, ObstacleLinseg *out, int n);
	/**
	 * @~english
	 *
	 * @~japanese
	 * 視差画像の２次元への投影処理.
	 * ResultLabelingの結果からカメラ座標での実空間座標X,Zへ変換する。
	 * 出力用のデータはあらかじめ十分な領域を用意しておく必要がある。
	 * @param[in]		point_res	スクリーン座標でのx配列.
	 * @param[out]	out			スクリーン座標でのy配列.
	 * @param[in]		n			出力用最大データ数
	 */
	bool ReprojectResLabelingTo2D(const StereoResultLabeling *point_res, ObstacleLinseg *out, int n);

protected:
	bool reprojectPointResTo2D(const StereoResultHough *point_res, ObstacleLinseg *out, int n);


private:
	float _disparity_to_distance[4*4];
	bool _b_projection;
};


	}
}



#endif


