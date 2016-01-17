#include "TemplateImage.h"

CTemplateImage::CTemplateImage() {}
CTemplateImage::CTemplateImage(const _TCHAR *filename, const int &matchsize )
{
	Create(filename, matchsize);
}
CTemplateImage::CTemplateImage(const tstring &filename, const int &matchsize )
{
	Create(filename.c_str(), matchsize);
}
CTemplateImage::CTemplateImage(const cv::Mat &mat, const int &matchsize )
{
	image = mat.clone();
	matchSize = matchsize;
}
CTemplateImage::~CTemplateImage() {}

void CTemplateImage::Create( const tstring &filename, const int &matchsize)
{
	//画像を読込
	image = cv::imread(convert<char>(filename));
	if (image.data == NULL)
	{
		SetError(this->ERROR_LOAD, (_T("filename : ") + filename) );
	}
	//ダイアログのための仮実装
	else
	{
		icon = filename;

		auto i = icon.find_last_of(_T("\\"), icon.size() );
		if( i != tstring::npos)
		{
			icon.erase(0, i + 1);
		
		}

		icon = _T("report_icon\\") + icon;
		cv::imwrite(convert<char>(icon), image );
	}

	matchSize = matchsize;
}
cv::Mat CTemplateImage::Resize(const double &scale) const
{
	cv::Mat resizeImage;

	cv::resize(image, resizeImage, cv::Size(), scale, scale);

	return resizeImage.clone();
}

cv::Mat CTemplateImage::Resize(const int &matchsize) const
{
	if (matchSize == matchsize)
	{
		return GetImage();
	}
	else
	{
		return Resize((double)matchsize / (double)matchSize);
	}

}