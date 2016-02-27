#pragma once

// バージョン取得
#define CV_VERSION_STR CVAUX_STR(CV_MAJOR_VERSION) CVAUX_STR(CV_MINOR_VERSION) CVAUX_STR(CV_SUBMINOR_VERSION)

// ビルドモード
#ifdef _DEBUG
#define CV_EXT_STR "d.lib"
#else
#define CV_EXT_STR ".lib"
#endif

//#pragma comment(lib, "opencv_aruco" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_bgsegm" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_bioinspired" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_calib3d" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_ccalib" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_core" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_datasets" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_dnn" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_dpm" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_face" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_features2d" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_flann" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_fuzzy" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_highgui" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_imgcodecs" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_imgproc" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_line_descriptor" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_ml" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_objdetect" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_optflow" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_photo" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_plot" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_reg" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_rgbd" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_saliency" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_shape" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_stereo" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_stitching" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_structured_light" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_superres" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_surface_matching" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_text" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_tracking" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_ts" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_video" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_videoio" CV_VERSION_STR CV_EXT_STR)
#pragma comment(lib, "opencv_videostab" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_viz" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_xfeatures2d" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_ximgproc" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_xobjdetect" CV_VERSION_STR CV_EXT_STR)
//#pragma comment(lib, "opencv_xphoto" CV_VERSION_STR CV_EXT_STR)