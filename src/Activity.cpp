#include "Activity.h"
#include "Common\Debug.h"

Activity CActivity::Instance = NULL;

int CActivity ::
main( int argc, _TCHAR **argv)
{
	
	//アプリケーション初期化
    initialize();

	////動作モードの設定
	//static BOOL pvmode = FALSE;

	//if (_tfopen(_T("MODE_PV"), _T("r")) != NULL)
	//{
	//	DEBUG_LOG(LOG_CONSOLE, "----PVモードで動作します----");
	//	pvmode = TRUE;
	//}

	//if (pvmode)
	//{

	//	//cv::Mat tex = cv::imread("testdata\\aigis150822005152_1.png");
	//	//cv::Mat tex2 = tex(cv::Rect(550, 170, 64, 32));
	//	//cv::imwrite("window.png", tex2);

	//	//cv::imshow("main", tex);

	//	//scene->matching(tex);

	//	//mthread->addQueue(tex);


	//	//動作テスト用システム
	//	//CScene tScene;

	//	WIN32_FIND_DATA fd;
	//	HANDLE h;
	//	tstring dirname = _T(".\\testdata\\");
	//	std::vector<tstring> filelist;


	//	// ハンドルを取得する
	//	h = FindFirstFileEx(
	//		(dirname + _T("*")).c_str(),
	//		FindExInfoStandard, &fd,
	//		FindExSearchNameMatch,
	//		NULL,
	//		0
	//		);

	//	if (INVALID_HANDLE_VALUE == h) {
	//		;// printf("ディレクトリ %s でエラー\n", dirname.c_str());
	//	}
	//	else
	//	{
	//		do {
	//			if (fd.dwFileAttributes & ~FILE_ATTRIBUTE_DIRECTORY) {
	//				DEBUG_LOG(LOG_CONSOLE, "%s", fd.cFileName);
	//				filelist.push_back(dirname + fd.cFileName);
	//				/*cv::Mat image = cv::imread(convert<char>((dirname + fd.cFileName).c_str()));
	//				if (image.data == NULL)
	//				{
	//					DEBUG_LOG(LOG_CONSOLE, "画像が開けません" );
	//				}
	//				else
	//				{
	//					//cv::resize(image, image, cv::Size(), 0.5, 0.5);

	//					cv::imshow("main", image);
	//					cv::waitKey(2);
	//					tScene.matching(image);
	//				}*/

	//			}

	//		} while (FindNextFile(h, &fd));

	//		FindClose(h);

	//	}

	//	//処理の開始
	//	for (auto i = filelist.begin(); i < filelist.end(); ++i)
	//	{

	//		cv::Mat image = cv::imread(convert<char>((*i).c_str()));
	//		if (image.data == NULL)
	//		{
	//			DEBUG_LOG(LOG_CONSOLE, "画像が開けません");
	//		}
	//		else
	//		{
	//			//cv::resize(image, image, cv::Size(), 0.5, 0.5);
	//			//CByteMat bmat( image );
	//			/*cv::Mat alpha = cv::imread("template\\base\\unit_alpha.png");
	//			for (int y = 0; y < alpha.rows; ++y )
	//			{
	//				for (int x = 0; x < alpha.cols; ++x)
	//				{
	//					//if( alpha.data[y * alpha.cols + x * alpha.step + 0] == 0 )
	//					//	_tprintf(_T("( %d, %d )"), x, y);
	//					if( alpha.at<cv::Vec3b>(y, x)[0] == 0 )
	//						_tprintf(_T("{ %d, %d },"), x, y);
	//					
	//				}
	//				_tprintf(_T("\n"));
	//			}*/
	//			/*cv::Mat icon = image(MatchRange::CombineIcon);
	//			for (auto& e : Icon::Mask)
	//			{
	//				icon.at<cv::Vec3b>(e) = { 0, 0, 0 };
	//			}

	//			cv::imwrite( "icon2.png", image( MatchRange::CombineIcon ) );
	//			*/
	//			/*cv::Mat icon;
	//			static int count = 101;
	//			icon = image(cv::Rect( MatchRange::CombineIcon.x, MatchRange::CombineIcon.y, MatchRange::CombineIcon.width, MatchRange::CombineIcon.height));
	//			cv::imwrite((std::string( "icon2\\icon" ) + std::to_string(count) + ".png").c_str(), icon );
	//			count++;
	//			icon = image(cv::Rect(MatchRange::CombineIcon.x + 1, MatchRange::CombineIcon.y, MatchRange::CombineIcon.width, MatchRange::CombineIcon.height));
	//			cv::imwrite((std::string("icon2\\icon") + std::to_string(count) + ".png").c_str(), icon);
	//			count++;
	//			icon = image(cv::Rect(MatchRange::CombineIcon.x, MatchRange::CombineIcon.y + 1, MatchRange::CombineIcon.width, MatchRange::CombineIcon.height));
	//			cv::imwrite((std::string("icon2\\icon") + std::to_string(count) + ".png").c_str(), icon);
	//			count++;
	//			icon = image(cv::Rect(MatchRange::CombineIcon.x + 1, MatchRange::CombineIcon.y + 1, MatchRange::CombineIcon.width, MatchRange::CombineIcon.height));
	//			cv::imwrite((std::string("icon2\\icon") + std::to_string(count) + ".png").c_str(), icon);
	//			count++;

	//			
	//			
	//			count = ((count / 100) + 1 ) * 100 + 1;
	//			*/

	//			cv::imshow("main", image);
	//			//COutputMat(_T("test.txt"), CByteMat(image));
	//			//cv::Mat image2 = bmat.ToMat();
	//			if (cv::waitKey(2) >= 0)
	//				break;
	//			//NewSystem::CSceneAnalysis(image).GetResult();
	//			iAnalysis->AddQueue(image.clone());
	//		}

	//		//はじめに戻る
	//		if (i == filelist.end() - 1)
	//		{
	//			i = filelist.begin();
	//		}

	//		if (cv::waitKey(2) >= 0)
	//			break;


	//		//Sleep(100);
	//	}

	//	//アプリケーション終了処理
	//	finalize();

	//	return 0;
	//}


	//Data data = (Data)new CData( _T("test"), new CTemplateImage(_T("template\\base\\stage.png")) );

	//cv::Mat test = data->getTempImage()->getImage();
	

	while(1)
	{

		//画面キャプチャ
		if (!screen->Capture())
		{
			//エンターを押したとき終了する
			if (cv::waitKey(1) >= 0) break;
			Sleep(5);

			continue;
		}

		cv::imshow("main", screen->getAigisMat() );
		
		////入力状態取得
		//input->checkState();



		//if (input->getState( CInput::InputState::INPUT_PUSH, screen->getRect() ))
		//{
		//	//DEBUG_LOG( LOG_CONSOLE, "クリックを取得" );
		//	//screen->output( "png" );
		//	//scene->matching( screen->getAigisMat() );

		//	iAnalysis->AddQueue(screen->getAigisMat().clone());
		//	

		//}

		//エンターを押したとき終了する
		if (cv::waitKey(1) >= 0) 
			break;
		Sleep(10);
	}
	

    finalize();

    return 0;
}

int CActivity ::
initialize(void)
{

	DEBUG_LOG(LOG_CONSOLE, "----プログラム開始----");

	DEBUG_LOG(LOG_CONSOLE, "----ローディング開始----");
	{
		//using namespace NewData;
	
		//ItemData::GetInstance().Load();
		//UnitData::GetInstance().Load();
		//StageData::GetInstance().Load();
	}
	DEBUG_LOG(LOG_CONSOLE, "----ローディング終了----");

	screen = std::make_unique<CScreen>();

    return 0;
}

int CActivity :: 
finalize(void)
{

	DEBUG_LOG( LOG_CONSOLE, "----プログラム終了----" );
	DEBUG_LOG( LOG_END, "" );

    return 0;
}