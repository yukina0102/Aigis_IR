
#include "debug.h"

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef _DEBUG

//出力ログの自動付与設定
static int logflag = LOG_START | LOG_FLASH | LOG_FILE;
//----------------------------------------------------------------------------
//	ログを出力する
//	
//	引数	int		OutputFlag	出力フラグ
//			_TCHAR	*FuncName	実行元関数名
//			_TCHAR	*FileName	実行元ファイル名
//			long	LineNum		実行元行数
//			_TCHAR	*Format		出力文字列
//
//	戻り値	なし
//----------------------------------------------------------------------------
void OutputLog(int OutputFlag, _TCHAR *FuncName, _TCHAR *FileName, long LineNum, _TCHAR *format, ...)
{

#define LOG_FOPEN(f) do { \
	SAFE_FCLOSE(fp); \
	fp = _tfopen( _T(LOG_FILE_NAME), _T(f));\
	if( !fp ) { \
		logflag &= ~LOG_FILE;\
		}\
} while (0)

#define LOG_SETTING ( LOG_ADD | LOG_START | LOG_END )

	static FILE *fp = NULL;

	OutputFlag |= logflag;


	//-----ログ設定-----
	switch (OutputFlag & LOG_SETTING)
	{
		//今のところSTARTとADDは同じ機能
		case LOG_START:
			LOG_FOPEN("a");
			_tsetlocale(LC_ALL, _T(""));	//コンソール表示設定
			logflag &= ~( LOG_START | LOG_ADD );
			break;
		case  LOG_ADD:
			LOG_FOPEN("a");
			_tsetlocale(LC_ALL, _T(""));	//コンソール表示設定
			logflag &= ~(LOG_START | LOG_ADD);
			break;

		case LOG_END:
			SAFE_FCLOSE(fp);
			return;
			break;
	}
		
	//-----ログ出力-----

	//フルパスからファイル名を検索("\\"が含まれている場合フルパスとして扱う)
	_TCHAR *tmp;	//一時保管用ポインタ
	while ((tmp = _tcsstr(FileName, _T("\\"))) != NULL)
	{
		//\\を削除する
		FileName = tmp + 1;
	}

	va_list ap;
	va_start(ap, format);

	//ログを文字列に変換
	_TCHAR formatbuf[100];
	_vstprintf(formatbuf, sizeof(formatbuf) / sizeof(formatbuf[0]), format, ap);


	_TCHAR outbuf[200];
	if ( OutputFlag & LOG_ERROR)
		_stprintf_s(outbuf, sizeof(outbuf) / sizeof(outbuf[0]), _T("%s[%d] %s:エラー %s\n"), FileName, LineNum, FuncName, formatbuf);
	else
		_stprintf_s(outbuf, sizeof(outbuf) / sizeof(outbuf[0]), _T("%s[%d] %s:%s\n"), FileName, LineNum, FuncName, formatbuf);

	



	if ( OutputFlag & LOG_CONSOLE)
	{
		_ftprintf( stdout, outbuf );
		if (logflag & LOG_FLASH)
		{
			fflush( stdout );
		}
	
	}
	if ( OutputFlag & LOG_ERROR)
	{
		_ftprintf(stderr, outbuf);
		if (logflag & LOG_FLASH)
		{
			fflush(stderr);
		}
	}
	if ( OutputFlag & LOG_FILE)
	{
		_ftprintf(fp, outbuf);
		if (logflag & LOG_FLASH)
		{
			fflush(fp);
		}
	}

	va_end(ap);

#undef LOG_FOPEN
#undef LOG_SETTING

}

#endif/*_DEBUG*/
