#include "SqlData.h"

unsigned int CSqlData::ColumnSize(void)
{
	return Column.size();
}
unsigned int CSqlData::RecordSize(void)
{
	return Data.size();
}

void CSqlData::Show(void)
{

	//最初にカラム名を入れる
	for (uint i = 0; i < Column.size(); i++)
	{
		//_tprintf(_T(" %-*s"), getField(Column[i].name.c_str(), Column[i].maxLength), Column[i].name.c_str() );
		//_tprintf(_T(" |"));
		_tprintf(
			_T("%s"), 
			Column[i].name.descript((-1) * Column[i].maxLength).c_str()
			);
		_tprintf(_T(" |"));
	}
	_tprintf(_T("\n"));

	//ラインを入れる
	for (uint i = 0; i < Column.size(); i++)
	{
		tstring line;
		line.append(Column[i].maxLength + 1, _T('-'));
		_tprintf(_T("%s-+"), line.c_str());
	}
	_tprintf(_T("\n"));

	//データの表示
	for (uint i = 0; i < Data.size(); i++)
	{
		for (uint j = 0; j < Data[i].size(); j++)
		{

			switch ( Data[i][j].which() )
			{
				case TYPE_INTEGER:
					_tprintf(_T(" %*d"), Column[j].maxLength, Extract<INTEGER>( i, Column[j].name.c_str() )  );
					break;
				case TYPE_TEXT:
					_tprintf(
						_T(" %s"),
						tstring(Extract<TEXT>(i, Column[j].name.c_str())).descript( (-1) * Column[j].maxLength).c_str()
						);
					break;
			}

			_tprintf(_T(" |"));
		}

		_tprintf(_T("\n"));
	}
}

void CSqlData::Clear(void)
{
	Column.clear();
	Data.clear();
}

void CSqlData::AddColumn(LPCTSTR cname, ColumnType ctype)
{
	//Dataが入ってる場合はColumnの追加ができない
	if (Data.size() != 0)
		return;


	CIndex[cname] = Column.size();

	ColumnData column = { cname, ctype };
	Column.push_back(column);

}

void CSqlData::AddColumn(LPCTSTR cname, LPCTSTR ctype)
{
	if (_tcsicmp( ctype, _T("INTEGER")) == 0)
	{
		AddColumn( cname, TYPE_INTEGER );
	}
	else if (_tcsicmp(ctype, _T("TEXT")) == 0)
	{
		AddColumn(cname, TYPE_TEXT );
	}

}

void CSqlData::CheckLength(void)
{
	int i = Data.size() - 1;

	for (uint j = 0; j < Data[i].size(); j++)
	{

		int length = 0;
		//カラム名のサイズも計算に入れる
		if (j == 0)
		{
			length = wcswidth(Column[j].name.c_str(), _tcslen(Column[j].name.c_str()));
		}


		switch (Data[i][j].which())
		{
		case TYPE_INTEGER:
			//文字列にして文字数チェック
			//length = std::to_wstring( Extract<INTEGER>(i, Column[j].name.c_str()) ).length();
			length = to_tstring(Extract<INTEGER>(i, Column[j].name.c_str())).length();
			break;
		case TYPE_TEXT:
			//length = _tcslen(Extract<TEXT>(i, Column[j].name.c_str()));
			length = wcswidth(Extract<TEXT>(i, Column[j].name.c_str()), _tcslen(Extract<TEXT>(i, Column[j].name.c_str())));
			break;
		}

		Column[j].maxLength = length > Column[j].maxLength ? length : Column[j].maxLength;

	}

}



//void CSqlData::AddRecord(unsigned int datanum, .../*std::vector<tstring> record*/)
//{
//	//レコードデータ数がカラム数と違う場合はデータを追加しない
//	if (/*record.size()*/datanum != Column.size())
//		return;
//
//
//
//	//データの整合性をチェックするための一時保管配列
//	//std::vector<tstring> trans;
//
//
//	va_list arg;
//	va_start(arg, datanum);
//
//	for (unsigned int i = 0; i < datanum/*record.size()*/; i++)
//	{
//
//		//Data.push_back(record[i]);
//
//
//		//_EXCEPTION_POINTERS* info;
//		//__try{
//
//
//		//typeid(va_arg());
//
//		if (Column[i].type == TYPE_INTEGER)
//		{
//			Data.push_back(std::to_wstring(va_arg(arg, int)));
//		}
//		else if (Column[i].type == TYPE_TEXT)
//		{
//			Data.push_back(va_arg(arg, LPCTSTR));
//		}
//
//		//va_arg(arg, LPCTSTR);
//
//		//}
//		/*__except (info = GetExceptionInformation(), EXCEPTION_EXECUTE_HANDLER)
//		{
//		va_end(arg);
//		return;
//		}*/
//	}
//
//	//Data = temp;
//
//
//	va_end(arg);
//}