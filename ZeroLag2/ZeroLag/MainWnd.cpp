#include "stdafx.h"
#include ".\mainwnd.h"
CMainWnd *g_pMainWnd = NULL;

CMainWnd::CMainWnd(void) : CKuiDialogImpl<CMainWnd>( "IDR_DLG_MAIN" )
{
	g_pMainWnd = this;
}

CMainWnd::~CMainWnd(void)
{
}

LRESULT CMainWnd::OnInitDialog( HWND hDlg, LPARAM lParam )
{
	SignScanUIHandler = new CSignScanUIHandler();
	SignScanUIHandler->init(g_pMainWnd);

	DWORD dwStyle = WS_CHILD|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL|LVS_OWNERDRAWFIXED;

	if( ServerManageListCtrl.Create( GetRichWnd(),  NULL, NULL, dwStyle, 0, 2001 ) )
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
	CenterWindow();
	return TRUE;
}

void CMainWnd::OnDestroy()
{
    PostQuitMessage(0);
}

void CMainWnd::OnBkBtnMax()
{
	if (WS_MAXIMIZE == (GetStyle() & WS_MAXIMIZE))
	{
		SendMessage(WM_SYSCOMMAND, SC_RESTORE | HTCAPTION, 0);
	}
	else
	{
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE | HTCAPTION, 0);
	}
}

void CMainWnd::OnBkBtnMin()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE | HTCAPTION, 0);
}

void CMainWnd::OnBkBtnClose()
{
	DestroyWindow();
}

void CMainWnd::OnSysCommand(WPARAM wParam, CPoint pt )
{
	SetMsgHandled(FALSE);

	switch (wParam & 0xFFF0)
	{
	case SC_CLOSE:
		SetMsgHandled(TRUE);
		DestroyWindow();
		break;
	case SC_RESTORE:
		{
			DWORD dwStyle = GetStyle();
			if (WS_MINIMIZE == (dwStyle & WS_MINIMIZE))
				break;

			if (WS_MAXIMIZE == (dwStyle & WS_MAXIMIZE))
			{
				SetItemAttribute(IDC_BTN_SYS_MAX, "skin", "maxbtn");
				break;
			}
		}
	case SC_MAXIMIZE:
		SetItemAttribute(IDC_BTN_SYS_MAX, "skin", "restorebtn");
		break;
	}
}

void CMainWnd::ServerManageFlush()
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
