// ProcessManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZeroLag.h"
#include "ProcessManageDlg.h"
#include "PeInfoDlg.h"
#include "ProcessModuleDlg.h"


// CProcessManageDlg 对话框

IMPLEMENT_DYNAMIC(CProcessManageDlg, CDialog)

CProcessManageDlg::CProcessManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessManageDlg::IDD, pParent)
{

}

CProcessManageDlg::~CProcessManageDlg()
{
}

void CProcessManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROCESS, m_tcProcessList);
	DDX_Control(pDX, IDC_PROCESSM_SCAN, m_bbegin);
}


BEGIN_MESSAGE_MAP(CProcessManageDlg, CDialog)
	ON_BN_CLICKED(IDC_PROCESSM_SCAN, &CProcessManageDlg::OnBnClickedProcessmScan)
	ON_COMMAND(ID_PROCESSM_GOTO, &CProcessManageDlg::OnProcessmGoto)
	ON_COMMAND(ID_PROCESSM_BAIDU, &CProcessManageDlg::OnProcessmBaidu)
	ON_COMMAND(ID_PROCESSM_PEINFO, &CProcessManageDlg::OnProcessmPeinfo)
	ON_COMMAND(ID_PROCESSM_CLOSE, &CProcessManageDlg::OnProcessmClose)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_PROCESS, &CProcessManageDlg::OnNMRclickListProcess)
	ON_COMMAND(ID_PROCESS_MODULE, &CProcessManageDlg::OnProcessModule)
END_MESSAGE_MAP()


// CProcessManageDlg 消息处理程序

void CProcessManageDlg::OnBnClickedProcessmScan()
{
	m_bbegin.EnableWindow(FALSE);
	m_tcProcessList.DeleteAllItems();

	ProcessManage = new CProcessManage();

	hThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)EnumProcesseThread,this,0,0);
}

void EnumProcesseThread(LPVOID param)
{
	CProcessManageDlg *p = (CProcessManageDlg *)param;

	CString temp;

	p->ProcessManage->Init();
	for (int i=0;i<p->ProcessManage->GetCount();i++)
	{
		p->m_tcProcessList.InsertItem(i, L"");
		temp.Format(L"%d", p->ProcessManage->GetProcessInfo(i).pid);
		p->m_tcProcessList.SetItemText(i, 0, temp);
		p->m_tcProcessList.SetItemText(i, 1, p->ProcessManage->GetProcessInfo(i).name);
	}

	delete p->ProcessManage;
	p->m_bbegin.EnableWindow(TRUE);
	CloseHandle(p->hThread);
}

BOOL CProcessManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_tcProcessList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_tcProcessList.InsertColumn(0, L"pid", LVCFMT_LEFT, 80);
	m_tcProcessList.InsertColumn(1, L"name", LVCFMT_LEFT, 400);

	//自動進行一次掃描
	OnBnClickedProcessmScan();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CProcessManageDlg::OnProcessmGoto()
{
	POSITION pos = m_tcProcessList.GetFirstSelectedItemPosition();
	int nItem = m_tcProcessList.GetNextSelectedItem(pos);
	CString pathname = m_tcProcessList.GetItemText(nItem, 1);
	CString sparam;
	sparam.Format(L"/select,%s",pathname);
	ShellExecute(0, L"open", L"explorer.exe", sparam , NULL,SW_SHOWNORMAL);
}

void CProcessManageDlg::OnProcessmBaidu()
{
	POSITION pos = m_tcProcessList.GetFirstSelectedItemPosition();
	int nItem = m_tcProcessList.GetNextSelectedItem(pos);
	CString pathname = m_tcProcessList.GetItemText(nItem, 1);
	CString url;
	url.Format(L"http://www.baidu.com/s?wd=%s", GetFilenameInPathname(pathname));
	ShellExecute(0, L"open", url, L"", L"", SW_SHOW );
}

void CProcessManageDlg::OnProcessmPeinfo()
{
	CPeInfoDlg dlg;
	POSITION pos = m_tcProcessList.GetFirstSelectedItemPosition();
	int nItem = m_tcProcessList.GetNextSelectedItem(pos);
	dlg.PathName = m_tcProcessList.GetItemText(nItem, 1);
	dlg.FileName = GetFilenameInPathname(dlg.PathName);
	dlg.DoModal();
}

void CProcessManageDlg::OnProcessmClose()
{
	POSITION pos = m_tcProcessList.GetFirstSelectedItemPosition();
	int nItem = m_tcProcessList.GetNextSelectedItem(pos);
	DWORD pid = _wtoi(m_tcProcessList.GetItemText(nItem, 0));
	if (ProcessManage->TerminateProcessById(pid) == FALSE)
	{
		MessageBox(L"結束進程失敗！");
	}	
	else
	{
		//結束進程後刷新進程列表
		OnBnClickedProcessmScan();
	}
}

void CProcessManageDlg::OnNMRclickListProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	//获得鼠标
	LPPOINT lpoint=new tagPOINT;   
	::GetCursorPos(lpoint);   
	CMenu menu,*pSubMenu; 
	//加载菜单 
	menu.LoadMenu(IDR_MENU_RIGHT);
	//加载子菜单,设置菜单弹出项目起始位置 
	pSubMenu=menu.GetSubMenu(2);
	//显示菜单
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this); 
	pSubMenu->DestroyMenu();
	*pResult = 0;
}

CString CProcessManageDlg::GetFilenameInPathname(CString pathname)
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
void CProcessManageDlg::OnProcessModule()
{
	POSITION pos = m_tcProcessList.GetFirstSelectedItemPosition();
	int nItem = m_tcProcessList.GetNextSelectedItem(pos);
	int pid = _wtoi(m_tcProcessList.GetItemText(nItem, 0));
	CProcessModuleDlg dlg;
	dlg.Pid = pid;
	dlg.DoModal();
}
