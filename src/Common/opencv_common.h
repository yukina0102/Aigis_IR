#ifndef __OPENCV_H__
#define __OPEMCV_H__

//#define __LIB_DLL__
#define __LIB_STATIC__

#pragma warning(disable : 4819)
//OpenCV���ʃw�b�_�[
//#include <opencv2/opencv.hpp>
#include <opencv2/opencv.hpp>
//���C�u����
#ifdef __LIB_DLL__
#include <opencv2/opencv_lib.hpp>
#endif
#ifdef __LIB_STATIC__
#include <opencv2/opencv_staticlib.hpp>
#endif

#pragma warning(default: 4819)

#undef __LIB_DLL__
#undef __LIB_STATIC__

#endif/*__OPEMCV_H__*/