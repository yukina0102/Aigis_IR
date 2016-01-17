#ifndef __BYTEMAT_H__
#define __BYTEMAT_H__

#include <windows.h>
#include <fstream>
#include <memory>

#include "opencv_common.h"
#include "tString.h"

namespace Aigis_DB
{

//バイナリMat情報構造体
struct ByteMatInfo
{
	int cols;	//横サイズ
	int rows;	//縦サイズ
	int type;	//タイプ
	size_t size;	//データサイズ
};

class ByteMat
{

public:
	ByteMat( void )
		: data(NULL)
	{}
	ByteMat(const cv::Mat& Mat)
		: info({ Mat.cols, Mat.rows, Mat.type(), Mat.total() * Mat.elemSize() }), data(NULL)
	{
		SetData( Mat.data, info.size );
	}
	ByteMat(const int& Cols, const int& Rows, const int& Type, const size_t& Size, const BYTE *Data)
		: info({ Cols, Rows, Type, Size }), data(NULL)
	{
		SetData( Data, info.size);
	}
	ByteMat( const ByteMat& BMat )
		: info( BMat.GetInfo() ), data(NULL)
	{
		SetData(BMat.GetData(), info.size);
	}
	virtual ~ByteMat()
	{
		if( data != NULL )
			delete data;
	}

	//ゲッター
public:
	inline cv::Mat GetCvMat(void) const
	{
		return cv::Mat(info.rows, info.cols, info.type, data);
	}

	inline int GetCols(void) const
	{
		return info.cols;
	}
	inline int GetRows(void) const
	{
		return info.rows;
	}
	inline int GetType(void) const
	{
		return info.type;
	}

	inline ByteMatInfo GetInfo(void) const
	{
		return info;
	}
	inline void SetInfo( const ByteMatInfo& Info )
	{
		info = Info;
	}

	inline const BYTE* GetData(void) const
	{
		return data;
	}
	//SetData
	//　実体データを代入
	//
	//	引数
	//	　const Byte*   Data	実体データ先頭ポインタ
	//　　const size_t& Size	データ数(ByteMatInfoのsize)
	//　戻り値
	//　　なし
	inline void SetData(const BYTE* Data, const size_t& Size)
	{
		if ( data != NULL )
			delete data;

		data = new BYTE[Size];
		memcpy_s(
			data,
			static_cast<size_t>(Size),
			Data,
			static_cast<size_t>(Size)
			);
	}

private:
	ByteMatInfo info;
	BYTE *data;	//画素データ

public:
	static const int32_t fileHeader = 0x424d6174;

};

struct OutputMat
{
	static bool Out( const tstring& FileName, const cv::InputArray& Img )
	{
		return cv::imwrite( convert<char>(FileName), Img );
	}
	static bool Out( const tstring& FileName, const ByteMat& BMat )
	{
		std::ofstream fout;
		fout.open(FileName, std::ios::out | std::ios::binary | std::ios::trunc);
		if (!fout) {
			//SetError(ERROR_OUTPUT, _T("ファイルオープン失敗"));
			return false;
		}
		//ファイルヘッダー
		fout.write((char *)(&ByteMat::fileHeader), sizeof(int32_t));
		//構造体
		fout.write( (char *)(&BMat.GetInfo()), sizeof(ByteMatInfo) );
		//データ実体
		fout.write((char *)(BMat.GetData()), sizeof(BYTE) * BMat.GetInfo().size);

		fout.close();

		return true;
	}
};

struct LoadBMat
{

	static ByteMat Load( const tstring& FileName )
	{
		ByteMat bmat = ByteMat();

		std::ifstream fin;
		fin.open(FileName, std::ios::in | std::ios::binary);
		if (!fin) {
			//ファイルオープン失敗
			return bmat;
		}

		//ファイルヘッダーチェック
		int32_t header;
		fin.read((char *)&header, sizeof(int32_t));
		if (header != ByteMat::fileHeader)
		{
			//ヘッダーが違います

			return bmat;
		}
		//構造体
		ByteMatInfo info;
		fin.read((char *)&info, sizeof(ByteMatInfo));
		bmat.SetInfo( info );

		//実体データ
		//std::unique_ptr<BYTE> data(new BYTE[info.size] );
		BYTE* data = new BYTE[info.size];
		fin.read((char *)data, sizeof(BYTE) * info.size );
		bmat.SetData(data, info.size);
		delete data;

		bool res = fin.bad();

		fin.close();

		return bmat;
	}
};


}

#endif/*__BYTEMAT_H__*/