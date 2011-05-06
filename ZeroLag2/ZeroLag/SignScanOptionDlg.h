#pragma once
#include "stdafx.h"

class CSignScanOptionDlg : public CKuiDialogImpl<CSignScanOptionDlg>
	, public CWHRoundRectFrameHelper<CSignScanOptionDlg>
{
public:
	CSignScanOptionDlg(void);
	CSignScanOptionDlg(BOOL xSignScanHideHave,int xSignScanFileType);
	~CSignScanOptionDlg(void);

	void OnSubmit();

	LRESULT OnInitDialog( HWND hDlg, LPARAM lParam );
	void OnSysCommand(WPARAM wParam, CPoint pt );
	void OnBkBtnClose();

	BOOL SignScanHideHave;
	int SignScanFileType;

	KUI_NOTIFY_MAP(IDC_RICHVIEW_WIN)
		KUI_NOTIFY_ID_COMMAND(11101, OnSubmit)
		KUI_NOTIFY_ID_COMMAND(60001, OnBkBtnClose)
	KUI_NOTIFY_MAP_END()

	BEGIN_MSG_MAP_EX(CSignScanOptionDlg)
		MSG_KUI_NOTIFY(IDC_RICHVIEW_WIN)
		CHAIN_MSG_MAP(CKuiDialogImpl<CSignScanOptionDlg>)	 
		CHAIN_MSG_MAP(CWHRoundRectFrameHelper<CSignScanOptionDlg>)
		MSG_WM_INITDIALOG(OnInitDialog)
		MSG_WM_SYSCOMMAND(OnSysCommand)
		REFLECT_NOTIFICATIONS_EX()
	END_MSG_MAP()
};

