#ifndef __MESSAGE_H__
#define __MESSAGE_H__

#include "common.h"

namespace ProcessNetwork{


class Message
{
public:
	Message( HWND Hwnd ) 
		:hwnd(Hwnd)
	{}

	bool Send( tstring tStr )
	{
		//wstringに変換してバッファにコピー
		std::wstring wstr = convert<wchar_t>(tStr);
		wchar_t *buffer = new wchar_t[wstr.length() + 1];
		wcscpy_s(buffer, wstr.length() + 1, wstr.c_str());


		COPYDATASTRUCT cd;
		cd.dwData = 0;
		cd.cbData = (DWORD)(wstr.length() + 1);
		cd.lpData = buffer;


		LRESULT res = SendMessage( 
			hwnd, 
			WM_COPYDATA, 
			(WPARAM)NULL, 
			(LPARAM)&cd 
			);


		return true;
	}

private:
	HWND hwnd;

};


}

#endif/*__MESSAGE_H__*/