#ifndef _UNITDATA_H_
#define _UNITDATA_H_

#pragma once

#include "Common/tString.h"
#include "Common/Singleton.h"
#include "DataCommon.h"

namespace Aigis_DB{

enum class UnitRarity
{
	NODATA,
	IRON,
	BRONZE,
	SILVER,
	GOLD,
	PLATINUM,
	BLACK,
};

//ユニットデータ
class CUnitData : public CDataCommon
{

public:
	CUnitData()
		: CDataCommon(_T(""), CTemplateImage(_T(""))), classname(_T("")), rarity(UnitRarity::NODATA)
	{}

	CUnitData(const tstring &name, const CTemplateImage &image, const tstring &classname, enum class UnitRarity rare)
		: CDataCommon(name, image)
	{
		Create(classname, rare);
	}
	CUnitData(const CDataCommon& Data)
		: CDataCommon( Data ), classname(_T("")),rarity(UnitRarity::NODATA) {}
	virtual ~CUnitData() {}

//アクセサー
public:
	inline enum class UnitRarity GetRarity(void)
	{
		return rarity;
	}


private:
	void Create( const tstring &classname, enum class UnitRarity rare)
	{
		//CData::Create(name, image);
		this->classname = classname;
		this->rarity = rare;
	} 

private:
	tstring classname;
	enum class UnitRarity rarity;

};

}

#define UNITDATA_NULL NewData::CUnitData( _T(""), CTemplateImage(_T("")), _T(""), NewData::UnitRarity::NODATA  )


#endif/*_UNITDATA_H_*/