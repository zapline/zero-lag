// AutoShutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZeroLag.h"
#include "AutoShutDlg.h"


// CAutoShutDlg 对话框

IMPLEMENT_DYNAMIC(CAutoShutDlg, CDialog)

CAutoShutDlg::CAutoShutDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAutoShutDlg::IDD, pParent)
	, m_ShutTime(0)
{
	status = 0;
}

CAutoShutDlg::~CAutoShutDlg()
{
}

void CAutoShutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_AUTOSHUT_SET, m_ButtonSet);
	DDX_DateTimeCtrl(pDX, IDC_DATETIMEPICKER1, m_ShutTime);
}


BEGIN_MESSAGE_MAP(CAutoShutDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_AUTOSHUT_SET, &CAutoShutDlg::OnBnClickedButtonAutoshutSet)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CAutoShutDlg 消息处理程序

void CAutoShutDlg::OnBnClickedButtonAutoshutSet()
{
	if (status == 0)
	{
		status = 1;
		m_ButtonSet.SetWindowText(L"停止計時");
		SetTimer(110, 1000, NULL);

	} 
	else
	{
		status = 0;
		m_ButtonSet.SetWindowText(L"開始計時");
		KillTimer(110);
	}
}

void CAutoShutDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 110)
	{
		UpdateData(TRUE);
		m_ShutTime -= CTimeSpan(0,0,0,1);
		UpdateData(FALSE);

		if(m_ShutTime <= CTime(2000,1,1,0,0,0))
		{
			KillTimer(110);
			//MessageBox(L"shut");
			AdjustToken();
			ExitWindowsEx(EWX_POWEROFF | EWX_SHUTDOWN | EWX_FORCE, 0);
		}
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CAutoShutDlg::AdjustToken()
{
	HANDLE hdlProcessHandle;
	HANDLE hdlTokenHandle;
	LUID tmpLuid;
	TOKEN_PRIVILEGES tkp;
	TOKEN_PRIVILEGES tkpNewButIgnored;
	DWORD lBufferNeeded;

	hdlProcessHandle = GetCurrentProcess();
	OpenProcessToken(hdlProcessHandle, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hdlTokenHandle);
	if(LookupPrivilegeValue(L"", SE_SHUTDOWN_NAME, &tmpLuid) == 0)
	{
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
			);
		LocalFree( lpMsgBuf );
	}
	tkp.PrivilegeCount = 1;    // One privilege to set
	tkp.Privileges->Luid = tmpLuid;
	tkp.Privileges->Attributes = SE_PRIVILEGE_ENABLED;
	if(AdjustTokenPrivileges(hdlTokenHandle, FALSE, &tkp, sizeof(tkpNewButIgnored), &tkpNewButIgnored, &lBufferNeeded) == 0)
	{
		LPVOID lpMsgBuf;
		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL 
			);
		LocalFree( lpMsgBuf );
	}
	return TRUE;
}
BOOL CAutoShutDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ShutTime = CTime(2000, 1, 1, 9, 0, 0);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAutoShutDlg::OnOK()
{
	KillTimer(110);
	DestroyWindow();
	delete this;
}

void CAutoShutDlg::OnCancel()
{
	KillTimer(110);
	DestroyWindow();
	delete this;
}
