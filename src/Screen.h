#ifndef __SCREEN_H__
#define __SCREEN_H__

#pragma once

#include "common.h"

class CScreen
{
private:
	
	enum Error
	{
		ERROR_NONE,
		ERROR_AEROCHECK,
	};

public:
	CScreen();
	~CScreen();

	BOOL Capture(void);
	RECT getRect(void);
	cv::Mat getAigisMat(void);

	void output(const char *Ext);


private:
	void Initialize(void);
	void Finalize(void);

	BOOL checkAero( void );
	BOOL searchWindow(void);
	void getWindowSize(void);
	BOOL Calibration(void);
	void CheckWindowState(void);

public:

	//デフォルトのスクリーンサイズ
	static const int defaultWidth = 960;
	static const int defaultHeight = 640;

private:

	//ウインドウキャプション
	static const std::vector<tstring> windowCaption;

	BOOL isAero;
	BOOL isWindow;
	BOOL isIconic;
	BOOL isActive;
	BOOL isChangeSize;
	BOOL isCaribration;
	
	//ウインドウ関係
	HWND hWnd;
	tstring caption;
	RECT rect;

	int width;
	int height;

	//キャプチャー関係
	HBITMAP hBitmap;
	HDC		hDC;
	HDC     hMemDC;

	IplImage *captureSrc;
	cv::Mat screen;
	cv::Rect aigisRect;
	//エラー
	Error error;

//C#連携用コード
private:
	static cv::Mat nowScreen;
	static BOOL flag;
public:
	static cv::Mat GetScreen( void ) 
	{
		if (!flag)
			return cv::Mat();

		//nowScreen = cv::imread("コミュアイコン2.png");

		return nowScreen;
	}


};

typedef class std::unique_ptr<CScreen> Screen;

#endif/*__SCREEN_H__*/