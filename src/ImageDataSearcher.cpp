#include "ImageDataSearcher.h"
#include <algorithm>
#include "../TemplateMatching.h"
#include "NewUnit.h"
#include "NewStage.h"
#include "DataManager.h"
#include "Item.h"

using namespace NewData;
using namespace NewSystem;

/*template<typename C>
CImageDataSearcher<C>::CImageDataSearcher(const CMatchingTarget &Target, const enum class ListType &Type ) : target(Target), type(Type)
{
	SearchData();
}*/
template<>
CImageDataSearcher<CUnitData>::CImageDataSearcher(const CMatchingTarget &Target, const enum class ListType &Type)
	: target(Target), type(Type), threshold( Threshold::ImageSearcher )
{
	SearchData();
}
template<>
CImageDataSearcher<CItemData>::CImageDataSearcher(const CMatchingTarget &Target, const enum class ListType &Type)
	: target(Target), type(Type), threshold( Threshold::ImageSearcher )
{
	SearchData();
}
template<>
CImageDataSearcher<CStageData>::CImageDataSearcher(const CMatchingTarget &Target, const enum class ListType &Type)
	: target(Target), type(Type), threshold( Threshold::StageSearcher )
{
	SearchData();
}


template<typename C>
BOOL CImageDataSearcher<C>::GetResult( std::vector<C> &Result ) const
{
	if (result.empty())
	{
		return FALSE;
	}

	Result = result;

	return TRUE;
}

template<typename C>
double CImageDataSearcher<C>::GetResultValue( void ) const 
{
	return maxvalue;
}

template<typename C>
void CImageDataSearcher<C>::SearchData(void)
{
	//検索結果
	C data;
	maxvalue = 0.0;

	NewSystem::CTemplateMatching match( Threshold::ImageSearcher );
//	NewSystem::CTemplateMatching match(std::map<int, double>({ { Aigis::DefaultWidth, 0.98 } }));


	if (static_cast<int>(type) & static_cast<int>(ListType::LOCAL))
	{
		for (auto& e : NewData::CDataManager<C>::GetInstance().GetLocalData())
		{

			if( !match.Matching(target, e.GetTemplate()))
				continue;

			//仮コード
			if (maxvalue < match.GetMatchValue())
			{
				maxvalue = match.GetMatchValue();
				data = e;
			}
		}
	}
	if (static_cast<int>(type) & static_cast<int>(ListType::GLOBAL))
	{
		for (auto& e : NewData::CDataManager<C>::GetInstance().GetGlobalData())
		{
			if( !match.Matching(target, e.GetTemplate()) )
				continue;

			//仮コード
			if (maxvalue < match.GetMatchValue())
			{
				maxvalue = match.GetMatchValue();
				data = e;
			}

		}
	}
	if (maxvalue >= 0.95)
	{
		//DEBUG_LOG(LOG_CONSOLE, "該当ユニット : %s  value : %lf", data.GetName().c_str(), maxvalue);
		result.push_back(data);
	}
	else
	{
		//DEBUG_LOG(LOG_CONSOLE, "該当ユニットなし");
	}
}

/*
template<>
void CImageDataSearcher<CUnitData>::SearchData( void )
{
	//検索結果
	CUnitData data;
	maxvalue = 0.0;

	NewSystem::CTemplateMatching match(CThreshold({ {SCREEN_WIDTH::value, 0.95 } }));

	if (static_cast<int>(type) & static_cast<int>(ListType::LOCAL))
	{

		for (auto& e : UnitData::GetInstance().GetLocalData())
		{

			match.Matching(target, e.GetTemplate());
			
			//仮コード
			if (maxvalue < match.GetMatchValue())
			{
				maxvalue = match.GetMatchValue();
				data = e;
			}

		}
	}
	if (static_cast<int>(type) & static_cast<int>(ListType::GLOBAL))
	{
		for (auto& e : UnitData::GetInstance().GetGlobalData())
		{
			match.Matching(target, e.GetTemplate());

			//仮コード
			if (maxvalue < match.GetMatchValue())
			{
				maxvalue = match.GetMatchValue();
				data = e;
			}

		}
	}

	if (maxvalue >= 0.95)
	{
		//DEBUG_LOG(LOG_CONSOLE, "該当ユニット : %s  value : %lf", data.GetName().c_str(), maxvalue);
		result.push_back(data);
	}
	else
	{
		//DEBUG_LOG(LOG_CONSOLE, "該当ユニットなし");
	}
}

template<>
void CImageDataSearcher<CStageData>::SearchData(void)
{
	CStageData data;
	double maxvalue = 0.0;

	NewSystem::CTemplateMatching match(CThreshold({ { SCREEN_WIDTH::value, 0.95 } }));

	if (static_cast<int>(type) & static_cast<int>(ListType::LOCAL))
	{

		for (auto& e : StageData::GetInstance().GetLocalData())
		{

			match.Matching(target, e.GetTemplate());

			//仮コード
			if (maxvalue < match.GetMatchValue())
			{
				maxvalue = match.GetMatchValue();
				data = e;
			}

		}
	}
	if (static_cast<int>(type) & static_cast<int>(ListType::GLOBAL))
	{
		for (auto& e : StageData::GetInstance().GetGlobalData())
		{
			match.Matching(target, e.GetTemplate());

			//仮コード
			if (maxvalue < match.GetMatchValue())
			{
				maxvalue = match.GetMatchValue();
				data = e;
			}

		}
	}



	if (maxvalue >= 0.95)
	{
		//DEBUG_LOG(LOG_CONSOLE, "該当ステージ : %s  value : %lf", data.GetName().c_str(), maxvalue);
		result.push_back(data);
	}
	else
	{
		//DEBUG_LOG(LOG_CONSOLE, "該当ステージなし");
	}
}*/



template class CImageDataSearcher<CUnitData>;
template class CImageDataSearcher<CStageData>;
template class CImageDataSearcher<CItemData>;