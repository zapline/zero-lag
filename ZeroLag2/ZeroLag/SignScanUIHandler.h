#pragma once
#include "stdafx.h"
#include "SignScan.h"

class CMainWnd;

class CSignScanUIHandler
{
public:
	void init(CMainWnd *p);
	CMainWnd *pMain;

	CString GetDirector(CString title);
	void OnSignScanChoicePath();
	void OnSignScanBegin();
	void OnSignScanPause();
	void OnSignScanEnd();
	void OnSignScanOption();
	friend void SignScanThread(LPVOID param);

	CKuiRealListCtrl SignScanListCtrl;
	CEdit SignScanPathEdit;
	CString SignScanPath;
	CSignScan SignScan;
	BOOL SignScanHideHave;
	int SignScanFileType;
	int SignScanThreadStatus;
	HANDLE SignScanhThread;

	KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		KUI_NOTIFY_ID_COMMAND(1105, OnSignScanChoicePath)
		KUI_NOTIFY_ID_COMMAND(1102, OnSignScanBegin)
		KUI_NOTIFY_ID_COMMAND(1103, OnSignScanPause)
		KUI_NOTIFY_ID_COMMAND(1104, OnSignScanEnd)
		KUI_NOTIFY_ID_COMMAND(1101, OnSignScanOption)
    KUI_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CSignScanUIHandler)
		MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
	END_MSG_MAP()

public:
	CSignScanUIHandler(void);
	~CSignScanUIHandler(void);
};

