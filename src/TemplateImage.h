#ifndef TEMPLATEIMAGE_H
#define TEMPLATEIMAGE_H

#pragma once

#include "common.h"
#include "Common\ErrorInfo.h"

typedef class CTemplateImage * TemplateImage;

class CTemplateImage : public ErrorInfo 
{

//コンストラクタ、デストラクタ
public:
	CTemplateImage();
	CTemplateImage(const _TCHAR  *filename, const int &matchsize = Aigis::DefaultWidth );
	CTemplateImage(const tstring &filename, const int &matchsize = Aigis::DefaultWidth );
	CTemplateImage(const cv::Mat &mat,      const int &matchsize = Aigis::DefaultWidth );
	virtual ~CTemplateImage();

//アクセサ
public:
	inline cv::Mat GetImage(void) const
	{
		return image;
	}
	inline int   GetMatchSize(void) const
	{
		return matchSize;
	}

//メソッド
private:
	void Create( const tstring &filename, const int &matchsize);
public:
	cv::Mat Resize( const double &scale ) const;
	cv::Mat Resize( const int &matchsize ) const;

//メンバ
private:
	cv::Mat image;
	int matchSize;

//エラー情報
	enum ErrorCode 
	{
		ERROR_NONE,
		ERROR_LOAD,
	};

	virtual void SetErrorMessage() 
	{
		message[ERROR_LOAD] = _T("画像ファイルロードエラー");
	}

public:
	tstring icon;	//アイコンファイル名(ダイアログに使用)


};

#endif/*TEMPLATEIMAGE_H*/