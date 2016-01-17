#ifndef _ERRORINFO_H_
#define _ERRORINFO_H_

#pragma once

#include <map>
#include "tString.h"

class ErrorInfo
{

public:
	virtual int GetLastError( void ) 
	{
		return error;
	}

	virtual void GetLastErrorMessage( void ) 
	{
		//エラーメッセージを設定
		if (!setflag) {
			SetErrorMessage();
			setflag = true;
		}

		if (error == ERROR_NONE)
		{
			_tprintf(_T("エラーなし\n"));
			return;
		}

		//エラーメッセージの取得
		if (message.find(error) != message.end())
		{
			_tprintf(_T("%s\n"), message[error].c_str());
			_tprintf(_T("%s\n"), detail.c_str());
		}
		//エラーコードメッセージが設定されてないときの処理
		else
		{
		}
	}

	virtual void SetError( const int &Code, const tstring &Detail )
	{
		error  = Code;
		detail = Detail;
	}

protected:
	ErrorInfo() : error(ERROR_NONE) { /*SetErrorMessage();*/ }
	virtual void SetErrorMessage() = 0;
	#pragma warning(disable : 4091 )
	virtual enum ErrorCode { ERROR_NONE = 0, };
	#pragma warning(default : 4091 )

	//エラー関係メンバ変数
	int error;
	std::map<int, tstring> message;
	tstring detail;

private:
	bool setflag = false;

};



#endif/*_ERRORINFO_H_*/