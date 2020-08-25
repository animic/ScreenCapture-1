/********************************************************
�ļ�˵������Ļץͼ�Ľ���ʵ���ļ�
���ߣ�����
���ڣ�2015-01-27

********************************************************/

#ifndef SCREEN_CAPTURE_DLG_H
#define SCREEN_CAPTURE_DLG_H

#pragma warning (disable: 4786)

#include <GdiPlus.h>
#pragma comment(lib, "Gdiplus.lib")
using namespace Gdiplus;

#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <map>
using namespace std;

#define IDC_BUTTON_RECT                 1000
#define IDC_BUTTON_ELLIPSE              1001
#define IDC_BUTTON_ARROW                1002
#define IDC_BUTTON_BRUSH                1003
#define IDC_BUTTON_WORD                 1004
#define IDC_BUTTON_BACK                 1005
#define IDC_BUTTON_SAVE                 1006
#define IDC_BUTTON_CANCEL               1007
#define IDC_BUTTON_OK                   1008

#define IDC_BUTTON_SIZE_SMA				1020
#define IDC_BUTTON_SIZE_MID				1021
#define IDC_BUTTON_SIZE_BIG				1022

#define IDC_BUTTON_COLOR_BASE			1030

#define IDC_EDIT_WORD					1100

class CWnd
{
public:		
	HWND m_hWnd;		
	
	static map<HWND, CWnd*> m_mapWndList;
	
	WNDPROC m_oldWndProc;
	
	CWnd();
	~CWnd();
	
	static void ToWndList(CWnd* pWnd);
	static CWnd* FromWndList(HWND hWnd);
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam); //message route
	
	virtual LRESULT CALLBACK WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam) = 0; //callback function	
};

class CMyButton;

//�Զ��尴ť���ƻص�����
typedef BOOL (__stdcall *pFunCustomDrawButtonCallback)(CMyButton*, HDC, RECT*);

//��ť״̬
typedef enum _button_state
{
	BS_NORMAL = 0,
	BS_HOVER,
	BS_DOWN,
	BS_DISABLE
		
}BUTTON_STATE;

//��ť��ʽ
typedef enum _button_style
{
	BS_BUTTON = 0,
	BS_RADIO
		
}BUTTON_STYLE;

class CMyButton : public CWnd
{
private:
	//��ťID
	UINT m_nButtonID;

	//��ť״̬
	BUTTON_STATE m_buttonState;

	//��ť״̬��Ӧ�ı���ͼƬ
	Image* m_pBkImage[4];
	
	//����ڰ�ť�ϵ����һ��λ��
	int m_lastCursorPos;

	//���ð�ť�Ի�ص�����
	pFunCustomDrawButtonCallback m_pFunCustomDrawButton;

	//���ð�ť��ʽ
	BUTTON_STYLE m_buttonStyle;
public:
	CMyButton();
	virtual ~CMyButton();

	//����button
	HWND CreateButton(UINT idCtl, HWND hParent = NULL, DWORD dwStyle = 0);

	//����ť����PNG����ͼƬ
	void SetPNGBitmaps(Image* pPngImageNormal, Image* pPngImageFocus = NULL, Image* pPngImageDown = NULL, 
		Image* pPngImageDisable = NULL);

	//�����Զ��尴ť���ƻص�����
	void SetCustomDrawButtonCallback(pFunCustomDrawButtonCallback pFun) {m_pFunCustomDrawButton = pFun;}

	//��ȡ��ťID
	UINT GetButtonID() {return m_nButtonID;}

	//��ȡ��ť״̬
	BUTTON_STATE GetButtonState() {return m_buttonState;}

	//��ȡ��ť��ʽ
	BUTTON_STYLE GetButtonStyle() {return m_buttonStyle;}
	
	//���ð�ť״̬
	void SetButtonState(BUTTON_STATE button_state) {m_buttonState = button_state; ::InvalidateRect(m_hWnd, NULL, FALSE);}

	//���ð�ť��ʽ
	void SetButtonStyle(BUTTON_STYLE button_style) {m_buttonStyle = button_style;}	

	//��Ϣ����ص�����
	virtual LRESULT CALLBACK WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);

	//������ƴ���
	BOOL OnPaint(WPARAM wParam, LPARAM lParam);

	//������������
	BOOL OnEraseBkgnd(WPARAM wParam, LPARAM lParam);
		
	//���������µĴ���
	BOOL OnLButtonDown(WPARAM wParam, LPARAM lParam);
	
	//����������Ĵ���
	BOOL OnLButtonUp(WPARAM wParam, LPARAM lParam);	
	
	//���Hover�Ĵ���
	BOOL OnMouseHover(WPARAM wParam, LPARAM lParam);

	//����뿪�Ĵ���
	BOOL OnMouseLeave(WPARAM wParam, LPARAM lParam);

	//Timer�¼��Ĵ���
	BOOL OnTimer(WPARAM wParam, LPARAM lParam);
	
	//�����ƻ��Ĵ���
	BOOL OnDestroy(WPARAM wParam, LPARAM lParam);
};

class CMyEdit : public CWnd
{
public:
	//���һ�ΰ��µ��ַ�
	TCHAR m_chLastCode;

	//�Ƿ��ڱ༭״̬
	BOOL m_bEdit;

private:
	//����
	HFONT m_hFont;
public:
	CMyEdit();
	virtual ~CMyEdit();
	
	//��������
	void SetFont(HFONT hFont);
	
	//����Edit
	HWND CreateEdit(UINT idCtl, HWND hParent = NULL, DWORD dwStyle = 0);
	
	//��Ϣ����ص�����
	virtual LRESULT CALLBACK WindowProc(UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	//������ƴ���
	BOOL OnPaint(WPARAM wParam, LPARAM lParam);

	//�����ƻ�����
	BOOL OnDestroy(WPARAM wParam, LPARAM lParam);
};

class CCustomDialog
{
	typedef struct _custom_info
	{
		union
		{
			int line_width; //�߿�
			int font_size; //�����С

		} size;
		COLORREF color; //������ߵ���ɫ

	}CUSTOM_INFO, *PCUSTOM_INFO;

public:
	HWND m_hDlg;
	BOOL m_bShow;
	UINT m_nSelButtonID; //��ǰѡ��ťID
	UINT m_nSelSizeButtonID; //��ǰѡ��ĳߴ簴ťID
	CUSTOM_INFO m_customInfo[5];
	CMyButton m_buttonWidth[3]; //���ֿ�ѡ���߿�ť
	CMyButton m_buttonColor[16]; //16�ֿ�ѡ����ɫ��ť
	POINT m_ptSepLine[2]; //�ָ��ߵ���������
public:
	CCustomDialog();
	virtual ~CCustomDialog();	

	//��ɫ��ť���ƻص�����
	static BOOL __stdcall DrawColorButton(CMyButton *pButton, HDC hDC, RECT *pRect);

	//���¿ؼ�
	void UpdateControls();

	//���°�ť״̬
	void UpdateButtonState();

	//չʾ���ƿ�
	void ShowCustomDlg(bool bShow = true, UINT nButtonID = 0);	

	//���߿�Ĵ������
	static BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	//�Ի����ʼ������
	BOOL DialogOnInit(HWND hWnd, WPARAM wParam, LPARAM lParam);

	//�Ի��������
	BOOL DialogOnCommand(WPARAM wParam, LPARAM lParam);		
	
	//�Ի�����ƴ���
	BOOL DialogOnPaint(WPARAM wParam, LPARAM lParam);
	
	//���������Ĵ���
	BOOL DialogOnEraseBkgnd(WPARAM wParam, LPARAM lParam);	
	
	//�����ƻ��Ĵ���
	BOOL DialogOnDestroy(WPARAM wParam, LPARAM lParam);
};

class CToolDialog
{
public:
	HWND m_hDlg;
	BOOL m_bShow;
	CCustomDialog m_CustomDlg;
	CMyButton m_btRect;
	CMyButton m_btEllipse;
	CMyButton m_btArrow;
	CMyButton m_btBrush;
	CMyButton m_btWord;
	CMyButton m_btBack;
	CMyButton m_btSave;
	CMyButton m_btCancel;	
	CMyButton m_btOk;	
public:
	CToolDialog();
	virtual ~CToolDialog();
	
	//չʾ���߿�
	void ShowToolDlg(bool bShow = true);	
	
	//���߿�Ĵ������
	static BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);
	
	//�Ի����ʼ������
	BOOL DialogOnInit(HWND hWnd, WPARAM wParam, LPARAM lParam);
	
	//�Ի��������
	BOOL DialogOnCommand(WPARAM wParam, LPARAM lParam);

	//�Ի���Timer����
	BOOL DialogOnTimer(WPARAM wParam, LPARAM lParam);
	
	//�Ի�����ƴ���
	BOOL DialogOnPaint(WPARAM wParam, LPARAM lParam);
	
	//���������Ĵ���
	BOOL DialogOnEraseBkgnd(WPARAM wParam, LPARAM lParam);	

	//�����ƻ��Ĵ���
	BOOL DialogOnDestroy(WPARAM wParam, LPARAM lParam);

public:
	//�Ƿ����༭ģʽ
	bool m_bEdit;

	//��ǰѡ��Ļ��ư�ťID(���Ρ���Բ����ͷ����ˢ���ı�)
	UINT m_nSelDrawButtonID;

	//��ǰѡ��Ŀ��ư�ťID(���������桢ȡ����ȷ��)
	UINT m_nSelCtrlButtonID;

	//�Ƿ�����ı���ť�л�
	bool m_bSwitchTextButton;

public:
	//��ʼ������������
	void InitToolData();

	//���°�ť״̬
	void UpdateButtonState();
};

class CSCDialog
{
	//��걻�������״̬
	typedef enum _capture_state
	{
		CS_NORMAL,
		CS_MOVE,
		CS_SIZE_UP,
		CS_SIZE_DOWN,
		CS_SIZE_LEFT,
		CS_SIZE_RIGHT,
		CS_SIZE_UPLEFT,
		CS_SIZE_UPRIGHT,
		CS_SIZE_DOWNLEFT,
		CS_SIZE_DOWNRIGHT,	
			
	}CAPTURE_STATE;
	
	//�������λ��
	typedef enum _cursor_position
	{
		CP_OUTSIDE,
		CP_INSIDE,
		CP_SIDE_UP,
		CP_SIDE_DOWN,
		CP_SIDE_LEFT,
		CP_SIDE_RIGHT,
		CP_CORNER_UPLEFT,
		CP_CORNER_UPRIGHT,
		CP_CORNER_DOWNLEFT,
		CP_CORNER_DOWNRIGHT,	
			
	}CURSOR_POSITION;

public:
	HWND m_hDlg;
	
	//��ͼ�Ƿ�ʼ
	bool m_bStartPrintScr; 

	//�Ƿ��ڴ��ڲ���ģʽ
	bool m_bCapWnd;	

	//�Ƿ���ʾ��ʾ
	bool m_bShowTip;

	//�Ƿ�ʼ�༭��ͼ
	bool m_bStartEdit;

	//�Ƿ���
	bool m_bSelBack;

	//��Ļ�ֱ���
	int m_nXScreen;
	int m_nYScreen;

	//������ʱ������Ĵ���
	int m_nWordCount;

	POINT m_ptCapStart; //��ʼ��ȡʱ����ʼ������
	POINT m_ptScrawStart; //��ʼͿѻʱ����ʼ������
	POINT m_ptScrawEnd; //����Ϳѻʱ������

	RECT m_rtSel; //ѡ���������
	RECT m_rtTip; //��ʾ�����
	vector<RECT> m_rtWnds; //��ǰ��Ļ�к��еĴ������

	RECT m_rtScrawl; //Ϳѻ����
	RECT m_rtWord; //�����������
	vector<POINT> m_ptScrawls; //Ϳѻ��
	vector<HBITMAP> m_vecBitmaps; //�洢�û����Ƶ�λͼ�����ڳ���

	HBITMAP m_hBitmap; //��ǰ��Ļλͼ
	HBITMAP m_hGrayBitmap; //��ǰ��Ļ�Ҷ�λͼ
	HBITMAP m_hCurScrawlBimtap; //��ǰͿѻλͼ

	CMyEdit m_edWord; //���ڻ������ֵı༭��
	CToolDialog m_ToolDlg; //�������Ի���

	//�ڵ���GdiplusStartup֮ǰ����ȷ��GdiplusStartupInput��ɳ�ʼ���������Ϊ��Ա������ʹ��
	GdiplusStartupInput   m_gdiplusStartupInput; 
	ULONG_PTR   m_gdiplusToken;

	RECT m_rtScreenShow; //��Ļչʾ����	
	RECT m_rtCutStart; //��갴��ʱ�Ĳü�����ľ���
	
	HCURSOR m_hCursor; //��ǰ���
	CAPTURE_STATE m_CaptureState; //��ǰ�������״̬
	CURSOR_POSITION m_CursorPos; //��ǰ�������λ��
	
	POINT m_ptStart; //��꿪ʼ�ƶ���λ��
	POINT m_ptEnd; //�������ƶ���λ��

private:
	//��ʼ��ץͼ����
	void InitCaptureData();

	//��ȡָ�����ε���Ļ��λͼ
	HBITMAP PrintScreenToBitmap(int x, int y, int width, int height);	

	//�жϵ�ǰѡ��������Ƿ����Ҫ��
	bool IsLegalForSelRgn();
	
	//��ٵ�ǰ���涥�㴰�ڵĻص�����
	static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

	//������ʾ�����
	void UpdateTipRect();

	//���¹���������
	void UpdateToolWndPos();

	//����Ϳѻ
	void DrawScrawl(HDC hDC, HBITMAP hBitmap);

	//����ѡ������ı߽�
	void DrawSelRgnEdge(HDC hDC);

	//������ʾ
	void DrawTip(HDC hDC);	

	//���µ�ǰ�������״̬
	void UpdateCaptureState();
	
	//���µ�ǰ�����
	void UpdateCursor();
	
	//���µ�ǰ���λ��
	void UpdateCursorPos(POINT point);		

	//ˢ����ʾ����
	void UpdateShowRgn();
public:
	//��ȡ�һ����λͼ
	HBITMAP GetGrayBitmap(HBITMAP hBitmap, COLORREF colorGray, double alpha);	

	//λͼ�ĸ���(�������Ŀ��λͼ������ԭλͼ��Ŀ��λͼ������������򴴽���λͼ������ԭλͼ��Ϊ����ֵ�����ҿ���ָ�����ƾ���)
	HBITMAP CopyBitmap(HBITMAP hSrcBitmap, HBITMAP hDstBitmap = NULL, const RECT *pRTSrc = NULL, const RECT *pRTDst = NULL);

	//�����Խ�ͼ�ı༭
	void BackEditBmp();

	//���Ϊ��ͼ
	void SaveAsCaptureBmp();

	//ȡ����ͼ
	void CancelScreenCapture();

	//ȷ����ͼ
	void EnsureScreenCapture();
public:
	CSCDialog();
	virtual ~CSCDialog();

	//չʾ������
	INT_PTR  ShowScreenCaptureDlg();	

	//�Ի���Ĵ������
	static BOOL CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam);

	//�Ի����ʼ������
	BOOL DialogOnInit(HWND hWnd, WPARAM wParam, LPARAM lParam);

	//�Ի��������
	BOOL DialogOnCommand(WPARAM wParam, LPARAM lParam);

	//�Ի�����ƴ���
	BOOL DialogOnPaint(WPARAM wParam, LPARAM lParam);

	//���������Ĵ���
	BOOL DialogOnEraseBkgnd(WPARAM wParam, LPARAM lParam);

	//���������µĴ���
	BOOL DialogOnLButtonDown(WPARAM wParam, LPARAM lParam);

	//������˫���¼�
	BOOL DialogOnLButtonDbClick(WPARAM wParam, LPARAM lParam);

	//����������Ĵ���
	BOOL DialogOnLButtonUp(WPARAM wParam, LPARAM lParam);

	//����Ҽ�����Ĵ���
	BOOL DialogOnRButtonUp(WPARAM wParam, LPARAM lParam);

	//����ƶ��Ĵ���
	BOOL DialogOnMouseMove(WPARAM wParam, LPARAM lParam);

	//�����ƻ��Ĵ���
	BOOL DialogOnDestroy(WPARAM wParam, LPARAM lParam);

	//���Թ��ߴ�����Ϣ�Ĵ���
	BOOL OnMsgFromTool(WPARAM wParam, LPARAM lParam);

	//���Ա༭�򴰿���Ϣ�Ĵ���
	BOOL OnMsgFromEdit(WPARAM wParam, LPARAM lParam);

	//���Զ��ƴ�����Ϣ�Ĵ���
	BOOL OnMsgFromCustom(WPARAM wParam, LPARAM lParam);
};


#endif
