// test.cpp : �������̨Ӧ�ó������ڵ㡣
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

