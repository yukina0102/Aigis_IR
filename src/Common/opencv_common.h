#ifndef __OPENCV_H__
#define __OPEMCV_H__

//#define __LIB_DLL__
#define __LIB_STATIC__

#pragma warning(disable : 4819)
//OpenCV共通ヘッダー
//#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
//ライブラリ
#ifdef __LIB_DLL__
#include <opencv2/opencv_lib.hpp>
#endif
#ifdef __LIB_STATIC__
#include "opencv_lib.h"
#endif

#pragma warning(default: 4819)

#undef __LIB_DLL__
#undef __LIB_STATIC__

#endif/*__OPEMCV_H__*/