#include "common.h"
#include "Activity.h"
//#include "Common\BitMat.h" 

int _tmain(int argc, _TCHAR  *argv[])
{
	/*using namespace Aigis_DB;
	cv::Mat mat0 = cv::imread("./image/icon301.png");
	ByteMat bmat0 = ByteMat(mat0);
	OutputMat::Out( 
		_T("test.dat"), 
		bmat0
		);


	ByteMat bmat = LoadBMat::Load(_T("test.dat"));
	cv::Mat mat = bmat.GetCvMat();

	while(1)
	{
		cv::imshow("main", mat );
		cv::waitKey(10);
	}*/

	
	return CActivity::GetInstance()->main( argc, argv );
}