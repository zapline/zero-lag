#include "stdafx.h"
#include "Mainwnd.h"
#include "resource.h"
CMainWnd *g_pMainWnd = NULL;

CMainWnd::CMainWnd(void) : CKuiDialogImpl<CMainWnd>( "IDR_DLG_MAIN" )
{
	g_pMainWnd = this;

	SignScanUIHandler = new CSignScanUIHandler();
	ServerManageHandler = new CServerManageUIHandler();
	ProcessManageHandler = new CProcessManageUIHandler();
	RunManageHandler = new CRunManageUIHandler();
	RightButtonHandler = new CRightButtonUIHandler();
	UpanHandler = new CUpanUIHandler();
	SystemInfoHandler = new CSystemInfoUIHandler();
}

CMainWnd::~CMainWnd(void)
{
	delete SignScanUIHandler;
	delete ServerManageHandler;
	delete ProcessManageHandler;
	delete SystemInfoHandler;
	delete RunManageHandler;
	delete RightButtonHandler;
	delete UpanHandler;
}

LRESULT CMainWnd::OnInitDialog( HWND hDlg, LPARAM lParam )
{
	SetIcon(::LoadIcon((HMODULE)&__ImageBase, MAKEINTRESOURCE(IDI_ICON_MAIN)));
	SetIcon(::LoadIcon((HMODULE)&__ImageBase, MAKEINTRESOURCE(IDI_ICON_MAIN)), FALSE);

	SignScanUIHandler->init(g_pMainWnd);
	ServerManageHandler->init(g_pMainWnd);
	ProcessManageHandler->init(g_pMainWnd);
	RunManageHandler->init(g_pMainWnd);
	RightButtonHandler->init(g_pMainWnd);
	UpanHandler->init(g_pMainWnd);
	SystemInfoHandler->init(g_pMainWnd);

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
