#pragma once	  
#include "stdafx.h"

class CMainWnd;

class CUpanUIHandler
{				   
public:
	void init(CMainWnd *p);
	CMainWnd *pMain;

	CComboBox m_DriveList,m_UpanList;

	KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		KUI_NOTIFY_MAP_END()

		BEGIN_MSG_MAP_EX(CUpanUIHandler)
		MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
		END_MSG_MAP()
public:
	CUpanUIHandler(void);
	~CUpanUIHandler(void);
};

