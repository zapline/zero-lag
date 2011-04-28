#pragma once 
#include "stdafx.h"

class CMainWnd;

class CSystemInfoUIHandler
{				   
public:
	void init(CMainWnd *p);
	CMainWnd *pMain;

	KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		KUI_NOTIFY_MAP_END()

		BEGIN_MSG_MAP_EX(CSystemInfoUIHandler)
		MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
		END_MSG_MAP()
public:
	CSystemInfoUIHandler(void);
	~CSystemInfoUIHandler(void);
};

