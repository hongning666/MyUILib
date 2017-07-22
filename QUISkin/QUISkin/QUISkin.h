#ifndef _QUISKIN_H_
#define _QUISKIN_H_
#include<string>

#ifdef QUISKIN_EXPORTS
#define QUISKIN_API _declspec(dllexport)
#else
#define QUISKIN_API _declspec(dllimport)
#endif


#define StdString std::basic_string<TCHAR>

#endif