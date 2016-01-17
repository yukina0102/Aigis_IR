#ifndef TSTRING_H
#define TSTRING_H

#pragma once

#include <tchar.h>
#include <string>

//class tstring : public std::basic_string<_TCHAR>
//{
//
//public:
//	using base = std::basic_string<_TCHAR>;
//
//	using base::operator=;
//	using base::operator+=;
//	using base::operator[];
//	
////コンストラクタ
//public:
//	tstring();
//	tstring(const _TCHAR *str);
//	tstring(const std::basic_string<_TCHAR>& s);
//	tstring(const size_t Count, _TCHAR TCh);
//
////wstring依存コードの可能性があるため
//#ifdef _UNICODE
//public:
//	//負の値のとき左詰め、正の値のとき右詰めになる
//	tstring descript(int Width) const;
//
//	/*inline std::string c_charstr(void)
//	{
//		return convert<char>( *this );
//	}*/
//#else
//
//#endif
//
//};

#include <locale>

template<typename type_t>
struct convert_t {
};

template<>
struct convert_t<char> {
	typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
	inline const std::string operator()(const std::string& narrow) const {
		return narrow;
	}
	inline const std::string operator()(const std::wstring& wide) const {
		return std::wstring_convert< const codecvt_t >{&std::use_facet<codecvt_t>(std::locale{})}.to_bytes(wide);
	}
};

template<>
struct convert_t<wchar_t> {
	typedef std::codecvt<wchar_t, char, std::mbstate_t> codecvt_t;
	inline const std::wstring operator()(const std::string& narrow) const {
		return std::wstring_convert< const codecvt_t >{ &std::use_facet<codecvt_t>(std::locale{})}.from_bytes(narrow);
	}
	inline const std::wstring operator()(const std::wstring& wide) const {
		return wide;
	}
};

// 関数オブジェクトを呼び出すための、関数テンプレート
template<typename result, typename arg_t>
inline auto convert(arg_t arg) -> decltype(convert_t<result>{}(arg)) {
	return convert_t<result>{}(arg);
}



class tstring : public std::basic_string<_TCHAR>
{

public:
	using base = std::basic_string<_TCHAR>;

	using base::operator=;
	using base::operator+=;
	using base::operator[];

	//コンストラクタ
public:
	tstring();
	tstring(const _TCHAR *str);
	tstring(const std::basic_string<_TCHAR>& s);
	tstring(const size_t Count, _TCHAR TCh);

	//wstring依存コードの可能性があるため
#ifdef _UNICODE
public:
	//負の値のとき左詰め、正の値のとき右詰めになる
	tstring descript(int Width) const;
#else

#endif

	inline std::string convStr(void)
	{
		return convert<char>(*this);
	}
	inline std::wstring convWStr(void)
	{
		return convert<wchar_t>(*this);
	}

};

template < typename T >
inline tstring to_tstring(const T& val)
{
#ifdef _UNICODE
	return std::to_wstring(val);
#else
	return std::to_string(val);
#endif

}

#endif/*TSTRING_H*/