#include "SqlAccess.h"

tstring upperstr(LPCTSTR psz)
{
	tstring buf = psz;


	for (unsigned int pos = 0; pos < buf.size(); ++pos) {
		buf.at(pos) = _totupper((wint_t)buf.at(pos));
	}

	return buf;
}

tstring lowerstr(LPCTSTR psz)
{
	tstring buf = psz;


	for (unsigned int pos = 0; pos < buf.size(); ++pos) {
		buf.at(pos) = _totlower((wint_t)buf.at(pos));
	}

	return buf;
}

CSqlAccess::CSqlAccess(tstring filename) : db((sqlite3 *)NULL)
{
	Error = ERROR_NONE;
	Load(filename.c_str());
}

CSqlAccess::CSqlAccess(LPCTSTR filename) : db((sqlite3 *)NULL)
{
	Error = ERROR_NONE;
	Load(filename);
}

CSqlAccess::~CSqlAccess()
{
	UnLoad();
}

BOOL CSqlAccess::Load(LPCTSTR filename)
{
	db = (sqlite3 *)NULL;

	if (sqlite3_open16(filename, &db) != SQLITE_OK) {
		
		UnLoad();
		return FALSE;
	}

	return TRUE;

}

void CSqlAccess::UnLoad(void)
{
	if (db != (sqlite3 *)NULL)
	{
		sqlite3_close(db);
		db = (sqlite3 *)NULL;
	}
}

BOOL CSqlAccess::Select(SqlData cache, LPCTSTR table, const std::vector<tstring> columns, LPCTSTR order)
{
	//----SQL文の生成開始----
	tstring state = _T("select ");
	//カラム
	for (auto iterator = columns.begin(); iterator < columns.end(); iterator++)
	{
		state += iterator->c_str();

		if (iterator < columns.end() - 1)
			state += _T(", ");
		else
			state += _T(" ");
	}
	//table
	state += _T("from ");
	state += table;

	//オーダーの項目があれば追加する
	if (order != NULL)
	{
		state += _T(" order by ");
		state += order;
	}

	//SELECT処理の本体
	return Select(cache, state.c_str());

}

BOOL CSqlAccess::Select(SqlData cache, LPCTSTR sqlStatement)
{

	//DBを開いてなければ処理を終了する
	if (db == (sqlite3 *)NULL)
		return FALSE;

	//キャッシュをクリアする
	cache->Clear();


	int result;
	result = sqlite3_prepare16(db, sqlStatement, -1, &stmt, NULL);

	// コメント等、有効なSQLステートメントでないと、戻り値はOKだがstmはNULLになる。
	if (result != SQLITE_OK && stmt == NULL) {
		return FALSE;
	}

	// カラム数の取得
	int colCount = sqlite3_column_count(stmt);
	//_tprintf(_TEXT("カラム数=%d\n"), colCount);
	for (int col = 0; col < colCount; ++col) 
	{		
		cache->AddColumn((_TCHAR *)sqlite3_column_name16(stmt, col), (_TCHAR *)sqlite3_column_decltype16(stmt, col));
	}

	//レコードデータの抽出
	//CSqlRecord record(colCount);
	for (;;) {
		result = sqlite3_step(stmt);
		if (result == SQLITE_ROW) {
			cache->Begin();
			
			for (int col = 0; col < colCount; ++col)
			{
				if (cache->GetColumnType(col) == cache->TYPE_INTEGER)
				{
					cache->AddData((int)sqlite3_column_int(stmt, col));
				}
				else if(cache->GetColumnType(col) == cache->TYPE_TEXT)
				{
					cache->AddData((_TCHAR *)sqlite3_column_text16(stmt, col));
				}
			}

			cache->Commit();

			continue;
		}
		break;
	}
	if (result == SQLITE_ERROR) {
//		_tprintf(_TEXT("データ取得失敗: %s\n"), sqlite3_errmsg16(db));
		return FALSE;
	}

	return TRUE;
}

BOOL CSqlAccess::insert(SqlData cache, LPCTSTR sqlStatement)
{
	//L"INSERT INTO myunit_tbl(name, icon)" L"VALUES(?, ?)"

	//DBを開いているか？
	if (db == (sqlite3 *)NULL)
		return FALSE;

	//カラムチェックここ

	//----データ追加処理----
	int result;
	BOOL isSuccess = FALSE;

	//トランザクションの開始
	result = sqlite3_exec(db, "BEGIN;", NULL, NULL, NULL);
	if (result != SQLITE_OK) 
	{
		//エラー処理ここ
		return FALSE;
	}

	__try 
	{
		result = sqlite3_prepare16(db, sqlStatement, -1, &stmt, NULL);
		if (result != SQLITE_OK || !stmt) {
			// コメント等、有効なSQLステートメントでないと、戻り値はOKだがstmはNULLになる。
			_tprintf(_TEXT("INSERT用PREPAREDの失敗: %s\n"), (_TCHAR *)sqlite3_errmsg16(db));
			__leave;
		}

		for ( uint i = 0; i < cache->RecordSize(); ++i )
		{
			for (uint j = 0; j < cache->ColumnSize(); ++j)
			{
				if (cache->GetColumnType(j) == cache->TYPE_INTEGER)
				{
					sqlite3_bind_int(stmt, j+1, cache->Extract<INTEGER>( i, j ) );  // インデックスは1ベース
				}
				else if (cache->GetColumnType(j) == cache->TYPE_TEXT)
				{
					sqlite3_bind_text16(stmt, j + 1, cache->Extract<TEXT>(i, j), _tcslen( cache->Extract<TEXT>(i, j) ) * sizeof(_TCHAR), SQLITE_STATIC );
				}
				//cache->getColumnName(j);

			}

			// 実行
			result = sqlite3_step(stmt);
			if (result != SQLITE_DONE) {
				_tprintf(_TEXT("INSERTの失敗: %s\n"), (_TCHAR *)sqlite3_errmsg16(db));
				__leave;
			}

			// 最後に挿入したROWIDの取得
			const long long rowid = sqlite3_last_insert_rowid(db);
			_tprintf(_TEXT("ROWID: %I64d\n"), rowid);


			// バインドのリセット
			result = sqlite3_reset(stmt);
			if (result != SQLITE_OK) {
				_tprintf(_TEXT("RESETの失敗: %s\n"), (_TCHAR *)sqlite3_errmsg16(db));
				__leave;
			}
			// リセットしてもバインド変数はリセットされないため
			// 明示的にリセットする必要あり。
			result = sqlite3_clear_bindings(stmt);
			if (result != SQLITE_OK) {
				_tprintf(_TEXT("CLEAR BINDINGSの失敗: %s\n"), (_TCHAR *)sqlite3_errmsg16(db));
				__leave;
			}

		}

		/*for (int idx = 0; idx < 100; idx++) {
			// パラメータのバインド
			sqlite3_bind_int(stmt, 1, idx + 100);
			if (idx % 2 == 0) {
				// セットされてないバインド変数はNULL扱いとなる。
				// ただし、CLEAR_BINDINGSを呼び出していないと前回の
				// バインド値となる。
				sqlite3_bind_int(stmt, 2, idx + 1000);
			}

			// 実行
			result = sqlite3_step(stmt);
			if (result != SQLITE_DONE) {
				_tprintf(_TEXT("INSERTの失敗: %s\n"), sqlite3_errmsg16(db));
				__leave;
			}

			// 最後に挿入したROWIDの取得
			const long long rowid = sqlite3_last_insert_rowid(db);
			_tprintf(_TEXT("ROWID: %I64d\n"), rowid);

			// バインドのリセット
			result = sqlite3_reset(stmt);
			if (result != SQLITE_OK) {
				_tprintf(_TEXT("RESETの失敗: %s\n"), sqlite3_errmsg16(db));
				__leave;
			}
			// リセットしてもバインド変数はリセットされないため
			// 明示的にリセットする必要あり。
			result = sqlite3_clear_bindings(stmt);
			if (result != SQLITE_OK) {
				_tprintf(_TEXT("CLEAR BINDINGSの失敗: %s\n"), sqlite3_errmsg16(db));
				__leave;
			}
		}*/

		isSuccess = TRUE;

	}
	__finally 
	{
		sqlite3_finalize(stmt);
	}

	//データ追加が成功しているか
	if (isSuccess == TRUE)
	{
		//成功していればコミット
		result = sqlite3_exec(db, "COMMIT;", NULL, NULL, NULL);
		if (result != SQLITE_OK)
		{
			sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
			//エラー処理ここ(ロールバック処理ここ)
			return FALSE;
		}
	}
	else
	{
		sqlite3_exec(db, "ROLLBACK;", NULL, NULL, NULL);
		return FALSE;
	}

	return TRUE;
}


BOOL CSqlAccess::CreateTable(LPCTSTR sqlStatement)
{
	int result;

	result = sqlite3_prepare16(db, sqlStatement, -1, &stmt, NULL);
	if (result != SQLITE_OK || stmt == NULL)
		return FALSE;
	result = sqlite3_step(stmt);
	if (result != SQLITE_DONE)
		return FALSE;
	result = sqlite3_finalize(stmt);
	if (result != SQLITE_OK)
		return FALSE;


	return TRUE;

}

BOOL CSqlAccess::DeleteTable(LPCTSTR sqlStatement)
{
	int result = sqlite3_exec( db, convert<char>( sqlStatement ).c_str(), NULL, NULL, NULL);
	
	if (result != SQLITE_OK)
		return FALSE;
	else
		return TRUE;
}



BOOL CSqlAccess::exec(SqlData cache, LPCTSTR sqlStatement)
{

	//全て大文字に変換した文字列を作成
	tstring upper = upperstr(sqlStatement);

	//命令を認識する
	//Select
	if (_tcsstr(upper.c_str(), _T("SELECT")) == upper.c_str())
	{
		return Select(cache, sqlStatement);
	}
	//Create Table
	else if ( _tcsstr(upper.c_str(), _T("CREATE TABLE")) == upper.c_str() )
	{
		return CreateTable( sqlStatement );
	}
	//Delete Table
	else if(_tcsstr(upper.c_str(), _T("DROP TABLE")) == upper.c_str())
	{
		return DeleteTable( sqlStatement );
	}
	//テスト用にここに実装
	else
	{
		return CreateTable(sqlStatement);

	}
	
	//SQL文のエラーの場合こちら
	Error = ERROR_STATEMENT;
	return FALSE;
}

BOOL CSqlAccess::exec( LPCTSTR sqlstatement )
{
	return exec( NULL, sqlstatement );
}

