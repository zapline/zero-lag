// SignScanDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZeroLag.h"
#include "SignScanDlg.h"
#include "process.h"
#include "PeInfoDlg.h"
#include "FileMd5Dlg.h"


// CSignScanDlg 对话框

IMPLEMENT_DYNAMIC(CSignScanDlg, CDialog)

CSignScanDlg::CSignScanDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSignScanDlg::IDD, pParent)
	, m_path(_T("c:\\windows\\system32"))
{

}

CSignScanDlg::~CSignScanDlg()
{
}

void CSignScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SIGNSCANADDR, m_path);
	DDX_Control(pDX, IDC_LIST_SIGNSANG, m_lcScan);
	DDX_Control(pDX, IDC_BUTTON_SIGNSCANBEGIN, m_bbegin);
	DDX_Control(pDX, IDC_BUTTON_SIGNSCANP, m_bp);
	DDX_Control(pDX, IDC_BUTTON_SIGNSCANEND, m_bend);
}


BEGIN_MESSAGE_MAP(CSignScanDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_SIGNSCANMENU, &CSignScanDlg::OnBnClickedButtonSignscanmenu)
	ON_BN_CLICKED(IDC_BUTTON_SIGNSCANBEGIN, &CSignScanDlg::OnBnClickedButtonSignscanbegin)
	ON_BN_CLICKED(IDC_BUTTON_SIGNSCANP, &CSignScanDlg::OnBnClickedButtonSignscanp)
	ON_BN_CLICKED(IDC_BUTTON_SIGNSCANEND, &CSignScanDlg::OnBnClickedButtonSignscanend)
	ON_BN_CLICKED(IDC_BUTTON_SIGNSCANFILETYPE, &CSignScanDlg::OnBnClickedButtonSignscanfiletype)
	ON_COMMAND(ID_MSIGNSCAN_GOTO, &CSignScanDlg::OnMsignscanGoto)
	ON_COMMAND(ID_MSIGNSCAN_BAIDU, &CSignScanDlg::OnMsignscanBaidu)
	ON_COMMAND(ID_MSIGNSCAN_PEINFO, &CSignScanDlg::OnMsignscanPeinfo)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_SIGNSANG, &CSignScanDlg::OnNMRclickListSignsang)
	ON_COMMAND(ID_MSIGNSCAN_FILEMD5, &CSignScanDlg::OnMsignscanFilemd5)
END_MESSAGE_MAP()


// CSignScanDlg 消息处理程序

void CSignScanDlg::OnBnClickedButtonSignscanmenu()
{
	m_path = GetDirector(L"選擇目錄");
	UpdateData(FALSE);
}

char* CString2Str(CString& str)
{
	char* ret = new char[1024];
	//假設1024足夠長
	memset(ret, 0, 1024);

	WideCharToMultiByte(CP_ACP, NULL, str.GetBuffer(), 1024, ret, 1024, 0, 0);

	return ret;
}

void SignScanThread(LPVOID param)
{
	CSignScanDlg *p = (CSignScanDlg *)param;
	
	p->scan.SetFileCount(0);
	p->scan.SetSubdirCount(0);

	p->scan.HideHave = p->HideHave;
	switch (p->FileType)
	{
	case 0:
		p->scan.BeginBrowse("*.exe");
		break;
	case 1:
		p->scan.BeginBrowse("*.*");
		break;
	default:
		p->MessageBox(L"掃描文件類型錯誤");
	}
	CString temp;
	temp.Format(L"共掃描 %d 個目錄，%d 個文件。",p->scan.GetSubdirCount(),p->scan.GetFileCount());
	p->MessageBox(temp);

	CloseHandle(p->hThread);
	p->m_bbegin.EnableWindow(TRUE);
	p->m_bp.EnableWindow(FALSE);
	p->m_bend.EnableWindow(FALSE);
	p->m_bp.SetWindowText(L"暫停掃描");
	p->ThreadStatus = 0;

	ExitThread(0);
}

void CSignScanDlg::OnBnClickedButtonSignscanbegin()
{
	m_lcScan.DeleteAllItems();

	UpdateData(TRUE);

	//防止以 \ 結尾的目錄名被判定為無效
	if (m_path.GetAt(m_path.GetLength()-1) == '\\')
	{
		m_path.Delete(m_path.GetLength()-1);
	}

	//數字簽名掃描目錄有效性判斷
	WIN32_FIND_DATA wfd;
	bool rValue = false;
	HANDLE hFind = FindFirstFile(m_path, &wfd);
	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		FindClose(hFind);
	}
	else
	{
		MessageBox(L"目錄無效！");
		return;
	}
	scan.SetInitDir(CString2Str(m_path));

	m_bbegin.EnableWindow(FALSE);
	m_bp.EnableWindow(TRUE);
	m_bend.EnableWindow(TRUE);
	ThreadStatus = 1;

	scan.pList = &m_lcScan;
	
	hThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)SignScanThread,this,0,0);
}

CString CSignScanDlg::GetDirector(CString title)
{
	ITEMIDLIST *ppidl; 
	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP ,&ppidl); 
	if ( ppidl == NULL) 
	{ 
		AfxMessageBox(_T("启动路径浏览失败") ) ; 
		return _T("error"); 
	} 
	TCHAR path[255] = _T(""); 
	BROWSEINFO *bi=new BROWSEINFO; 
	bi->hwndOwner=NULL; 
	bi->pidlRoot=ppidl; 
	bi->pszDisplayName=NULL; 
	bi->lpszTitle=title; 
	bi->lpfn=NULL; 
	bi->ulFlags=/*BIF_BROWSEINCLUDEFILES|*/BIF_EDITBOX |BIF_RETURNONLYFSDIRS ; 
	ppidl = SHBrowseForFolder(bi); 
	if ( !SHGetPathFromIDList(ppidl,path) ) 
	{ 
		delete bi; 
		return _T("error") ; 
	} 
	delete bi; 
	CString s = path ; 
	if ( s.Right( 1 ) != _T("\\") ) 
		s+= _T("\\") ; 
	return s ;
}

BOOL CSignScanDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_lcScan.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_lcScan.InsertColumn(0,L"文件名",LVCFMT_LEFT,360);
	m_lcScan.InsertColumn(1,L"數字簽名",LVCFMT_LEFT,80);

	m_bp.EnableWindow(FALSE);
	m_bend.EnableWindow(FALSE);
	ThreadStatus = 0;

	FileType = 0;
	HideHave = FALSE;
	return TRUE;
}

void CSignScanDlg::OnBnClickedButtonSignscanp()
{
	if (ThreadStatus == 1)
	{
		SuspendThread(hThread);
		m_bp.SetWindowText(L"繼續掃描");
		ThreadStatus = 2;
	}
	else if (ThreadStatus == 2)
	{
		ResumeThread(hThread);
		m_bp.SetWindowText(L"暫停掃描");
		ThreadStatus = 1;
	}
	
}

void CSignScanDlg::OnBnClickedButtonSignscanend()
{
	m_bbegin.EnableWindow(TRUE);
	m_bp.EnableWindow(FALSE);
	m_bend.EnableWindow(FALSE);
	TerminateThread(hThread,0);
	CloseHandle(hThread);
	m_bp.SetWindowText(L"暫停掃描");
	ThreadStatus = 0;
}

void CSignScanDlg::OnBnClickedButtonSignscanfiletype()
{
	CSignScanFileTypeDlg dlg;
	dlg.m_FileType = FileType;
	if (HideHave == FALSE)
	{
		dlg.m_HideHave = 0;
	}
	else
	{
		dlg.m_HideHave = 1;
	}
	
	if (dlg.DoModal() == IDOK)
	{
		FileType = dlg.m_FileType;
		if (dlg.m_HideHave == 0)
		{
			HideHave = FALSE;
		}
		else
		{
			HideHave = TRUE;
		}
	}
}

void CSignScanDlg::OnMsignscanGoto()
{
	POSITION pos = m_lcScan.GetFirstSelectedItemPosition();
	int nItem = m_lcScan.GetNextSelectedItem(pos);
	CString pathname = m_lcScan.GetItemText(nItem, 0);
	CString sparam;
	sparam.Format(L"/select,%s",pathname);
	ShellExecute(0, L"open", L"explorer.exe", sparam , NULL,SW_SHOWNORMAL);
}

void CSignScanDlg::OnMsignscanBaidu()
{
	POSITION pos = m_lcScan.GetFirstSelectedItemPosition();
	int nItem = m_lcScan.GetNextSelectedItem(pos);
	CString pathname = m_lcScan.GetItemText(nItem, 0);
	CString url;
	url.Format(L"http://www.baidu.com/s?wd=%s", GetFilenameInPathname(pathname));
	ShellExecute(0, L"open", url, L"", L"", SW_SHOW );
}

void CSignScanDlg::OnMsignscanPeinfo()
{
	CPeInfoDlg dlg;
	POSITION pos = m_lcScan.GetFirstSelectedItemPosition();
	int nItem = m_lcScan.GetNextSelectedItem(pos);
	dlg.PathName = m_lcScan.GetItemText(nItem, 0);
	dlg.FileName = GetFilenameInPathname(dlg.PathName);
	dlg.DoModal();
}

void CSignScanDlg::OnNMRclickListSignsang(NMHDR *pNMHDR, LRESULT *pResult)
{
	//获得鼠标
	LPPOINT lpoint=new tagPOINT;   
	::GetCursorPos(lpoint);   
	CMenu menu,*pSubMenu; 
	//加载菜单 
	menu.LoadMenu(IDR_MENU_RIGHT);
	//加载子菜单,设置菜单弹出项目起始位置 
	pSubMenu=menu.GetSubMenu(0);
	//显示菜单
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this); 
	pSubMenu->DestroyMenu();
	*pResult = 0;
}

CString CSignScanDlg::GetFilenameInPathname(CString pathname)
{
	int i,j=0;
	i = pathname.Find('\\');
	while (i != -1)
	{
		j = i;
		i = pathname.Find('\\',j+1);
	}
	return pathname.Mid(j+1);
}

void CSignScanDlg::OnMsignscanFilemd5()
{
	CFileMd5Dlg dlg;
	POSITION pos = m_lcScan.GetFirstSelectedItemPosition();
	int nItem = m_lcScan.GetNextSelectedItem(pos);
	dlg.m_PathName = m_lcScan.GetItemText(nItem, 0);
	dlg.DoModal();
}
