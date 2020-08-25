// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <atlbase.h>
#include <atltrace.h>

#include "../ScreenCapture/ScreenCapture.h"

#ifdef _WIN64

#ifdef DEBUG
#pragma comment(lib, "../../x64/Debug/ScreenCapture.lib")
#else
#pragma comment(lib, "../../x64/Release/ScreenCapture.lib")
#endif

#else

#ifdef DEBUG
#pragma comment(lib, "../../Debug/ScreenCapture.lib")
#else
#pragma comment(lib, "../../Release/ScreenCapture.lib")
#endif

#endif


int _tmain(int argc, _TCHAR* argv[])
{
	int ret = ExecuteScreenCapture1();
	ATLTRACE("%d\n", ret);
	return 0;
}

