#include "Stdafx.h"

#include "DataManager.h"

#include "SqlAccess.h"
#include "SqlData.h"
//#include "../TemplateMatching.h"
//#include "ImageDataSearcher.h"
#include "Path.h"

using namespace Aigis_DB;

template< class C >
CDataManager<C>::CDataManager() {}
template< class C >
CDataManager<C>::~CDataManager() {};

template< class C >
inline const std::vector<C> &CDataManager<C>::GetLocalData() const
{
	return local;
}
template< class C >
inline const std::vector<C> &CDataManager<C>::GetGlobalData() const
{
	return global;
}

//ユニット専用コード
//パス関係
//const tstring GUNIT_DIR = _T("template\\unit\\");
//const tstring LUNIT_DIR = _T("template\\myunit\\");
//const tstring LDB_DIR = LUNIT_DIR + _T("myunit.db");
template<>
void CDataManager<CUnitData>::Load(void)
{

	global.push_back(
		CUnitData(
			_T("モニカ"), 
			CTemplateImage(( DirPath::UNIT_GLOBAL + _T("5bc9b7cf42f135d995d03dc11524ef70.png")).c_str()),
			_T("パイレーツ"),
			UnitRarity::GOLD
			)
		);
	global.push_back(
		CUnitData(
			_T("キュテリ"),
			CTemplateImage(( DirPath::UNIT_GLOBAL + _T("5bc9b7cf42f135d995d03dc11524ef70.png")).c_str()),
			_T("ローグ"),
			UnitRarity::GOLD
			)
		);
	global.push_back(
		CUnitData(
			_T("ロベルト"),
			CTemplateImage((DirPath::UNIT_GLOBAL + _T("5bc9b7cf42f135d995d03dc11524ef70.png")).c_str()),
			_T("ヒーラー"),
			UnitRarity::GOLD
			)
		);
	global.push_back(
		CUnitData(
			_T("レダ"),
			CTemplateImage((DirPath::UNIT_GLOBAL + _T("5bc9b7cf42f135d995d03dc11524ef70.png")).c_str()),
			_T("シーフ"),
			UnitRarity::GOLD
			)
		);

	//ローカルデータのロード(ここでdbファイル、テーブルも必要があれば新規作成する)
	SqlAccess saccess = new CSqlAccess( DBPath::UNIT_LOCAL );
	if (!saccess->CreateTable(_T("create table myunit_tbl(id INTEGER PRIMARY KEY, name text, icon text, matchsize INTEGER);")))
	{
		SqlData sdata = new CSqlData();
		saccess->Select(sdata, _T("myunit_tbl"), { _T("name"), _T("icon"), _T("matchsize") }, NULL);

		//sdataのレコード内容に合わせてローカルユニットデータの読込処理を行う
		for (uint i = 0; i < sdata->RecordSize(); ++i)
		{
			local.push_back(
				CUnitData(
					sdata->Extract<TEXT>(i, _T("name")),
					CTemplateImage(
						( DirPath::UNIT_LOCAL + sdata->Extract<TEXT>(i, _T("icon")) + _T(".png")).c_str(),
						sdata->Extract<INTEGER>(i, _T("matchsize"))
						),
					_T(""),
					UnitRarity::NODATA
				)
			);

		}

		delete sdata;
	}
	delete saccess;
	

	//ローカルデータのマージ処理
	Merge();
}
template<>
void CDataManager<CUnitData>::Merge(void)
{
	/*
	for (auto& e : CDataManager<CUnitData>::GetInstance().GetLocalData())
	{
		std::vector<CUnitData> cdata;
		if (
			CImageDataSearcher<CUnitData>(
				e.GetTemplate(),
				ListType::GLOBAL 
				).GetResult( cdata ) 
			)
		{
			//----SQLデータ更新----
			//データを共通データに変換する
			tstring before = e.GetName();
			tstring after  = cdata[0].GetName();

			SqlAccess saccess = new CSqlAccess(_T(".\\score.dat"));
			int dropnum;
			for (dropnum = 1; dropnum <= 7; ++dropnum)
			{

				tstring statement = _T("update score_tbl set drop") + to_tstring(dropnum) + _T("= '") + after + _T("' Where drop") + to_tstring(dropnum) + _T("= '") + before + _T("';");
				if (!saccess->exec(statement.c_str()))
					break;
			}

			delete saccess;

			//SQLの更新が成功した場合のみ
			if (dropnum > 7)
			{
				tstring statement;
				//ローカルからレコードと画像ファイルを削除
				saccess = new CSqlAccess(LDB_DIR);
				//データベースから削除するファイル名を取得
				CSqlData sdata;
				statement = _T("SELECT name FROM myunit_tbl WHERE name = '") + before + _T("';");
				saccess->Select(&sdata, statement.c_str());

				//レコードの削除
				statement = _T("delete from myunit_tbl where name = '") + before + _T("';");
				saccess->exec(statement.c_str());
				delete saccess;


				//ファイルを削除
				for (uint i = 0; i < sdata.RecordSize(); ++i)
				{
					DeleteFile((LUNIT_DIR + sdata.Extract<TEXT>(i, _T("name")) + _T(".png")).c_str());
				}

			}
		}
	}

	//アイテム用
	for (auto& e : UnitData::GetInstance().GetLocalData())
	{
		std::vector<CItemData> cdata;
		if (
			CImageDataSearcher<CItemData>(
				e.GetTemplate(),
				ListType::GLOBAL
				).GetResult(cdata)
			)
		{
			//----SQLデータ更新----
			//データを共通データに変換する
			tstring before = e.GetName();
			tstring after = cdata[0].GetName();

			SqlAccess saccess = new CSqlAccess(_T(".\\score.dat"));
			int dropnum;
			for (dropnum = 1; dropnum <= 7; ++dropnum)
			{

				tstring statement = _T("update score_tbl set drop") + to_tstring(dropnum) + _T("= '") + after + _T("' Where drop") + to_tstring(dropnum) + _T("= '") + before + _T("';");
				if (!saccess->exec(statement.c_str()))
					break;
			}

			delete saccess;

			//SQLの更新が成功した場合のみ
			if (dropnum > 7)
			{
				tstring statement;
				//ローカルからレコードと画像ファイルを削除
				saccess = new CSqlAccess(LDB_DIR);
				//データベースから削除するファイル名を取得
				CSqlData sdata;
				statement = _T("SELECT name FROM myunit_tbl WHERE name = '") + before + _T("';");
				saccess->Select(&sdata, statement.c_str());

				//レコードの削除
				statement = _T("delete from myunit_tbl where name = '") + before + _T("';");
				saccess->exec(statement.c_str());
				delete saccess;


				//ファイルを削除
				for (uint i = 0; i < sdata.RecordSize(); ++i)
				{
					DeleteFile((LUNIT_DIR + sdata.Extract<TEXT>(i, _T("name")) + _T(".png")).c_str());
				}

			}
		}
	}

	*/



	//Matching match = new CTemplateMatching();

	//for (auto i = local.begin(), n = local.end(); i < n; ++i)
	//{
	//	CData *data = NULL;
	//	double maxValue = 0.0;

	//	for (auto j = global.begin(); j < global.end(); ++j)
	//	{
	//		match->Matching(i->GetImage().Resize(960), j->GetImage().Resize(960));
	//		if (match->getMaxValue() > maxValue)
	//		{
	//			maxValue = match->getMaxValue();
	//			data = &*j;
	//		}
	//	}

	//	//該当したデータを検証
	//	if (maxValue >= 0.95)
	//	{
	//		//データを共通データに変換する
	//		tstring before = i->GetName();
	//		tstring after = data->GetName();

	//		SqlAccess saccess = new CSqlAccess(_T(".\\score.dat"));
	//		int dropnum;
	//		for (dropnum = 1; dropnum <= 7; ++dropnum)
	//		{

	//			tstring statement = _T("update score_tbl set drop") + to_tstring(dropnum) + _T("= '") + after + _T("' Where drop") + to_tstring(dropnum) + _T("= '") + before + _T("';");
	//			if (!saccess->exec(statement.c_str()))
	//				break;
	//		}

	//		delete saccess;

	//		//SQLの更新が成功した場合のみ
	//		if (dropnum > 7)
	//		{
	//			tstring statement;
	//			//ローカルからレコードと画像ファイルを削除
	//			saccess = new CSqlAccess(LDB_DIR);
	//			//データベースから削除するファイル名を取得
	//			CSqlData sdata;
	//			statement = _T("SELECT name FROM myunit_tbl WHERE name = '") + before + _T("';");
	//			saccess->Select(&sdata, statement.c_str());

	//			//レコードの削除
	//			statement = _T("delete from myunit_tbl where name = '") + before + _T("';");
	//			saccess->exec(statement.c_str());
	//			delete saccess;


	//			//ファイルを削除
	//			for (uint i = 0; i < sdata.RecordSize(); ++i)
	//			{
	//				DeleteFile((LUNIT_DIR + sdata.Extract<TEXT>(i, _T("name")) + _T(".png")).c_str());
	//			}

	//		}

	//	}

	//}

	//delete match;


	//CImageDataSearcher<NewData::CUnitData> test( 
	//	CMatchingTarget( 
	//		global[0].GetImage().GetImage(), 
	//		CRange(
	//			0,
	//			0,
	//			global[0].GetImage().GetImage().cols, 
	//			global[0].GetImage().GetImage().rows, 
	//			global[0].GetImage().GetMatchSize()
	//			) 
	//		) , 
	//	ListType::ALL);

	//std::vector<CUnitData> data;
	//if (test.GetResult(data))
	//{
	//	_tprintf(_T("%s"), data[0].GetName()  );
	//}







}

//ステージ専用コード
template<>
void CDataManager<CStageData>::Load(void)
{

}
template<>
void CDataManager<CStageData>::Merge(void)
{

}

template<>
void CDataManager<CItemData>::Load(void)
{
	
	SqlAccess saccess = new CSqlAccess(DBPath::ITEM_GLOBAL);
	//if (!saccess->CreateTable(_T("create table myunit_tbl(id INTEGER PRIMARY KEY, name text, icon text, matchsize INTEGER);")))
	//{
	SqlData sdata = new CSqlData();
	
	saccess->Select(sdata, _T("item_tbl"), { _T("name"), _T("icon") }, NULL);

	//データサイズを設定する
	global.reserve(sdata->RecordSize());
	//sdataのレコード内容に合わせてローカルユニットデータの読込処理を行う
	for (uint i = 0, n = sdata->RecordSize(); i < n ; ++i)
	{
		global.push_back(
			CItemData(
				sdata->Extract<TEXT>(i, _T("name")),
				CTemplateImage(
					(DirPath::ITEM_GLOBAL + sdata->Extract<TEXT>(i, _T("icon")) + _T(".png")).c_str(),
					960 
					)
				)
			);

		//画像ファイルの読込が失敗していればデータを除外する
		if ((global.end() - 1)->GetTemplate().GetLastError())
		{
			global.erase(global.end() - 1);
		}
	}

	delete sdata;

	delete saccess;
	

}

template<>
void CDataManager<CItemData>::Merge(void)
{

}


template< class C >
void CDataManager<C>::AddLocalData(const C &data)
{
	local.push_back(data);
}
/*template< class C >
void CDataManager<C>::AddLocalData(const CData &data)
{
	//local.push_back(data);
}*/


// 明示的テンプレートのインスタンス化
template class CDataManager<CUnitData>;
template class CDataManager<CStageData>;
template class CDataManager<CItemData>;

//スレッドセーフ用グローバル宣言
static CDataManager<CUnitData>  &data  = CDataManager<CUnitData>::GetInstance();
static CDataManager<CStageData> &stage = CDataManager<CStageData>::GetInstance();
static CDataManager<CItemData>  &item  = CDataManager<CItemData>::GetInstance();

