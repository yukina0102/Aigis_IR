#ifndef _DATAMANAGER_H_
#define _DATAMANAGER_H_

#pragma once

#include "common.h"
#include "Common/Singleton.h"

#include "Stage.h"
#include "Unit.h"
#include "Item.h"

namespace Aigis_DB{

template<class C>
class CDataManager : public Singleton<CDataManager<C>>
{
	friend class Singleton<CDataManager<C>>;

//コンストラクタ、デストラクタ
private:
	CDataManager(); // 外部でのインスタンス作成は禁止
	virtual ~CDataManager();

//アクセサ
public:
	const std::vector<C> &GetLocalData() const;
	const std::vector<C> &GetGlobalData() const;

//メソッド
public:
	virtual void Load(void);
private:
	virtual void Merge(void);
public:
	virtual void AddLocalData(const C &data);
	//virtual void AddLocalData(const CData &data);

//メンバ
private:
	std::vector<C> local;
	std::vector<C> global;

};

template<typename C>
struct DataBase
{
	static const std::vector<C> LocalData( void )
	{
		return CDataManager<C>::GetInstance().GetLocalData();
	}
	static const std::vector<C> GlobalData( void )
	{
		return CDataManager<C>::GetInstance().GetGlobalData();
	}

	static void Load(void)
	{
		CDataManager<C>::GetInstance().Load();
	}

	static void AddLocal( const C &Data )
	{
		CDataManager<C>::GetInstance().AddLocal( Data );
	}

};

typedef struct DataBase<CStageData> StageData;
typedef struct DataBase<CUnitData>  UnitData;
typedef struct DataBase<CItemData>  ItemData;

}

#endif/*_DATAMANAGER_H_*/