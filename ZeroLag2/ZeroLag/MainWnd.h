#pragma once
#include "stdafx.h"
#include "SignScan.h"
class CMainWnd : public CKuiDialogImpl<CMainWnd>
	, public CWHRoundRectFrameHelper<CMainWnd>
{
public:
	CMainWnd(void);
	virtual ~CMainWnd(void);
	LRESULT OnInitDialog( HWND hDlg, LPARAM lParam );
	void OnDestroy();
	void OnSysCommand(WPARAM wParam, CPoint pt );

	CString GetDirector(CString title);

	void OnBkBtnClose();
    void OnBkBtnMax();
    void OnBkBtnMin();

	void OnSignScanChoicePath();
	void OnSignScanBegin();
	void OnSignScanPause();
	void OnSignScanEnd();
	void OnSignScanOption();
	friend void SignScanThread(LPVOID param);

	CKuiRealListCtrl SignScanListCtrl;
/*	CButton SignScanbBegin,SignScanbPause,SignScanbEnd;*/
	CEdit SignScanPathEdit;
	CString SignScanPath;
	CSignScan SignScan;
	BOOL SignScanHideHave;
	int SignScanFileType;
	int SignScanThreadStatus;
	HANDLE SignScanhThread;
	

	KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
        KUI_NOTIFY_ID_COMMAND(60001, OnBkBtnClose)
        KUI_NOTIFY_ID_COMMAND(60002, OnBkBtnMax)
        KUI_NOTIFY_ID_COMMAND(60003, OnBkBtnMin)
        //KUI_NOTIFY_TAB_SELCHANGE(IDC_TAB_MAIN, OnBkTabMainSelChange)
		KUI_NOTIFY_ID_COMMAND(1105, OnSignScanChoicePath)
		KUI_NOTIFY_ID_COMMAND(1102, OnSignScanBegin)
		KUI_NOTIFY_ID_COMMAND(1103, OnSignScanPause)
		KUI_NOTIFY_ID_COMMAND(1104, OnSignScanEnd)
		KUI_NOTIFY_ID_COMMAND(1101, OnSignScanOption)
    KUI_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CMainWnd)
		MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP(CKuiDialogImpl<CMainWnd>)
		CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CMainWnd>)

		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_SYSCOMMAND(OnSysCommand)
		MSG_WM_DESTROY(OnDestroy)
		
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
};

extern CMainWnd *g_pMainWnd;
