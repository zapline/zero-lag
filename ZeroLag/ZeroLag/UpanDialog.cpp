// UpanDialog.cpp : 实现文件
//

#include "stdafx.h"
#include "ZeroLag.h"
#include "UpanDialog.h"


// CUpanDialog 对话框

IMPLEMENT_DYNAMIC(CUpanDialog, CDialog)

CUpanDialog::CUpanDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CUpanDialog::IDD, pParent)
{

}

CUpanDialog::~CUpanDialog()
{
}

void CUpanDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_UPAN_DRIVELIST, m_DriveList);
	DDX_Control(pDX, IDC_COMBO_UPAN_DRIVELIST2, m_UpanList);
}


BEGIN_MESSAGE_MAP(CUpanDialog, CDialog)
	ON_BN_CLICKED(IDC_UPAN_CREATEAUTORUN, &CUpanDialog::OnBnClickedUpanCreateautorun)
	ON_CBN_DROPDOWN(IDC_COMBO_UPAN_DRIVELIST, &CUpanDialog::OnCbnDropdownComboUpanDrivelist)
	ON_BN_CLICKED(IDC_UPAN_KILLHIDE, &CUpanDialog::OnBnClickedUpanKillhide)
	ON_CBN_DROPDOWN(IDC_COMBO_UPAN_DRIVELIST2, &CUpanDialog::OnCbnDropdownComboUpanDrivelist2)
END_MESSAGE_MAP()


// CUpanDialog 消息处理程序

void CUpanDialog::OnBnClickedUpanCreateautorun()
{
	int index = m_DriveList.GetCurSel();
	if (index == CB_ERR)
	{
		//判斷是否已選擇磁盤
		MessageBox(L"請先選擇磁盤再點擊免疫按鈕！");
	}
	else
	{
		CString name;
		m_DriveList.GetLBText(index, name);
		WCHAR ch = name.GetAt(0);
		char n = *(char *)&ch;
		Upan.StopAutorun(n);
		MessageBox(L"免疫完成！");
	}
}

void CUpanDialog::OnCbnDropdownComboUpanDrivelist()
{
	m_DriveList.ResetContent();
	CString temp;
	for (char ch='C';ch<='Z';ch++)
	{
		if (Upan.IsEnableDrive(ch) == TRUE)
		{
			temp.Format(L"%c:",ch);
			m_DriveList.AddString(temp);
		}
	}
}

BOOL CUpanDialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CUpanDialog::OnBnClickedUpanKillhide()
{
	int index = m_UpanList.GetCurSel();
	if (index == CB_ERR)
	{
		//判斷是否已選擇磁盤
		MessageBox(L"請先選擇磁盤再點擊設置按鈕！");
	}
	else
	{
		CString name;
		m_UpanList.GetLBText(index, name);
		WCHAR ch = name.GetAt(0);
		char n = *(char *)&ch;
		MessageBox(L"請耐心等候命令行窗口自動關閉！");
		Upan.KillHide(n);
		MessageBox(L"設置完成！");
	}
}

void CUpanDialog::OnCbnDropdownComboUpanDrivelist2()
{
	m_UpanList.ResetContent();
	CString temp;
	for (char ch='D';ch<='Z';ch++)
	{
		if (Upan.IsRemoveDrive(ch) == TRUE)
		{
			temp.Format(L"%c:",ch);
			m_UpanList.AddString(temp);
		}
	}
}
