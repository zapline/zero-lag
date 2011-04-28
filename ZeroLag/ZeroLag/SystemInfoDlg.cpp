// SystemInfoDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZeroLag.h"
#include "SystemInfoDlg.h"


// CSystemInfoDlg 对话框

IMPLEMENT_DYNAMIC(CSystemInfoDlg, CDialog)

CSystemInfoDlg::CSystemInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSystemInfoDlg::IDD, pParent)
{

}

CSystemInfoDlg::~CSystemInfoDlg()
{
}

void CSystemInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSystemInfoDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CPU, &CSystemInfoDlg::OnBnClickedButtonCpu)
END_MESSAGE_MAP()


// CSystemInfoDlg 消息处理程序

void CSystemInfoDlg::OnBnClickedButtonCpu()
{
	CStringA temp;
	char name[20] = {0},type[40] = {0};
	SystemInfo.Cpu.GetName(name);
	SystemInfo.Cpu.GetTypeName(type);
	temp.Format("Name:\t%s\r\nType:\t%s",name,type);
	MessageBoxA(0,temp,"",0);
}
