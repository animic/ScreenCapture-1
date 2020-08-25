// test.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "../ScreenCapture/ScreenCapture.h"
#pragma comment(lib, "../ScreenCapture/Debug/ScreenCapture.lib")

int _tmain(int argc, _TCHAR* argv[])
{
	CAPTURE_DATA d;
	ExecuteScreenCapture(&d);
	return 0;
}

