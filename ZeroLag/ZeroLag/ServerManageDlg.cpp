// ServerManageDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZeroLag.h"
#include "ServerManageDlg.h"


// CServerManageDlg 对话框

IMPLEMENT_DYNAMIC(CServerManageDlg, CDialog)

CServerManageDlg::CServerManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CServerManageDlg::IDD, pParent)
	, m_ServerHide(FALSE)
{

}

CServerManageDlg::~CServerManageDlg()
{
}

void CServerManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SERVER, m_ServerList);
	DDX_Check(pDX, IDC_CHECK_SERVERHIDE, m_ServerHide);
}


BEGIN_MESSAGE_MAP(CServerManageDlg, CDialog)
	ON_BN_CLICKED(IDC_SERVER_FLUSH, &CServerManageDlg::OnBnClickedServerFlush)
	ON_COMMAND(ID_SERVER_STATUS, &CServerManageDlg::OnServerStatus)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_SERVER, &CServerManageDlg::OnNMRclickListServer)
	ON_BN_CLICKED(IDC_CHECK_SERVERHIDE, &CServerManageDlg::OnBnClickedCheckServerhide)
END_MESSAGE_MAP()


// CServerManageDlg 消息处理程序

void CServerManageDlg::OnBnClickedServerFlush()
{
	//獲得隱藏未運行複選框的狀態
	UpdateData(TRUE);

	m_ServerList.DeleteAllItems();

	ENUM_SERVICE_STATUS* lpservice = NULL;
	DWORD servicesReturned = 0;
	ServerManage.EnumServername(&lpservice,SERVICE_WIN32|SERVICE_DRIVER,SERVICE_STATE_ALL,&servicesReturned);

	unsigned j=0;
	for(unsigned i=0;i < servicesReturned;i++)
	{
		if (lpservice[i].ServiceStatus.dwCurrentState == SERVICE_RUNNING)
		{
			m_ServerList.InsertItem(j,L"");
			m_ServerList.SetItemText(j,0,lpservice[i].lpServiceName);
			m_ServerList.SetItemText(j,1,lpservice[i].lpDisplayName);
			m_ServerList.SetItemText(j,2,L"正運行");
			j++;
		}
		else if (m_ServerHide == FALSE)
		{
			m_ServerList.InsertItem(j,L"");
			m_ServerList.SetItemText(j,0,lpservice[i].lpServiceName);
			m_ServerList.SetItemText(j,1,lpservice[i].lpDisplayName);
			m_ServerList.SetItemText(j,2,L"已停止");
			j++;
		}
	}
}

BOOL CServerManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ServerList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_ServerList.InsertColumn(0,L"服務名稱",LVCFMT_LEFT,200);
	m_ServerList.InsertColumn(1,L"服務描述",LVCFMT_LEFT,300);
	m_ServerList.InsertColumn(2,L"服務狀態",LVCFMT_LEFT,100);

	OnBnClickedServerFlush();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CServerManageDlg::OnServerStatus()
{
	POSITION pos = m_ServerList.GetFirstSelectedItemPosition();
	int nItem = m_ServerList.GetNextSelectedItem(pos);
	CString SName = m_ServerList.GetItemText(nItem, 0);
	if (m_ServerList.GetItemText(nItem, 2) == "已停止")
	{
		ServerManage.ChangeServerStatusByname((wchar_t *)SName.GetString(), TRUE);
	} 
	else
	{
		ServerManage.ChangeServerStatusByname((wchar_t *)SName.GetString(), FALSE);
	}
	OnBnClickedServerFlush();
}

void CServerManageDlg::OnNMRclickListServer(NMHDR *pNMHDR, LRESULT *pResult)
{
	//获得鼠标
	LPPOINT lpoint=new tagPOINT;   
	::GetCursorPos(lpoint);   
	CMenu menu,*pSubMenu; 
	//加载菜单 
	menu.LoadMenu(IDR_MENU_RIGHT);
	//加载子菜单,设置菜单弹出项目起始位置 
	pSubMenu=menu.GetSubMenu(3);
	//显示菜单
	pSubMenu->TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this); 
	pSubMenu->DestroyMenu();

	*pResult = 0;
}

void CServerManageDlg::OnBnClickedCheckServerhide()
{
	OnBnClickedServerFlush();
}
