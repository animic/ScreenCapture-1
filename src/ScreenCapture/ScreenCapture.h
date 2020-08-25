/********************************************************
�ļ�˵������Ļץͼ�Ľӿ��ļ�
���ߣ�����
���ڣ�2015-01-27

********************************************************/

#ifndef SCREEN_CAPTURE_H
#define SCREEN_CAPTURE_H

#include "windows.h"

#define IS_EXPORT

#ifdef IS_EXPORT
	#define PORT_DIR __declspec(dllexport)
#else
	#define PORT_DIR __declspec(dllimport)
#endif

//ץͼ���û��Ĳ���
typedef enum _capture_oper
{
	CO_CANCEL = 0, //ȡ��ץͼ
	CO_SURE,       //ȷ��ץͼ
	CO_SAVEAS,	   //���Ϊץͼ
	CO_EDIT		   //��ץͼ���б༭

}CAPTURE_OPER;

//��ͼ�����ݽṹ
typedef struct _capture_data
{
	char save_dir[MAX_PATH]; //��ͼ�ļ��ı���Ŀ¼
	char filename[MAX_PATH]; //��ͼ�ļ����ļ����ƣ�����·����	
	CAPTURE_OPER capture_oper; //ץͼ���û��Ĳ�����Ϊ

}CAPTURE_DATA, *PCAPTURE_DATA;

//ִ����Ļ��ͼ�ĺ���
PORT_DIR void ExecuteScreenCapture(CAPTURE_DATA* pCaptureData);

#endif
