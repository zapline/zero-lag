// FileMd5Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZeroLag.h"
#include "FileMd5Dlg.h"
#include ".\public\MD5.h"
#include "shlwapi.h"


// CFileMd5Dlg 对话框

IMPLEMENT_DYNAMIC(CFileMd5Dlg, CDialog)

CFileMd5Dlg::CFileMd5Dlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileMd5Dlg::IDD, pParent)
	, m_PathName(_T(""))
	, m_md5_16(_T(""))
	, m_md5_32(_T(""))
{

}

CFileMd5Dlg::~CFileMd5Dlg()
{
}

void CFileMd5Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_FILEMD5_PATHNAME, m_PathName);
	DDX_Text(pDX, IDC_EDIT_FILEMD5_16, m_md5_16);
	DDX_Text(pDX, IDC_EDIT_FILEMD5_32, m_md5_32);
}


BEGIN_MESSAGE_MAP(CFileMd5Dlg, CDialog)
	ON_BN_CLICKED(IDC_FILEMD5_16, &CFileMd5Dlg::OnBnClickedFilemd516)
	ON_BN_CLICKED(IDC_FILEMD5_32, &CFileMd5Dlg::OnBnClickedFilemd532)
END_MESSAGE_MAP()


// CFileMd5Dlg 消息处理程序

BOOL CFileMd5Dlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_md5_32 = MD5_Caculate_File(m_PathName);
	m_md5_16 = m_md5_32.Mid(8, 16);
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CFileMd5Dlg::OnBnClickedFilemd516()
{
	if(OpenClipboard())
	{
		EmptyClipboard();
		USES_CONVERSION;
		HGLOBAL hGlobal = GlobalAlloc(GHND | GMEM_SHARE, (strlen(T2A(m_md5_16))+1) * sizeof(TCHAR));
		char * pGlobal = (char*)GlobalLock(hGlobal);
		strcpy(pGlobal, T2A(m_md5_16));
		GlobalUnlock(hGlobal);
		SetClipboardData(CF_TEXT, hGlobal);
		CloseClipboard();
		MessageBox(L"複製成功，使用ctrl+v黏貼該md5！");
	}
	else
	{
		MessageBox(L"複製失敗！");
	}
}

void CFileMd5Dlg::OnBnClickedFilemd532()
{
	if(OpenClipboard())
	{
		EmptyClipboard();
		USES_CONVERSION;
		HGLOBAL hGlobal = GlobalAlloc(GHND | GMEM_SHARE, (strlen(T2A(m_md5_32))+1) * sizeof(TCHAR));
		char * pGlobal = (char*)GlobalLock(hGlobal);
		strcpy(pGlobal, T2A(m_md5_32));
		GlobalUnlock(hGlobal);
		SetClipboardData(CF_TEXT, hGlobal);
		CloseClipboard();
		MessageBox(L"複製成功，使用ctrl+v黏貼該md5！");
	}
	else
	{
		MessageBox(L"複製失敗！");
	}
}
