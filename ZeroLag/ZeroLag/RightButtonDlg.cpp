// RightButtonDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZeroLag.h"
#include "RightButtonDlg.h"


// CRightButtonDlg 对话框

IMPLEMENT_DYNAMIC(CRightButtonDlg, CDialog)

CRightButtonDlg::CRightButtonDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRightButtonDlg::IDD, pParent)
{
}

CRightButtonDlg::~CRightButtonDlg()
{
}

void CRightButtonDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRightButtonDlg, CDialog)
	ON_BN_CLICKED(IDC_RIGHT_RECYCLE, &CRightButtonDlg::OnBnClickedRightRecycle)
	ON_BN_CLICKED(IDC_RIGHT_RECYCLE2, &CRightButtonDlg::OnBnClickedRightRecycle2)
	ON_BN_CLICKED(IDC_RIGHT_MOVETO, &CRightButtonDlg::OnBnClickedRightMoveto)
	ON_BN_CLICKED(IDC_RIGHT_MOVETO2, &CRightButtonDlg::OnBnClickedRightMoveto2)
END_MESSAGE_MAP()


// CRightButtonDlg 消息处理程序

void CRightButtonDlg::OnBnClickedRightRecycle()
{
	RightButton.AddSystemRecycle();
	MessageBox(L"添加成功");
}

void CRightButtonDlg::OnBnClickedRightRecycle2()
{
	RightButton.DelSystemRecycle();
	MessageBox(L"移除成功");
}

void CRightButtonDlg::OnBnClickedRightMoveto()
{
	RightButton.AddSystemCutTo();
	MessageBox(L"添加成功");
}

void CRightButtonDlg::OnBnClickedRightMoveto2()
{
	RightButton.DelSystemCutTo();
	MessageBox(L"移除成功");
}
