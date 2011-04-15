// RunManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZeroLag.h"
#include "RunManageDlg.h"


// CRunManageDlg 对话框

IMPLEMENT_DYNAMIC(CRunManageDlg, CDialog)

CRunManageDlg::CRunManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRunManageDlg::IDD, pParent)
{

}

CRunManageDlg::~CRunManageDlg()
{
}

void CRunManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_RUNMBEGIN, m_bBegin);
	DDX_Control(pDX, IDC_TREE_RUNMANAGE, m_tRunList);
}


BEGIN_MESSAGE_MAP(CRunManageDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_RUNMBEGIN, &CRunManageDlg::OnBnClickedButtonRunmbegin)
	ON_WM_TIMER()
	ON_COMMAND(ID_RUNM_GOTO, &CRunManageDlg::OnRunmGoto)
	ON_COMMAND(ID_RUNM_BAIDU, &CRunManageDlg::OnRunmBaidu)
	ON_NOTIFY(NM_RCLICK, IDC_TREE_RUNMANAGE, &CRunManageDlg::OnNMRclickTreeRunmanage)
END_MESSAGE_MAP()


// CRunManageDlg 消息处理程序

void CRunManageDlg::OnBnClickedButtonRunmbegin()
{
	//清空樹狀控件
	m_tRunList.DeleteAllItems();

	m_bBegin.EnableWindow(FALSE);
	ThreadStatus = 2;
	//全部掃描完畢時，ThreadStatus==0,按鈕恢復可用

	//0，註冊表啟動項掃描
	//1，文件夾啟動項掃描
	ht0 = m_tRunList.InsertItem(L"RegRun");
	ht1 = m_tRunList.InsertItem(L"DirRun");

	//100ms後刷新，展開樹狀控件
	CRunManageDlg::SetTimer(0, 100, 0);

	RunManage = new CRunManage();
	RunManage->init();
	hThread1 = CreateThread(0,0,(LPTHREAD_START_ROUTINE)ScanRegRunThread,this,0,0);
	hThread2 = CreateThread(0,0,(LPTHREAD_START_ROUTINE)ScanDirRunThread,this,0,0);
}

void ScanRegRunThread(LPVOID param)
{
	CRunManageDlg *p = (CRunManageDlg *)param;
	
	CString temp;

	int count = p->RunManage->RegEnumer->GetCount();
	if (count == 0)
	{
		p->m_tRunList.InsertItem(L"無開機啟動項", p->ht0);
	}
	else
	{
		for (int i=0;i<count;i++)
		{
			temp.Format(L"%s", p->RunManage->RegEnumer->GetItem(i).strPath);
			p->m_tRunList.InsertItem(temp, p->ht0);
		}
	}
	
	if (--(p->ThreadStatus) == 0)
	{
		p->m_bBegin.EnableWindow(TRUE);
		delete p->RunManage;
	}
	CloseHandle(p->hThread1);
}

void ScanDirRunThread(LPVOID param)
{
	CRunManageDlg *p = (CRunManageDlg *)param;

	CString temp;

	int count = p->RunManage->DirEnumer->GetCount();
	if (count == 0)
	{
		p->m_tRunList.InsertItem(L"無開機啟動項", p->ht1);
	}
	else
	{
		for (int i=0;i<count;i++)
		{
			temp.Format(L"%s", p->RunManage->DirEnumer->GetItem(i).strParam);
			p->m_tRunList.InsertItem(temp, p->ht0);
		}
	}

	if (--(p->ThreadStatus) == 0)
	{
		p->m_bBegin.EnableWindow(TRUE);
		delete p->RunManage;
	}
	CloseHandle(p->hThread2);
}
BOOL CRunManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	//自動進行一次掃描
	OnBnClickedButtonRunmbegin();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CRunManageDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 0)
	{
		//展開樹狀控件
		m_tRunList.Expand(ht0, TVE_EXPAND);
		m_tRunList.Expand(ht1, TVE_EXPAND);
		CRunManageDlg::KillTimer(0);
	}

	CDialog::OnTimer(nIDEvent);
}

void CRunManageDlg::OnRunmGoto()
{
	HTREEITEM  h = m_tRunList.GetSelectedItem();
	CString pathname = m_tRunList.GetItemText(h);
	CString sparam;
	sparam.Format(L"/select,%s",pathname);
	ShellExecute(0, L"open", L"explorer.exe", sparam , NULL,SW_SHOWNORMAL);
}

void CRunManageDlg::OnRunmBaidu()
{
	HTREEITEM  h = m_tRunList.GetSelectedItem();
	CString pathname = m_tRunList.GetItemText(h);
	CString url;
	url.Format(L"http://www.baidu.com/s?wd=%s", GetFilenameInPathname(pathname));
	ShellExecute(0, L"open", url, L"", L"", SW_SHOW );
}

void CRunManageDlg::OnNMRclickTreeRunmanage(NMHDR *pNMHDR, LRESULT *pResult)
{
	//获得鼠标
	LPPOINT lpoint=new tagPOINT;   
	::GetCursorPos(lpoint);   
	CMenu menu,*pSubMenu; 
	//加载菜单 
	menu.LoadMenu(IDR_MENU_RIGHT);
	//加载子菜单,设置菜单弹出项目起始位置 
	pSubMenu=menu.GetSubMenu(1);
	//显示菜单
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this); 
	pSubMenu->DestroyMenu();
	*pResult = 0;
}

CString CRunManageDlg::GetFilenameInPathname(CString pathname)
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