#include "Stdafx.h"

#include "Screen.h"

#include <Dwmapi.h>
#include "Define.h"

//#include <mutex>

//#include "TemplateMatching.h"

const std::vector<tstring> CScreen::windowCaption = {
	_T("千年戦争アイギス - オンラインゲーム - DMM.com - Google Chrome"),
	_T("千年戦争アイギス R - オンラインゲーム - DMM.R18 - Google Chrome"),
	_T("千年戦争アイギス - オンラインゲーム - DMM.com - Iron")
};

//C#連携用コード
cv::Mat CScreen::nowScreen;
BOOL CScreen::flag = FALSE;


BOOL CScreen::checkAero(void)
{

	if (!SUCCEEDED(DwmIsCompositionEnabled(&isAero)))
	{
		error = ERROR_AEROCHECK;
		
		//_tprintf( _T("Aeroモードチェック失敗 エラーコード:0x%08x"), GetLastError());

		//DEBUG_LOG(LOG_ERROR, "Aeroモードチェック失敗" );
		//チェックが失敗した場合FALSEとして扱う
		isAero = FALSE;
		return FALSE;
	}

	return TRUE;

}

BOOL CScreen::searchWindow(void)
{

	//ウインドウを取得済みかチェック
	if (isWindow)
		return TRUE;

	for (auto i = Aigis::BrowserList.begin(), n = Aigis::BrowserList.end(); i < n; ++i)
	{
		if ((hWnd = FindWindow(NULL, i->c_str())) != NULL)
		{
			caption = *i;
			isWindow = TRUE;
			//DEBUG_LOG(LOG_CONSOLE, "ウインドウが見つかりました\n%s hwnd=%08X", caption.c_str(), hWnd );
			
			//ウインドウサイズ関係の初期化
			width = -1;
			height = -1;
			
			return TRUE;
		}
	}

	//DEBUG_LOG(LOG_ERROR, "ウインドウが見つかりません");
	return FALSE;

}

void CScreen::getWindowSize( void )
{
	int width, height;

	//ウインドウサイズを取得
	GetWindowRect(hWnd, &rect);
	width = rect.right - rect.left;
	height = rect.bottom - rect.top;

	if (width != this->width || height != this->height)
	{
		this->width = width;
		this->height = height;

		isChangeSize = TRUE;
	}

}

cv::Mat CScreen::getAigisMat(void)
{
	return screen(aigisRect);
}

RECT CScreen::getRect(void)
{
	return rect;
}

BOOL CScreen::Calibration(void)
{
	aigisRect = cv::Rect(0, 0, 0, 0);

	cv::Mat gray;
	//グレースケールに変換
	cv::cvtColor(screen, gray, cv::COLOR_BGR2GRAY);

	// 画像の二値化【判別分析法(大津の二値化)】
	try
	{
		cv::threshold(gray, gray, 254, 255, cv::THRESH_BINARY/* | cv::THRESH_OTSU*/);
	}
	catch (cv::Exception& e)
	{
		const char* err_msg = e.what();
		return FALSE;
	}

	std::vector<std::vector<cv::Point> > contours;


	//std::vector<std::vector<int> > test = { {1,2,3},{4,5,6,7},{8,9,10,11} };


	//return FALSE;
	// 輪郭の検出
	cv::findContours(gray, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE/*CV_CHAIN_APPROX_SIMPLE*/);
	//cv::findContours(screen, contours, CV_RETR_LIST, CV_CHAIN_APPROX_NONE/*CV_CHAIN_APPROX_SIMPLE*/);


	//return FALSE;


	// 検出された輪郭線を緑で描画
	std::vector< cv::Point > approx;
	for (auto contour = contours.begin(); contour != contours.end(); contour++){
		approx.clear();
		cv::approxPolyDP(cv::Mat(*contour), approx, 25.0, true);

		//輪郭線を近似
		if (approx.size() == 4)
		{
			//近似の癖を考慮して線分を補正
			if (approx[0].y != approx[1].y)
				approx[1].y = approx[0].y;
			if (approx[1].x != approx[2].x)
				approx[2].x = approx[1].x;
			if (approx[2].y != approx[3].y)
				approx[3].y = approx[2].y;
			if (approx[3].x != approx[0].x)
				approx[0].x = approx[3].x;

			//輪郭を4点座標に変換
			RECT rect;
			rect.left = approx[0].x;
			rect.top = approx[0].y;
			rect.right = approx[2].x;
			rect.bottom = approx[2].y;
			cv::Rect tempRoi(approx[0].x, approx[0].y, approx[2].x - approx[0].x + 1, approx[2].y - approx[0].y + 1);
			double rat = (double)(tempRoi.width) / (double)(tempRoi.height);

			if (1.49 <= rat && rat <= 1.51)
			{
				//比率があっていればアイギスの画面とする
				//輪郭線を描画
				//cv::polylines(ScreenData, /**contour*/approx, true, cv::Scalar(0, 255, 0), 2);
				//cv::Rect roi_rect(rect.left, rect.top, rect.right - rect.left + 1, rect.bottom - rect.top + 1);
				//aigisScreen = screen(roi_rect);
				aigisRect = tempRoi;
				//approx.clear();
				//contours.clear();
				return TRUE;

			}

		}
	}


	//DEBUG_LOG(LOG_ERROR, "アイギス画面取得失敗");

	return FALSE;

}

void CScreen::CheckWindowState(void)
{

	_TCHAR buf[255];
	//ウインドウが存在するかチェック
	if (!GetWindowText(hWnd, buf, 255))
	{
		isWindow = FALSE;
		hWnd = NULL;

		return;
	}

	//ウインドウの最小化チェック
	if( isIconic = IsIconic( hWnd ) )
		return;

	//ウインドウがアクティブかチェック
	/*if (hWnd == GetForegroundWindow())
		isActive = TRUE;
	else
		isActive = FALSE;
	*/
	isActive = TRUE;

	//ウインドウのサイズ変更チェック
	getWindowSize();

}


BOOL CScreen::Capture(void)
{
	flag = FALSE;

	//----キャプチャするウインドウの状態チェック----

	//ウインドウサーチ
	if (!searchWindow())
	{
		return FALSE;
	}

	//ウインドウの状態取得
	CheckWindowState();

	//ウインドウがなかったり、最小化されているときは実行しない
	//または対象ウインドウがアクティブじゃない場合もキャプチャしない
	if (!isWindow || isIconic || !isActive )
	{
		return FALSE;
	}


	//ウインドウサイズが変わっている場合、キャプチャ環境を初期化する
	if (isChangeSize)
	{
		Initialize();
		isChangeSize = FALSE;
		isCaribration = FALSE;
	}

	//----キャプチャ処理の開始----

	//画面の取得
	int result = BitBlt(hMemDC, 0, 0, width, height, hDC, 0, 0, SRCCOPY);

	screen = cv::cvarrToMat(captureSrc);
	//上下反転
	cv::flip(screen, screen, 0);

	//cv::Mat test = cv::cvarrToMat(captureSrc);

	//static bool debug = false;

	//if (!debug)
	//{
	//	cv::imwrite("test.png", CaptureMat);
	//	debug = true;


	//キャリブレーションが正常かチェック
	/*if (isCaribration)
	{
		cv::Mat threshold;
		cv::cvtColor(screen, threshold, cv::COLOR_BGR2GRAY);
		cv::threshold(threshold, threshold, 254, 255, cv::THRESH_BINARY );


		cv::Mat m1(cv::Size(aigisRect.width, 1), CV_8UC1, cv::Scalar(255, 255, 255));
		cv::Mat m2(cv::Size(1, aigisRect.height), CV_8UC1, cv::Scalar(255, 255, 255));
	
		CTemplateMatching test;
		if (test.Matching(threshold(aigisRect), m1) || test.Matching(threshold(aigisRect), m2, CTemplateMatching::COUNT_ADD))
		//{
			//isCaribration = FALSE;
			
			//処理が重いため機能を切ってある  デフォルトはFALSE
			isCaribration = TRUE;

			

		}

		//DEBUG_LOG(LOG_CONSOLE, "キャリブレーションチェック:%lf", test.getProcTime());

		


	
	}*/

	

	if (!isCaribration && Calibration())
	{
		isCaribration = TRUE;
	}
	else if( !isCaribration )
	{
		return FALSE;
	}

	//if( isCaribration )
	//	cv::imshow("test bmp", screen(aigisRect));
	//}

	//

	//C#連携用コード
	nowScreen = getAigisMat().clone();
	flag = TRUE;

	return TRUE;
}

void CScreen::Initialize(void)
{
	Finalize();

	// IplImageの作成
	//captureSrc = cvCreateImageHeader( cvSize( width, height ), IPL_DEPTH_8U, 3 );
	captureSrc = cvCreateImageHeader(cvSize(width, height), IPL_DEPTH_8U, 3);


	// DIBの情報を設定する
	BITMAPINFO bmpInfo;
	bmpInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmpInfo.bmiHeader.biWidth = width;
	bmpInfo.bmiHeader.biHeight = height;
	bmpInfo.bmiHeader.biPlanes = 1;
	bmpInfo.bmiHeader.biBitCount = 24;
	bmpInfo.bmiHeader.biCompression = BI_RGB;

	// DIBSection作成
	hDC = GetDC(hWnd);


	LPDWORD lpPixel;
	hBitmap = CreateDIBSection(hDC, &bmpInfo, DIB_RGB_COLORS, (void**)&lpPixel, NULL, 0);
	hMemDC = CreateCompatibleDC(hDC);
	SelectObject(hMemDC, hBitmap);

	// IplImageヘッダにデータをセット
	captureSrc->imageData = (char *)lpPixel;

	//cv::namedWindow("test bmp", CV_WINDOW_AUTOSIZE | CV_WINDOW_FREERATIO);
}

void CScreen::Finalize(void)
{
	//if (captureSrc != NULL)
	if (captureSrc != NULL)
	{
		cvReleaseImageHeader(&captureSrc);
		captureSrc = NULL;
	}
	if (hDC != NULL)
	{
		ReleaseDC(hWnd, hDC);
		hDC = NULL;
	}
	if (hMemDC != NULL)
	{
		DeleteDC(hMemDC);
		hMemDC = NULL;
	}
	if (hBitmap != NULL)
	{
		DeleteObject(hBitmap);
		hBitmap = NULL;
	}

}

CScreen::CScreen()
{
	captureSrc = NULL;
	hDC = NULL;
	hMemDC = NULL;
	hBitmap = NULL;

	isAero = FALSE;
	isWindow = FALSE;
	isIconic = FALSE;
	isChangeSize = FALSE;

	hWnd = NULL;
	width = 0;
	height = 0;
	//Initialize();
}

CScreen::~CScreen()
{
	Finalize();
}

/*
#include "FileName.h"
void CScreen::output(const char *Ext)
{

	CFileName name(_T(".\\testdata\\aigis"), _T(""), _T(""));

	do
	{
		name.Generate();

	} while (_tfopen(name.GetString().c_str(), _T("r")) != NULL);

	//ファイル書き出し
	cv::imwrite(convert<char>(name.GetString()), screen(aigisRect));
}*/