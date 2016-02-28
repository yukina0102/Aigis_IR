#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "../common.h"

//非推奨関数を実行可能にする
#pragma warning(disable:4996)

//デバッグ時実行
#ifdef _DEBUG

//ログ出力用フラグ
#define LOG_START	1 << 0
#define LOG_END		1 << 1
#define LOG_ADD		1 << 2

#define LOG_CONSOLE	1 << 3	//ログ出力関係
#define LOG_ERROR	1 << 4
#define LOG_FILE	1 << 5
#define LOG_FLASH	1 << 6

#define LOG_FILE_NAME	"log.txt"
#define SAFE_FCLOSE(p) if(p){ fclose((p)); (p) = NULL; }


//処理時間出力
#define COUNT_START	0
#define COUNT_END	1

//----テスト画像関係-----
//出力先フォルダ
#define TESTTEX_FOLDER	".\\test"

//ログ出力マクロ
void OutputLog(int OutputFlag, TCHAR *FuncName, TCHAR *FileName, long LineNum, TCHAR *Format, ...);
#define DEBUG_LOG( flag, lpszFormat, ...) OutputLog( flag, _T(__FUNCTION__), _T(__FILE__), __LINE__, _T(lpszFormat), __VA_ARGS__ )

#else/*_DEBUG*/
//リリース時のみ実行

#define DEBUG_LOG( flag, lpszFormat, ...)

#endif/*_DEBUG*/


#endif/*_DEBUG_H_*/