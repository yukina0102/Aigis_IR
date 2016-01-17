#include "Define.h"

const int Aigis::DefaultWidth  = 960;
const int Aigis::DefaultHeight = 640;
const int Aigis::DefaultCols = Aigis::DefaultWidth;
const int Aigis::DefaultRows = Aigis::DefaultHeight;

const int Aigis::IconWidth  = 99;
const int Aigis::IconHeight = 98;
const int Aigis::IconCols = Aigis::IconWidth;
const int Aigis::IconRows = Aigis::IconHeight;

const std::vector<tstring> Aigis::BrowserList = {
	 _T("千年戦争アイギス - オンラインゲーム - DMM.com - Google Chrome")
	,_T("千年戦争アイギス R - オンラインゲーム - DMM.R18 - Google Chrome")
	,_T("千年戦争アイギス - オンラインゲーム - DMM.com - Iron")
};

const int Aigis::MaxDrop = 7;

//Threshold
const std::map<int, double> Threshold::ImageSearcher = { 
	{ Aigis::DefaultWidth, 0.98 } 
};
const std::map<int, double> Threshold::SceneChecker  = {
	{ Aigis::DefaultWidth, 0.98 }
};
const std::map<int, double> Threshold::StageSearcher = {
	{ Aigis::DefaultWidth, 0.98 }
};


//MatchRange
const cv::Rect MatchRange::Combine = { 30 - 5, 520 - 5, 256 + 10, 32 + 10 };
const cv::Rect MatchRange::CombineIcon = { 46, 177, Aigis::IconWidth, Aigis::IconHeight };


//Icon
const int Icon::Width  = 99;
const int Icon::Height = 98;
const int Icon::Cols = Icon::Width;
const int Icon::Rows = Icon::Height;

const std::vector<cv::Rect> Icon::CombineRect = {
	{ 46,     177,     Icon::Width, Icon::Height },
	{ 46 + 1, 177,     Icon::Width, Icon::Height },
	{ 46,     177 + 1, Icon::Width, Icon::Height },
	{ 46 + 1, 177 + 1, Icon::Width, Icon::Height },
};

const std::vector<cv::Point> Icon::Mask = { 
	{ 0, 0 },{ 1, 0 },{ 2, 0 },{ 3, 0 },{ 4, 0 },{ 5, 0 },{ 6, 0 },{ 91, 0 },{ 92, 0 },{ 93, 0 },{ 94, 0 },{ 95, 0 },{ 96, 0 },{ 97, 0 },{ 98, 0 },
	{ 0, 1 },{ 1, 1 },{ 2, 1 },{ 3, 1 },{ 4, 1 },{ 93, 1 },{ 94, 1 },{ 95, 1 },{ 96, 1 },{ 97, 1 },{ 98, 1 },
	{ 0, 2 },{ 1, 2 },{ 2, 2 },{ 3, 2 },{ 95, 2 },{ 96, 2 },{ 97, 2 },{ 98, 2 },
	{ 0, 3 },{ 1, 3 },{ 2, 3 },{ 96, 3 },{ 97, 3 },{ 98, 3 },
	{ 0, 4 },{ 1, 4 },{ 97, 4 },{ 98, 4 },
	{ 0, 5 },{ 97, 5 },{ 98, 5 },
	{ 0, 6 },{ 98, 6 },
	{ 98, 7 },
	{ 0, 90 },{ 98, 90 },
	{ 0, 91 },{ 98, 91 },
	{ 0, 92 },{ 1, 92 },{ 97, 92 },{ 98, 92 },
	{ 0, 93 },{ 1, 93 },{ 97, 93 },{ 98, 93 },
	{ 0, 94 },{ 1, 94 },{ 2, 94 },{ 96, 94 },{ 97, 94 },{ 98, 94 },
	{ 0, 95 },{ 1, 95 },{ 2, 95 },{ 3, 95 },{ 95, 95 },{ 96, 95 },{ 97, 95 },{ 98, 95 },
	{ 0, 96 },{ 1, 96 },{ 2, 96 },{ 3, 96 },{ 4, 96 },{ 5, 96 },{ 93, 96 },{ 94, 96 },{ 95, 96 },{ 96, 96 },{ 97, 96 },{ 98, 96 },
	{ 0, 97 },{ 1, 97 },{ 2, 97 },{ 3, 97 },{ 4, 97 },{ 5, 97 },{ 6, 97 },{ 7, 97 },{ 91, 97 },{ 92, 97 },{ 93, 97 },{ 94, 97 },{ 95, 97 },{ 96, 97 },{ 97, 97 },{ 98, 97 },
};

