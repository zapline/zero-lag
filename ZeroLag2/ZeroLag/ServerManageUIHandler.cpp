#include "ServerManageUIHandler.h"
#include "stdafx.h"
#include "MainWnd.h"


CServerManageUIHandler::CServerManageUIHandler(void)
{
}


CServerManageUIHandler::~CServerManageUIHandler(void)
{
}

void CServerManageUIHandler::init( CMainWnd *p )
{
	pMain = p;

	DWORD dwStyle = WS_CHILD|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL|LVS_OWNERDRAWFIXED;

	if( ServerManageListCtrl.Create( pMain->GetRichWnd(),  NULL, NULL, dwStyle, 0, 2001 ) )
	{
		DWORD dwExStyle = LVS_EX_FULLROWSELECT;
		dwExStyle |= ServerManageListCtrl.GetExtendedListViewStyle();
		ServerManageListCtrl.SetExtendedListViewStyle(dwExStyle);

		ServerManageListCtrl.InsertColumn( 0, _T("服务名称"), LVCFMT_LEFT, 250);
		ServerManageListCtrl.InsertColumn( 1, _T("服务描述"), LVCFMT_LEFT, 400);
		ServerManageListCtrl.InsertColumn( 2, _T("服务状态"), LVCFMT_LEFT, 100);

		ServerManageListCtrl.Init();

		ServerManageHide = FALSE;
		ServerManageFlush();
	}

}

void CServerManageUIHandler::ServerManageFlush()
{
	//獲得隱藏未運行複選框的狀態

	ServerManageListCtrl.DeleteAllItems();

	ENUM_SERVICE_STATUS* lpservice = NULL;
	DWORD servicesReturned = 0;
	ServerManage.EnumServername(&lpservice,SERVICE_WIN32|SERVICE_DRIVER,SERVICE_STATE_ALL,&servicesReturned);

	unsigned j=0;
	for(unsigned i=0;i < servicesReturned;i++)
	{
		if (lpservice[i].ServiceStatus.dwCurrentState == SERVICE_RUNNING)
		{
			ServerManageListCtrl.InsertItem(j, "");
			ServerManageListCtrl.SetItemText(j,0,lpservice[i].lpServiceName);
			ServerManageListCtrl.SetItemText(j,1,lpservice[i].lpDisplayName);
			ServerManageListCtrl.SetItemText(j,2, "正运行");
			j++;
		}
		else if (ServerManageHide == FALSE)
		{
			ServerManageListCtrl.InsertItem(j, "");
			ServerManageListCtrl.SetItemText(j,0,lpservice[i].lpServiceName);
			ServerManageListCtrl.SetItemText(j,1,lpservice[i].lpDisplayName);
			ServerManageListCtrl.SetItemText(j,2, "已停止");
			j++;
		}
	}
}

void CServerManageUIHandler::OnServerManageFlush()
{
	ServerManageFlush();

}