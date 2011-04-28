#include "StdAfx.h"
#include "ProcessModule.h"
#include <Tlhelp32.h>


CProcessModule::CProcessModule(void)
{
}

CProcessModule::~CProcessModule(void)
{
}

void CProcessModule::GetModule( int Uid,CListCtrl *pList )
{
	MODULEENTRY32 me32={0};
	CString szModuleBase;
	HANDLE hModuleSnap=::CreateToolhelp32Snapshot(TH32CS_SNAPMODULE,Uid);
	if(hModuleSnap==INVALID_HANDLE_VALUE)
		return;
	me32.dwSize=sizeof(MODULEENTRY32);
	if(::Module32First(hModuleSnap,&me32))
	{
		int i=0;
		do 
		{
			szModuleBase.Format(L"0x%08X",me32.hModule);
			pList->InsertItem(i,L"");
			pList->SetItemText(i,0,me32.szExePath);
			pList->SetItemText(i,1,szModuleBase);
			i++;

		}
		while(::Module32Next(hModuleSnap,&me32));
	}
	::CloseHandle(hModuleSnap);
}