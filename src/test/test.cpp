// test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "../ScreenCapture/ScreenCapture.h"

#ifdef DEBUG
#pragma comment(lib, "../../Debug/ScreenCapture.lib")
#else
#pragma comment(lib, "../../Release/ScreenCapture.lib")
#endif


int _tmain(int argc, _TCHAR* argv[])
{
	CAPTURE_DATA d = {0};
	ExecuteScreenCapture(&d);
	return 0;
}

