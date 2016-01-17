#ifndef _SQLACCESS_H_
#define _SQLACCESS_H_

#pragma once

#include "common.h"
#include "SqlData.h"

typedef class CSqlAccess * SqlAccess;

class CSqlAccess 
{
	public:
		typedef enum{
			ERROR_NONE,
			ERROR_STATEMENT,
		} err;

	private:
		sqlite3 *db = (sqlite3 *)NULL;
		sqlite3_stmt *stmt;

		err Error = ERROR_NONE;

	public:
		CSqlAccess(LPCTSTR filename);
		CSqlAccess(tstring filename);
		~CSqlAccess();

		BOOL Load(LPCTSTR filename);
		void UnLoad(void);

		//SQL文を使って処理を指定できる
		BOOL exec( SqlData cache, LPCTSTR sqlstatement );
		BOOL exec( LPCTSTR sqlstatement );
		BOOL Select(SqlData cache, LPCTSTR table, const std::vector<tstring> columns, LPCTSTR order);
		BOOL Select(SqlData cache, LPCTSTR sqlStatement);

		BOOL insert(SqlData cache, LPCTSTR sqlStatement);

		BOOL CreateTable(LPCTSTR sqlStatement);
		//void createTable( LPCTSTR table, std::vector<CSqlData::ColumnData> );

		BOOL DeleteTable(LPCTSTR sqlStatement);

		/*void query( void )
		{
			int ret;

			// データベースのオープン
			// オープンに失敗しても、Closeは行う必要がある。
			sqlite3* dp = NULL;
			ret = sqlite3_open16(L"testdb.dat", &dp);
			__try {
				if (ret != SQLITE_OK) {
					_tprintf(_TEXT("エラーメッセージ: %s\n"), sqlite3_errmsg16(dp));
					__leave;
				}

				// テーブルの作成
				ret = sqlite3_exec(dp, "CREATE TABLE TESTTBL("
					"IDX INTEGER PRIMARY KEY, VAL1 VARCHAR, VAL2 NUMBER);",
					NULL, NULL, NULL);
				if (ret != SQLITE_OK) {
					_tprintf(_TEXT("CREATEの失敗: %s\n"), sqlite3_errmsg16(dp));
				}

				// 既存テーブル上のデータの削除
				ret = sqlite3_exec(dp, "DELETE FROM TESTTBL;", NULL, NULL, NULL);
				if (ret != SQLITE_OK) {
					_tprintf(_TEXT("DELETEの失敗: %s\n"), sqlite3_errmsg16(dp));
					__leave;
				}

				// トランザクションの開始
				// トランザクションがかかっていないと、とてもとても遅くなる。
				ret = sqlite3_exec(dp, "BEGIN;", NULL, NULL, NULL);
				if (ret != SQLITE_OK) {
					_tprintf(_TEXT("BEGINの失敗: %s\n"), sqlite3_errmsg16(dp));
					__leave;
				}

				// 行の作成ループ
				sqlite3_stmt *stm = NULL;

				ret = sqlite3_prepare16(dp, L"INSERT INTO TESTTBL(VAL1, VAL2)"
					L"VALUES(?, ?)", -1, &stm, NULL);
				if (ret != SQLITE_OK || !stm) {
					// コメント等、有効なSQLステートメントでないと、戻り値はOKだがstmはNULLになる。
					_tprintf(_TEXT("INSERT用PREPAREDの失敗: %s\n"), sqlite3_errmsg16(dp));
					__leave;
				}
				__try {
					for (int idx = 0; idx < 100; idx++) {
						// パラメータのバインド
						sqlite3_bind_int(stm, 1, idx + 100); // インデックスは1ベース
						if (idx % 2 == 0) {
							// セットされてないバインド変数はNULL扱いとなる。
							// ただし、CLEAR_BINDINGSを呼び出していないと前回の
							// バインド値となる。
							sqlite3_bind_int(stm, 2, idx + 1000);
						}

						// 実行
						ret = sqlite3_step(stm);
						if (ret != SQLITE_DONE) {
							_tprintf(_TEXT("INSERTの失敗: %s\n"), sqlite3_errmsg16(dp));
							__leave;
						}

						// 最後に挿入したROWIDの取得
						const long long rowid = sqlite3_last_insert_rowid(dp);
						_tprintf(_TEXT("ROWID: %I64d\n"), rowid);

						// バインドのリセット
						ret = sqlite3_reset(stm);
						if (ret != SQLITE_OK) {
							_tprintf(_TEXT("RESETの失敗: %s\n"), sqlite3_errmsg16(dp));
							__leave;
						}
						// リセットしてもバインド変数はリセットされないため
						// 明示的にリセットする必要あり。
						ret = sqlite3_clear_bindings(stm);
						if (ret != SQLITE_OK) {
							_tprintf(_TEXT("CLEAR BINDINGSの失敗: %s\n"),
								sqlite3_errmsg16(dp));
							__leave;
						}
					}
				}
				__finally {
					sqlite3_finalize(stm);
				}

				// コミット
				ret = sqlite3_exec(dp, "COMMIT;", NULL, NULL, NULL);
				if (ret != SQLITE_OK) {
					_tprintf(_TEXT("COMMITの失敗: %s\n"), sqlite3_errmsg16(dp));
					__leave;
				}

				// 作成した行の取得
				stm = NULL;
				ret = sqlite3_prepare16(dp, L"SELECT IDX, VAL1, VAL2 FROM TESTTBL ORDER BY IDX",
					-1, &stm, NULL);
				if (ret == SQLITE_OK && stm) {
					// コメント等、有効なSQLステートメントでないと、戻り値はOKだがstmはNULLになる。
					__try {
						// カラム数の取得
						int colCount = sqlite3_column_count(stm);
						_tprintf(_TEXT("カラム数=%d\n"), colCount);
						for (int col = 0; col < colCount; ++col) {
							_tprintf(_TEXT("%d : %s %s\n"), col,
								sqlite3_column_name16(stm, col),
								sqlite3_column_decltype16(stm, col));
						}
						for (;;) {
							ret = sqlite3_step(stm);
							if (ret == SQLITE_ROW) {
								const int idx = sqlite3_column_int(stm, 0); // インデックスは0ベース
								const void* val1 = sqlite3_column_text16(stm, 1);
								const void* val2 = sqlite3_column_text16(stm, 2); // 実数 -> 文字列に
								_tprintf(_TEXT("%d:%s:%s\n"), idx,
									val1 == NULL ? _TEXT("NULL") : val1,
									val2 == NULL ? _TEXT("NULL") : val2);
								continue;
							}
							break;
						}
						if (ret == SQLITE_ERROR) {
							_tprintf(_TEXT("LOOP中の失敗: %s\n"), sqlite3_errmsg16(dp));
						}
					}
					__finally {
						sqlite3_finalize(stm);
					}
				}
				else {
					_tprintf(_TEXT("PREPAREDの失敗: %s\n"), sqlite3_errmsg16(dp));
					__leave;
				}
			}
			__finally {
				sqlite3_close(dp);
				_tprintf(_TEXT("closed\n"));
			}
		
		}
		*/
		void getLastError(void)
		{
			//クラスエラーかSQL命令実行エラーか判別する

			//クラスエラー
			if (Error != ERROR_NONE)
			{
				_tprintf(_T("エラーメッセージ: %ws\n"), _T("何か"));
			}
			//SQL実行エラー
			if ( sqlite3_errcode(db) != SQLITE_OK )
			{
				_tprintf(_T("エラーメッセージ: %s\n"), (_TCHAR *)sqlite3_errmsg16(db));
			}


		}

		
};


#endif/*_SQLACCESS_H_*/