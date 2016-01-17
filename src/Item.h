#ifndef _ITEM_H_
#define _ITEM_H_

#pragma once

#include "DataCommon.h"

namespace Aigis_DB {

class CItemData : public CDataCommon
{

public:
	CItemData()
		: CDataCommon()
	{}
	CItemData(const tstring &Name, const CTemplateImage &Image )
		: CDataCommon( Name, Image )
	{}
	CItemData( const CDataCommon& Data )
		: CDataCommon(Data)
	{}

	virtual ~CItemData() 
	{}

};

}

#endif/*_ITEM_H_*/
