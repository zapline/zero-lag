#pragma once	
#include "stdafx.h"
#include "ProcessManage.h"

class CMainWnd;

class CProcessManageUIHandler
{		   		   
public:
	void init(CMainWnd *p);
	CMainWnd *pMain;
	void Scan();

	CProcessManage *ProcessManage;
	HANDLE hThread;

	friend void EnumProcesseThread(LPVOID param);
	CString GetFilenameInPathname(CStringA pathname);

	void OnProcessScan(); 

	CKuiRealListCtrl ProcessList;

	KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		KUI_NOTIFY_ID_COMMAND(4101, OnProcessScan)
	KUI_NOTIFY_MAP_END()

		BEGIN_MSG_MAP_EX(CProcessManageUIHandler)
		MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
		END_MSG_MAP()
public:
	CProcessManageUIHandler(void);
	~CProcessManageUIHandler(void);
};

