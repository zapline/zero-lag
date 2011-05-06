#include "SignScanOptionDlg.h"


CSignScanOptionDlg::CSignScanOptionDlg(void) : CKuiDialogImpl<CSignScanOptionDlg>( "IDR_DLG_SIGNSCAN_OPTION" )
{
	SignScanFileType = 0;
	SignScanHideHave = FALSE;
}

CSignScanOptionDlg::CSignScanOptionDlg( BOOL xSignScanHideHave,int xSignScanFileType ) : CKuiDialogImpl<CSignScanOptionDlg>( "IDR_DLG_SIGNSCAN_OPTION" )
{
	SignScanHideHave = xSignScanHideHave;
	SignScanFileType = xSignScanFileType;

}

CSignScanOptionDlg::~CSignScanOptionDlg(void)
{
}

//这里等熟悉CKuiRadioBox后重写
LRESULT CSignScanOptionDlg::OnInitDialog( HWND hDlg, LPARAM lParam )
{
	(SignScanFileType==0)?SetItemCheck(11003,TRUE):SetItemCheck(11004,TRUE);
	SignScanHideHave?SetItemCheck(11006,TRUE):SetItemCheck(11005,TRUE);
	return TRUE;
}

void CSignScanOptionDlg::OnSubmit()
{
	GetItemCheck(11004)?SignScanFileType = 1:SignScanFileType = 0;
	SignScanHideHave = GetItemCheck(11006);
	EndDialog(IDOK);

}

void CSignScanOptionDlg::OnBkBtnClose()
{
	EndDialog(IDCANCEL);
}

void CSignScanOptionDlg::OnSysCommand(WPARAM wParam, CPoint pt )
{
	SetMsgHandled(FALSE);

	if ((wParam & 0xFFF0) == SC_CLOSE)
	{
		SetMsgHandled(TRUE);
		EndDialog(IDCANCEL);
	}
}