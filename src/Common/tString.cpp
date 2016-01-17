#include "tString.h"
#include "../SubModule/wcwidth/wcwidth.h"

tstring::tstring()
	: std::basic_string<_TCHAR>() {}
tstring::tstring(const _TCHAR *str)
	: std::basic_string<_TCHAR>(str) {}
tstring::tstring(const std::basic_string<_TCHAR>& s)
	: std::basic_string<_TCHAR>(s) {}
tstring::tstring(const size_t Count, _TCHAR TCh)
	: std::basic_string<_TCHAR>(Count, TCh) {}

#ifdef _UNICODE

tstring tstring::descript(int Width) const
{
	int size = abs(Width) - wcswidth(c_str(), size_t( _tcslen(c_str())));
	if (size < 0)
		size = 0;

	//-が左詰め、+が右詰め
	return (Width < 0) ?
		*this + tstring(size, _T(' ')) : tstring(size, _T(' ')) + *this;
}
#else

#endif