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
//�R���X�g���N�^�A�f�X�g���N�^
public:
	CImageDataSearcher(const CMatchingTarget &Target, const enum class ListType &Type );

//�A�N�Z�T�[
public:
	BOOL   GetResult(std::vector<C> &Result) const;
	double GetResultValue(void) const;

private:
	void SearchData(void);

//�����o
private:
	CMatchingTarget target;
	enum class ListType type;
	
	//�}�b�`���O臒l
	CThreshold threshold;

	std::vector<C> result;
	double maxvalue;
};

#endif/*_IMAGEDATASEARCHER_H_*/