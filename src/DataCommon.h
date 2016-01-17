#ifndef _NEWDATA_H_
#define _NEWDATA_H_

#pragma once

//#include "../common/Singleton.h"
#include "Common/ErrorInfo.h"
#include "Common/tString.h"
#include "TemplateImage.h"


namespace Aigis_DB
{

class CDataCommon
{
public:
	CDataCommon() : name(_T("")), image(_T("")){}
	CDataCommon( const tstring &name, const CTemplateImage &image )
	{
		Create(name, image);
	}

	void Create(const tstring &name, const CTemplateImage &image)
	{
		this->name = name;
		this->image = image;
	}
	virtual ~CDataCommon() {}

public:
	//データの中身チェック
	virtual void Show( void ) const
	{
		_tprintf( _T("%ws"), name.c_str() );
	}

//アクセサー
public:
	inline tstring GetName(void) const
	{
		return name;
	}
	virtual void SetName( const tstring &name )
	{
		this->name = name;
	}

	inline CTemplateImage GetTemplate(void) const
	{
		return image;
	}

	virtual void SetTemplate(const CTemplateImage &image)
	{
		this->image = image;
	}

//オペレーター
/*public:
	virtual BOOL operator==( const CData &data ) {
		if (data.GetName() != name)
			return FALSE;
		if (data.GetImage().GetImage().size() != image.GetImage().size())
			return FALSE;

		return TRUE;
		
	}*/

protected:
	tstring name;
	CTemplateImage image;

};}

//#define DATA_NULL NewData::CData( _T(""), CTemplateImage(_T("")))

#endif/*_NEWDATA_H_*/


/*
private:

enum ErrorCode
{
ERROR_NONE = 0,
ERROR_LOAD,
ERROR_NANIKA1,
ERROR_NANIKA2,
ERROR_NANIKA3,
};

void SetErrorMessage()
{
message[ERROR_LOAD]    = _T("ファイルロード失敗しました");
message[ERROR_NANIKA1] = _T("なにか１");
message[ERROR_NANIKA2] = _T("なにか２");
message[ERROR_NANIKA3] = _T("なにか３");
}
*/
