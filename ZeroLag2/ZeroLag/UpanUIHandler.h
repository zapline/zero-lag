#pragma once	  
#include "stdafx.h"
#include "Upan.h"

class CMainWnd;

class CUpanUIHandler
{				   
public:
	void init(CMainWnd *p);
	CMainWnd *pMain;
	CUpan Upan;

	void OnCreateAutorun();
	void OnKillHide();
	LRESULT OnList1(DWORD whParam, DWORD wlParam, HWND lParam,BOOL bHandled);
	LRESULT OnList2(DWORD whParam, DWORD wlParam, HWND lParam,BOOL bHandled);

	CComboBox m_DriveList,m_UpanList;

	KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		KUI_NOTIFY_ID_COMMAND(7105 ,OnCreateAutorun)
		KUI_NOTIFY_ID_COMMAND(7106 ,OnKillHide)
	KUI_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CUpanUIHandler)
		MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
		COMMAND_HANDLER(7001, CBN_DROPDOWN, OnList1)
		COMMAND_HANDLER(7002, CBN_DROPDOWN, OnList2)
	END_MSG_MAP()
public:
	CUpanUIHandler(void);
	~CUpanUIHandler(void);
};

