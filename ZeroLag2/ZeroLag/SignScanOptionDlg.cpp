#include "SignScanOptionDlg.h"


CSignScanOptionDlg::CSignScanOptionDlg(void) : CKuiDialogImpl<CSignScanOptionDlg>( "IDR_DLG_SIGNSCAN_OPTION" )
{
}


CSignScanOptionDlg::~CSignScanOptionDlg(void)
{
}

LRESULT CSignScanOptionDlg::OnInitDialog( HWND hDlg, LPARAM lParam )
{
	return TRUE;

}

void CSignScanOptionDlg::OnSubmit()
{
	CKuiMsgBox::Show("ok!");
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