// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <atlbase.h>
#include <atltrace.h>

#include "../ScreenCapture/ScreenCapture.h"

#ifdef DEBUG
#pragma comment(lib, "../../Debug/ScreenCapture.lib")
#else
#pragma comment(lib, "../../Release/ScreenCapture.lib")
#endif


int _tmain(int argc, _TCHAR* argv[])
{
	int ret = ExecuteScreenCapture1();
	ATLTRACE("%d\n", ret);
	return 0;
}

