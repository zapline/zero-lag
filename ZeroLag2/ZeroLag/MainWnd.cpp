#include "stdafx.h"
#include "Mainwnd.h"
#include "resource.h"
CMainWnd *g_pMainWnd = NULL;

CMainWnd::CMainWnd(void) : CKuiDialogImpl<CMainWnd>( "IDR_DLG_MAIN" )
{
	g_pMainWnd = this;

	SignScanUIHandler = new CSignScanUIHandler();
	ServerManageHandler = new CServerManageUIHandler();
}

CMainWnd::~CMainWnd(void)
{
	delete SignScanUIHandler;
	delete ServerManageHandler;
}

LRESULT CMainWnd::OnInitDialog( HWND hDlg, LPARAM lParam )
{
	SetIcon(::LoadIcon((HMODULE)&__ImageBase, MAKEINTRESOURCE(IDI_ICON_MAIN)));
	SetIcon(::LoadIcon((HMODULE)&__ImageBase, MAKEINTRESOURCE(IDI_ICON_MAIN)), FALSE);

	SignScanUIHandler->init(g_pMainWnd);
	ServerManageHandler->init(g_pMainWnd);

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
