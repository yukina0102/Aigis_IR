#ifndef _DEFINE_H_
#define _DEFINE_H_

#pragma once

#include <vector>
#include <map>
#include "Common\opencv_common.h"

#include "Common/tString.h"

struct Aigis
{
	//サイズ関係
	static const int DefaultWidth;
	static const int DefaultHeight;
	static const int DefaultCols;
	static const int DefaultRows;

	static const int IconWidth;
	static const int IconHeight;
	static const int IconCols;
	static const int IconRows;


	//ブラウザ関係
	static const std::vector<tstring> BrowserList;

	//ドロップ関係
	static const int MaxDrop;

};

//認識閾値
struct Threshold
{
	static const std::map<int, double> ImageSearcher;
	static const std::map<int, double> StageSearcher;

	static const std::map<int, double> SceneChecker;
};

//マッチング範囲
struct MatchRange
{
	static const cv::Rect Combine;
	static const cv::Rect CombineIcon;
};

struct Icon 
{
	static const int Width;
	static const int Height;
	static const int Cols;
	static const int Rows;

	static const std::vector<cv::Rect> CombineRect;//合成画面アイコン領域

	static const std::vector<cv::Point> Mask;//アイコン不要部分の除外マスク
};

#include "Path.h"

#endif/*_DEFINE_H_*/
