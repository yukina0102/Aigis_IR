#ifndef _NEWSTAGE_H_
#define _NEWSTAGE_H_

#pragma once

#include "DataCommon.h"


namespace Aigis_DB 
{

enum class MissionType	
{
	NODATA,
	STORY,		//ストーリーミッション
	DAILY,		//曜日ミッション
	CHALLENGE,	//チャレンジ
	URGENT,		//緊急ミッション
	REPRINT,
};

class CStageData : public CDataCommon
{
public:
	CStageData()
		: CDataCommon( _T(""), CTemplateImage(_T("")) ), charisma(0), stamina(0), missiontype(MissionType::NODATA)
	{}
	CStageData( const tstring &Name, const CTemplateImage &TImage, const enum class MissionType &Type )
		: CDataCommon( Name, TImage ), missiontype(Type)
	{}
	CStageData(const CDataCommon& Data)
		: CDataCommon( Data ), charisma(0), stamina(0), missiontype(MissionType::NODATA)
	{}
private:
	int charisma;
	int stamina;
	enum class MissionType missiontype;
	std::vector<tstring> drop;
};}


#endif/*_NEWSTAGE_H_*/
