#include "stdafx.h"
#include ".\mainwnd.h"
CMainWnd *g_pMainWnd = NULL;

CMainWnd::CMainWnd(void) : CKuiDialogImpl<CMainWnd>( "IDR_DLG_MAIN" )
{
	g_pMainWnd = this;
	SignScanPath = L"c:\\windows\\system32\\";
}

CMainWnd::~CMainWnd(void)
{
}

LRESULT CMainWnd::OnInitDialog( HWND hDlg, LPARAM lParam )
{
	DWORD dwStyle = WS_CHILD|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL|LVS_OWNERDRAWFIXED;

	if( SignScanListCtrl.Create( GetRichWnd(),  NULL, NULL, dwStyle, 0, 1001 ) )
	{
		if( SignScanPathEdit.Create( GetRichWnd(), NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER , 0, 1002 ) )
		{
			SignScanPathEdit.SetDlgCtrlID( 1002 );
			SignScanPathEdit.SetWindowText(SignScanPath);
		}

		DWORD dwExStyle = LVS_EX_FULLROWSELECT;
		dwExStyle |= SignScanListCtrl.GetExtendedListViewStyle();
		SignScanListCtrl.SetExtendedListViewStyle(dwExStyle);

		SignScanListCtrl.InsertColumn( 0, _T("文件名"), LVCFMT_LEFT, 500);
		SignScanListCtrl.InsertColumn( 1, _T("数字签名"), LVCFMT_LEFT, 100);

		SignScanListCtrl.Init();

		SetItemVisible(1103,FALSE);
		SetItemVisible(1104,FALSE);
		SignScanThreadStatus = 0;

		SignScanFileType = 0;
		SignScanHideHave = FALSE;
	}

	if( ServerManageListCtrl.Create( GetRichWnd(),  NULL, NULL, dwStyle, 0, 2001 ) )
	{
		DWORD dwExStyle = LVS_EX_FULLROWSELECT;
		dwExStyle |= ServerManageListCtrl.GetExtendedListViewStyle();
		ServerManageListCtrl.SetExtendedListViewStyle(dwExStyle);

		ServerManageListCtrl.InsertColumn( 0, _T("服务名称"), LVCFMT_LEFT, 250);
		ServerManageListCtrl.InsertColumn( 1, _T("服务描述"), LVCFMT_LEFT, 400);
		ServerManageListCtrl.InsertColumn( 2, _T("服务状态"), LVCFMT_LEFT, 100);

		ServerManageListCtrl.Init();

		ServerManageHide = FALSE;
		ServerManageFlush();
	}
	CenterWindow();
	return TRUE;
}

void CMainWnd::OnDestroy()
{
    PostQuitMessage(0);
}

void CMainWnd::OnBkBtnMax()
{
	if (WS_MAXIMIZE == (GetStyle() & WS_MAXIMIZE))
	{
		SendMessage(WM_SYSCOMMAND, SC_RESTORE | HTCAPTION, 0);
	}
	else
	{
		SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE | HTCAPTION, 0);
	}
}

void CMainWnd::OnBkBtnMin()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE | HTCAPTION, 0);
}

void CMainWnd::OnBkBtnClose()
{
	DestroyWindow();
}

void CMainWnd::OnSysCommand(WPARAM wParam, CPoint pt )
{
	SetMsgHandled(FALSE);

	switch (wParam & 0xFFF0)
	{
	case SC_CLOSE:
		SetMsgHandled(TRUE);
		DestroyWindow();
		break;
	case SC_RESTORE:
		{
			DWORD dwStyle = GetStyle();
			if (WS_MINIMIZE == (dwStyle & WS_MINIMIZE))
				break;

			if (WS_MAXIMIZE == (dwStyle & WS_MAXIMIZE))
			{
				SetItemAttribute(IDC_BTN_SYS_MAX, "skin", "maxbtn");
				break;
			}
		}
	case SC_MAXIMIZE:
		SetItemAttribute(IDC_BTN_SYS_MAX, "skin", "restorebtn");
		break;
	}
}

CString CMainWnd::GetDirector(CString title)
{
	ITEMIDLIST *ppidl; 
	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP ,&ppidl); 
	if ( ppidl == NULL) 
	{ 
		MessageBox(_T("启动路径浏览失败") ) ; 
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

void CMainWnd::OnSignScanChoicePath()
{
	SignScanPathEdit.SetWindowTextA(GetDirector( "选择扫描目录"));
}

void CMainWnd::OnSignScanBegin()
{
	SignScanListCtrl.DeleteAllItems();
	SignScanPathEdit.GetWindowTextA(SignScanPath);

	//防止以 \ 結尾的目錄名被判定為無效
	if (SignScanPath.GetAt(SignScanPath.GetLength()-1) == '\\')
	{
		SignScanPath.Delete(SignScanPath.GetLength()-1);
	}

	//數字簽名掃描目錄有效性判斷
	WIN32_FIND_DATA wfd;
	bool rValue = false;
	HANDLE hFind = FindFirstFile(SignScanPath, &wfd);
	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		FindClose(hFind);
	}
	else
	{
		MessageBox("目录无效！");
		return;
	}
	SignScan.SetInitDir(SignScanPath);

	SetItemVisible(1102,FALSE);
	SetItemVisible(1103,TRUE);
	SetItemVisible(1104,TRUE);
	
	SignScanThreadStatus = 1;

	SignScan.pList = &SignScanListCtrl;

	SignScanhThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)SignScanThread,this,0,0);
}

void CMainWnd::OnSignScanPause()
{
	if (SignScanThreadStatus == 1)
	{
		SignScanThreadStatus = 2;
		SuspendThread(SignScanhThread);
		SetItemText(1103, "继续扫描" );
	} 
	else if (SignScanThreadStatus == 2)
	{
		SignScanThreadStatus = 1;
		ResumeThread(SignScanhThread);
		SetItemText(1103, "暂停扫描" );
	}

}

void CMainWnd::OnSignScanEnd()
{
	SignScanThreadStatus = 0;
	TerminateThread(SignScanhThread,0);
	CloseHandle(SignScanhThread);
	SetItemText(1103, "暂停扫描" );
	SetItemVisible(1102,TRUE);
	SetItemVisible(1103,FALSE);
	SetItemVisible(1104,FALSE);
}

void CMainWnd::OnSignScanOption()
{

}

void CMainWnd::ServerManageFlush()
{
	//獲得隱藏未運行複選框的狀態

	ServerManageListCtrl.DeleteAllItems();

	ENUM_SERVICE_STATUS* lpservice = NULL;
	DWORD servicesReturned = 0;
	ServerManage.EnumServername(&lpservice,SERVICE_WIN32|SERVICE_DRIVER,SERVICE_STATE_ALL,&servicesReturned);

	unsigned j=0;
	for(unsigned i=0;i < servicesReturned;i++)
	{
		if (lpservice[i].ServiceStatus.dwCurrentState == SERVICE_RUNNING)
		{
			ServerManageListCtrl.InsertItem(j, "");
			ServerManageListCtrl.SetItemText(j,0,lpservice[i].lpServiceName);
			ServerManageListCtrl.SetItemText(j,1,lpservice[i].lpDisplayName);
			ServerManageListCtrl.SetItemText(j,2, "正运行");
			j++;
		}
		else if (ServerManageHide == FALSE)
		{
			ServerManageListCtrl.InsertItem(j, "");
			ServerManageListCtrl.SetItemText(j,0,lpservice[i].lpServiceName);
			ServerManageListCtrl.SetItemText(j,1,lpservice[i].lpDisplayName);
			ServerManageListCtrl.SetItemText(j,2, "已停止");
			j++;
		}
	}
}
void SignScanThread( LPVOID param )
{
	CMainWnd *p = (CMainWnd *)param;

	p->SignScan.SetFileCount(0);
	p->SignScan.SetSubdirCount(0);

	p->SignScan.HideHave = p->SignScanHideHave;
	switch (p->SignScanFileType)
	{
	case 0:
		p->SignScan.BeginBrowse("*.exe");
		break;
	case 1:
		p->SignScan.BeginBrowse("*.*");
		break;
	default:
		p->MessageBox( "扫描文件类型错误" );
	}

	CString temp;
	temp.Format( "共扫描 %d 个目录，%d 个文件。", p->SignScan.GetSubdirCount(), p->SignScan.GetFileCount());
	p->MessageBox(temp);

	CloseHandle(p->SignScanhThread);
// 	p->m_bbegin.EnableWindow(TRUE);
// 	p->m_bp.EnableWindow(FALSE);
// 	p->m_bend.EnableWindow(FALSE);
// 	p->m_bp.SetWindowText(L"暫停掃描");
// 	p->ThreadStatus = 0;

	ExitThread(0);
}
