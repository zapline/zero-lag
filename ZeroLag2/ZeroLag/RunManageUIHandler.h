#pragma once
#include "stdafx.h"
#include "RunManage.h"

class CMainWnd;

class CRunManageUIHandler
{		   
public:
	void init(CMainWnd *p);
	void OnRunScan();
	CMainWnd *pMain;

	KUIMulStatusTree RunTree;
	friend void ScanRegRunThread(LPVOID param);
	friend void ScanDirRunThread(LPVOID param);

	void scan();

	CString GetFilenameInPathname(CString pathname);

	HANDLE hThread1,hThread2;
	HTREEITEM ht0,ht1;
	int ThreadStatus;

	CRunManage *RunManage;

	KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		KUI_NOTIFY_ID_COMMAND(3101, OnRunScan)
		KUI_NOTIFY_MAP_END()

		BEGIN_MSG_MAP_EX(CRunManageUIHandler)
		MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
		END_MSG_MAP()
public:
	CRunManageUIHandler(void);
	~CRunManageUIHandler(void);
};

