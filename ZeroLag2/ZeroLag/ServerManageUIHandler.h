#pragma once
#include "stdafx.h"
#include "ServerManage.h"

class CMainWnd;

class CServerManageUIHandler
{
public:
	void init(CMainWnd *p);
	CMainWnd *pMain;

	CKuiRealListCtrl ServerManageListCtrl;
	BOOL ServerManageHide;
	CServerManage ServerManage;

	void ServerManageFlush();
	void OnServerManageFlush();

	KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		KUI_NOTIFY_ID_COMMAND(2102, OnServerManageFlush)
	KUI_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CServerManageUIHandler)
		MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
	END_MSG_MAP()

public:
	CServerManageUIHandler(void);
	~CServerManageUIHandler(void);
};

