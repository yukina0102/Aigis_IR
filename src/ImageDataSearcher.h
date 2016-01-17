#ifndef _IMAGEDATASEARCHER_H_
#define _IMAGEDATASEARCHER_H_

#pragma once

#include "../ImageProcess.h"
#include "../TemplateMatching.h"

enum class ListType
{
	GLOBAL = 1 << 0,
	LOCAL  = 1 << 1,
	ALL    = GLOBAL | LOCAL,
};

template<typename C>
class CImageDataSearcher
{
//コンストラクタ、デストラクタ
public:
	CImageDataSearcher(const CMatchingTarget &Target, const enum class ListType &Type );

//アクセサー
public:
	BOOL   GetResult(std::vector<C> &Result) const;
	double GetResultValue(void) const;

private:
	void SearchData(void);

//メンバ
private:
	CMatchingTarget target;
	enum class ListType type;
	
	//マッチング閾値
	CThreshold threshold;

	std::vector<C> result;
	double maxvalue;
};

#endif/*_IMAGEDATASEARCHER_H_*/