#include "ProcessManageUIHandler.h"		   
#include "stdafx.h"
#include "MainWnd.h"

void CProcessManageUIHandler::init(CMainWnd *p)
{
	pMain = p;

	DWORD dwStyle = WS_CHILD|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL|LVS_OWNERDRAWFIXED;
	if (ProcessList.Create( pMain->GetRichWnd(),  NULL, NULL, dwStyle, 0, 4001 ))
	{
		DWORD dwExStyle = LVS_EX_FULLROWSELECT;
		dwExStyle |= ProcessList.GetExtendedListViewStyle();

		ProcessList.SetExtendedListViewStyle(dwExStyle);

		ProcessList.InsertColumn( 0, _T("pid"), LVCFMT_LEFT, 100);
		ProcessList.InsertColumn( 1, _T("½ø³ÌÃû"), LVCFMT_LEFT, 500);

		ProcessList.Init();

		Scan();
	}
}



CProcessManageUIHandler::CProcessManageUIHandler(void)
{
}


CProcessManageUIHandler::~CProcessManageUIHandler(void)
{
}

void CProcessManageUIHandler::Scan()
{
	ProcessList.DeleteAllItems();

	ProcessManage = new CProcessManage();

	hThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)EnumProcesseThread,this,0,0);

}

CString CProcessManageUIHandler::GetFilenameInPathname( CStringA pathname )
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

void CProcessManageUIHandler::OnProcessScan()
{
	Scan();

}
void EnumProcesseThread( LPVOID param )
{
	CProcessManageUIHandler *p = (CProcessManageUIHandler *)param;
	CStringA temp;

	p->ProcessManage->Init2();
	for (int i=0;i<p->ProcessManage->GetCount();i++)
	{
		p->ProcessList.InsertItem(i, "");
		temp.Format("%d", p->ProcessManage->GetProcessInfo(i).pid);
		p->ProcessList.SetItemText(i, 0, temp);
		p->ProcessList.SetItemText(i, 1, p->ProcessManage->GetProcessInfo(i).name);
	}
	delete p->ProcessManage;
	CloseHandle(p->hThread);
}