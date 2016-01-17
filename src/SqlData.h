#ifndef SQLDATA_H
#define SQLDATA_H

#include "common.h"


typedef class CSqlData * SqlData;
typedef class CSqlRecord * SqlRecord;

//DB側で指定される型名をプログラム内の型に変換
typedef const int INTEGER;
typedef const _TCHAR * TEXT;

class CSqlData
{
	public:
		typedef enum
		{
			TYPE_INTEGER = 0,
			TYPE_TEXT,
		}ColumnType;

	private:
		//CulumnTypeとvariantの中身は一致させておく
		typedef boost::variant< int, tstring > SqlVar;

		typedef struct ColumnData
		{
			tstring name;
			ColumnType type;
			int maxLength;
		}ColumnData;


	private:
		std::vector< ColumnData > Column;
		std::map< tstring, uint > CIndex;

		//std::vector< tstring > Data;
		
		std::vector< std::vector< SqlVar > > Data;

		//レコード一時保管用
		std::vector< SqlVar > Tmp;


	public:
		CSqlData(){}

		uint ColumnSize(void);
		uint RecordSize(void);
	
		void Show(void);
		void Clear(void);

		//カラム、レコードの追加
		void AddColumn(LPCTSTR cname, ColumnType ctype);
		void AddColumn(LPCTSTR cname, LPCTSTR ctype );

		void CheckLength(void);

		//void AddRecord(const SqlRecord record);

		//レコード一時保管関係
		void Begin()
		{
			Tmp.clear();
		}
		void Begin( uint num )
		{
			Tmp.clear();
			Tmp.resize( num );
		}

		void AddData( boost::variant< int, tstring >  data )
		{
			Tmp.push_back( data );
		}


		void Commit()
		{
			//レコードデータ数がカラム数と違う場合はデータを追加しない
			if ( Tmp.size() != Column.size())
				return;

			Data.push_back( Tmp );

			//各カラムの最大文字数を保存
			CheckLength();
		}


		
		ColumnType GetColumnType(unsigned int num)
		{
			return Column[num].type;
		}
		ColumnType GetColumnType(LPCTSTR column)
		{
			GetColumnType(CIndex[column]);
		}

		tstring getColumnName(uint num)
		{
			return Column[num].name;
		}

		//データ抽出
		template<typename result_t>
		inline result_t Extract( uint record, LPCTSTR column);

		template<typename result_t>
		inline result_t Extract(uint record, uint cnum );

};


template<>
inline INTEGER CSqlData::Extract<INTEGER>(unsigned int record, LPCTSTR column)
{
	//指定したカラム
	if (record >= Data.size() || CIndex.find(column) == CIndex.end())
	{
		return -1;
	}

	if (Column[CIndex[column]].type != TYPE_INTEGER )
	{
		return -1;
	}

	return boost::get<int>( Data[record][CIndex[column]] );
}

template<>
inline TEXT CSqlData::Extract<TEXT>(unsigned int record, LPCTSTR column)
{

	//指定したカラム
	if (record >= Data.size() || CIndex.find(column) == CIndex.end())
	{
		return _T("Data Error");
	}

	if (Column[CIndex[column]].type != TYPE_TEXT)
	{
		return _T("Data Error");
	}

	return boost::get<tstring>(Data[record][CIndex[column]]).c_str();

}

template<>
inline INTEGER CSqlData::Extract<INTEGER>( uint record, uint cnum )
{
	//指定したカラム
	if (record >= Data.size() || cnum >= ColumnSize() )
	{
		return -1;
	}

	if (Column[cnum].type != TYPE_INTEGER)
	{
		return -1;
	}

	return boost::get<int>(Data[record][cnum]);
}

template<>
inline TEXT CSqlData::Extract<TEXT>( uint record, uint cnum )
{

	//指定したカラム
	if (record >= Data.size() || cnum >= ColumnSize() )
	{
		return _T("Data Error");
	}

	if (Column[cnum].type != TYPE_TEXT)
	{
		return _T("Data Error");
	}

	return boost::get<tstring>(Data[record][cnum]).c_str();

}




#endif/*SQLDATA_H*/