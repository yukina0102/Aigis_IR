#ifndef _DATASEARCHER_H_
#define _DATASEARCHER_H_

#pragma once

#include "common.h"


namespace NewData {

template<class C>
class CDataSearcherBase
{

//コンストラクタ、デストラクタ
public:
	CDataSearcherBase() {}
	CDataSearcherBase(const std::vector<C> &datalist, tstring string) : targetlist(datalist), name(string)
	{
		SearchName();
	}
	CDataSearcherBase(const CDataSearcherBase<C> &sercher, tstring string) : targetlist(sercher.GetResultList()), name(string)
	{
		SearchName();
	}
	virtual ~CDataSearcherBase(void) {}


//アクセサー
public:
	virtual const std::vector<C> &GetResultList() const
	{
		return resultlist;
	}
private:
	inline void SetTargetList(const std::vector<C> &datalist)
	{
		targetlist = datalist;
	}
	inline void SetSearchName(const tstring &string )
	{
		name = string;
	}

private:
	//void SearchRarity(void);
	virtual void SearchName(void) 
	{
			std::copy_if(
				targetlist.begin(), 
				targetlist.end(),
				std::back_inserter(resultlist), 
				[&](C &data) { return data.GetName() == name; }
			);
	}


protected:
	std::vector<C> targetlist;
	std::vector<C> resultlist;

	//検索条件
	tstring         name;
	
};}





#endif/*_DATASEARCHER_H_*/
