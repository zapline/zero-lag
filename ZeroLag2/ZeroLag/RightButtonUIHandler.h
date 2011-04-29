#pragma once	 
#include "stdafx.h"
#include "RightButton.h"

class CMainWnd;

class CRightButtonUIHandler
{			 		   
public:
	void init(CMainWnd *p);
	CMainWnd *pMain;

	void OnAddSysRecycle();
	void OnDelSysRecycle();
	void OnAddCutTo();
	void OnDelCutTo();

	KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		KUI_NOTIFY_ID_COMMAND(6101, OnAddSysRecycle)
		KUI_NOTIFY_ID_COMMAND(6102, OnDelSysRecycle)
		KUI_NOTIFY_ID_COMMAND(6103, OnAddCutTo)
		KUI_NOTIFY_ID_COMMAND(6104, OnDelCutTo)
		KUI_NOTIFY_MAP_END()

		BEGIN_MSG_MAP_EX(CRightButtonUIHandler)
		MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
		END_MSG_MAP()
public:
	CRightButtonUIHandler(void);
	~CRightButtonUIHandler(void);
};

