#include "ProcessManageUIHandler.h"		   
#include "stdafx.h"
#include "MainWnd.h"

void CProcessManageUIHandler::init(CMainWnd *p)
{
	pMain = p;

	DWORD dwStyle = WS_CHILD|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL|LVS_OWNERDRAWFIXED;
	if (ProcessList.Create( pMain->GetRichWnd(),  NULL, NULL, dwStyle, 0, 4001 ))
	{
		DWORD dwExStyle = LVS_EX_FULLROWSELECT;
		dwExStyle |= ProcessList.GetExtendedListViewStyle();

		ProcessList.SetExtendedListViewStyle(dwExStyle);

		ProcessList.InsertColumn( 0, _T("pid"), LVCFMT_LEFT, 100);
		ProcessList.InsertColumn( 1, _T("½ø³ÌÃû"), LVCFMT_LEFT, 500);

		ProcessList.Init();
	}
}



CProcessManageUIHandler::CProcessManageUIHandler(void)
{
}


CProcessManageUIHandler::~CProcessManageUIHandler(void)
{
}
