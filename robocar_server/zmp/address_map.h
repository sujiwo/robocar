/**
 * @file
 *
 * @~english
 * @brief
 *
 * @author	Masaki SegaWa
 *
 * @~japanese
 * @brief		IMAPCAR ステレオ視プログラムのアドレス定義　ヘッダ
 *
 * @author	瀬川正樹
 *
 * @~
 * @date	2009-07-01
 *
 * Copyright (c) 2009 ZMP Inc. All rights reserved.
 */


#ifndef __ADDRESS_MAP_H__
#define __ADDRESS_MAP_H__




#define DATA_SIZE_STEREO                  (640*240*2)
#define DATA_SIZE_HALF_STEREO             (640*240*2)
#define DATA_SIZE_HALF                    (640*240*1)
#define DATA_SIZE_MONO                    (640*240)
#define DATA_SIZE_MAP_X                   (256*640)
#define DATA_SIZE_MAP_Y                   (DATA_SIZE_MONO)
#define DATA_SIZE_MAP_X_STEREO            (DATA_SIZE_MAP_X*2)
#define DATA_SIZE_MAP_Y_STEREO            (DATA_SIZE_MAP_Y*2)
#define DATA_SIZE_DISPARITY               (256*237)
#define DATA_SIZE_DISPARITY_COMP          (256*237*2)
#define DATA_SIZE_HISTO_D                 (128*213)
#define DATA_SIZE_LANE_RESULT             (2*8*4)
#define DATA_SIZE_STEREO_RESULT_HIST      (256*20*2)
#define DATA_SIZE_STEREO_RESULT_HOUGH     ((2+2+1+1)*512+2)
#define DATA_SIZE_STEREO_RESULT_LABELING  ((2+2+1+1)*512+2)



#define ADDR_SOFT_NAME			0x20000
#define ADDR_SOFT_VERSION		0x20002
#define ADDR_REMAP_OFFSET_L		0x20100
#define ADDR_REMAP_OFFSET_R		0x20102
#define ADDR_LANE_INPUT_CH		0x20110
#define ADDR_LANE_BIN_TH		0x20111
#define ADDR_LANE_NUM_TH		0x20112
#define ADDR_STEREO_SAD_TH		0x20120
#define ADDR_STEREO_EDGE_TH		0x20121
#define ADDR_STEREO_DIS_OFFSET		0x20122
#define ADDR_STEREO_DIS_SHIFT		0x20123
#define ADDR_STEREO_PRE_FILTER          0x20124
#define ADDR_HIST_Y0			0x20128
#define ADDR_HIST_Y1			0x20129
#define ADDR_GAUSS_C1			0x20130
#define ADDR_GAUSS_C2			0x20131
#define ADDR_GAUSS_C3			0x20132
#define ADDR_GAUSS_C4			0x20133
#define ADDR_GAUSS_C5			0x20134
#define ADDR_GAUSS_C6			0x20135
#define ADDR_GAUSS_KSHIFT		0x20136
#define ADDR_OBJECT_SEL			0x20140
#define ADDR_HOUGH_BIN_TH		0x20150
#define ADDR_HOUGH_MIN_COUNT		0x20151
#define ADDR_HOUGH_MIN_LENGTH		0x20152
#define ADDR_HOUGH_MAX_BREAK		0x20153
#define ADDR_LABEL_BIN_TH		0x20160
#define ADDR_LABEL_NOISE_TH		0x20161
#define ADDR_LABEL_DILATION		0x20162
#define ADDR_LABEL_MIN_WIDTH		0x20163
#define ADDR_OUTSEL			0x20180
#define ADDR_HOST_INTREQ_INTERVAL	0x20181
#define ADDR_HOST_IMAGEOUT_INTERVAL     0x20182
#define ADDR_IMAGEOUT_FLAG              0x20183
#define ADDR_LANE_XPOS_L		0x20200
#define ADDR_LANE_XPOS_R		0x20210
#define ADDR_LANE_YPOS_L		0x20220
#define ADDR_LANE_YPOS_R		0x20230
#define ADDR_OBJECT_NPOINT		0x202a0
#define ADDR_OBJECT_POINT_X0		0x202a2
#define ADDR_OBJECT_POINT_X1		0x206a2
#define ADDR_OBJECT_POINT_Y0		0x20aa2
#define ADDR_OBJECT_POINT_Y1		0x20ca2
#define ADDR_MAP_X0_L			0x40000
#define ADDR_MAP_X1_L			0x68000
#define ADDR_MAP_X0_R			0x90000
#define ADDR_MAP_X1_R			0xB8000
#define ADDR_MAP_Y0_L			0xE0000
#define ADDR_MAP_Y1_L			0x105800
#define ADDR_MAP_Y0_R			0x12B000
#define ADDR_MAP_Y1_R			0x150800
#define ADDR_Image_I_L			0x176000
#define ADDR_Image_I_R			0x19B800
#define ADDR_Image_M_L			0x1C1000
#define ADDR_Image_M_R			0x1E9000
#define ADDR_Image_D_I			0x211000
#define ADDR_Image_D_F			0x21FD00
#define ADDR_HISTO_D			0x22EA00
#define ADDR_HIST_TOP_VALUE		0x236300
#define ADDR_HIST_TOP_INDEX		0x237700
#define ADDR_Buffer_O			0x238B00


#endif

