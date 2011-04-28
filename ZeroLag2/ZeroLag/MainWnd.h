#pragma once
#include "stdafx.h"
#include "SignScanUIHandler.h"
#include "ServerManageUIHandler.h"
#include "RightButtonUIHandler.h"
#include "RunManageUIHandler.h"
#include "UpanUIHandler.h"
#include "SystemInfoUIHandler.h"
#include "ProcessManageUIHandler.h"
class CMainWnd : public CKuiDialogImpl<CMainWnd>
	, public CWHRoundRectFrameHelper<CMainWnd>
{
public:
	CMainWnd(void);
	virtual ~CMainWnd(void);
	LRESULT OnInitDialog( HWND hDlg, LPARAM lParam );
	void OnDestroy();
	void OnSysCommand(WPARAM wParam, CPoint pt );
	void OnBkBtnClose();
    void OnBkBtnMax();
    void OnBkBtnMin();
	CSignScanUIHandler *SignScanUIHandler;
	CServerManageUIHandler *ServerManageHandler;
	CProcessManageUIHandler *ProcessManageHandler;
	CRunManageUIHandler *RunManageHandler;
	CRightButtonUIHandler *RightButtonHandler;
	CUpanUIHandler *UpanHandler;
	CSystemInfoUIHandler *SystemInfoHandler;

	KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
        KUI_NOTIFY_ID_COMMAND(60001, OnBkBtnClose)
        KUI_NOTIFY_ID_COMMAND(60002, OnBkBtnMax)
        KUI_NOTIFY_ID_COMMAND(60003, OnBkBtnMin)
    KUI_NOTIFY_MAP_END()
	BEGIN_MSG_MAP_EX(CMainWnd)
		MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP(CKuiDialogImpl<CMainWnd>)
		CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CMainWnd>)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_SYSCOMMAND(OnSysCommand)
		MSG_WM_DESTROY(OnDestroy)
		CHAIN_MSG_MAP_MEMBER((*SignScanUIHandler))
		CHAIN_MSG_MAP_MEMBER((*ServerManageHandler))
		CHAIN_MSG_MAP_MEMBER((*UpanHandler))
		CHAIN_MSG_MAP_MEMBER((*SystemInfoHandler))
		CHAIN_MSG_MAP_MEMBER((*RunManageHandler))
		CHAIN_MSG_MAP_MEMBER((*RightButtonHandler))
		CHAIN_MSG_MAP_MEMBER((*ProcessManageHandler))
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
};
extern CMainWnd *g_pMainWnd;
