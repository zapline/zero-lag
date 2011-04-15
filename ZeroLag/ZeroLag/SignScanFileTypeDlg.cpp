// SignScanFileTypeDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZeroLag.h"
#include "SignScanFileTypeDlg.h"


// CSignScanFileTypeDlg 对话框

IMPLEMENT_DYNAMIC(CSignScanFileTypeDlg, CDialog)

CSignScanFileTypeDlg::CSignScanFileTypeDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSignScanFileTypeDlg::IDD, pParent)
{

}

CSignScanFileTypeDlg::~CSignScanFileTypeDlg()
{
}

void CSignScanFileTypeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_FileType);
	DDX_Radio(pDX, IDC_RADIO3, m_HideHave);
}


BEGIN_MESSAGE_MAP(CSignScanFileTypeDlg, CDialog)
END_MESSAGE_MAP()


// CSignScanFileTypeDlg 消息处理程序
