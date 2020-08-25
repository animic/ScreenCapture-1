#include "ScreenCapture.h"
#include "ScreenCaptureDlg.h"

CAPTURE_DATA* g_pCaptureData = NULL;
CSCDialog g_scDialog;
HANDLE g_hModule = NULL;

BOOL APIENTRY DllMain( HANDLE hModule, 
					  DWORD  ul_reason_for_call, 
					  LPVOID lpReserved
					  )
{
	g_hModule = hModule;
    switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
    }
    return TRUE;
}

INT_PTR ExecuteScreenCapture(CAPTURE_DATA* pCaptureData)
{
	if(!pCaptureData)
		return -1;

	g_pCaptureData = pCaptureData;

	return g_scDialog.ShowScreenCaptureDlg();
}

INT_PTR ExecuteScreenCapture1()
{
	return g_scDialog.ShowScreenCaptureDlg();
}
