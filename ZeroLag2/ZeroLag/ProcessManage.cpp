#include "StdAfx.h"
#include "ProcessManage.h"

CProcessManage::CProcessManage(void)
{
}

CProcessManage::~CProcessManage(void)
{
	ProcessList.clear();
}

void CProcessManage::Init()
{
	DWORD aProcesses[1024], cbNeeded;
	ProcessStruct ps;

	AdjustPurview();

	//枚举系统进程ID列表
	if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
	{
		return;
	}
	//计算进程数量
	Count = cbNeeded / sizeof(DWORD);
	// 得到每个进程的名称和ID
	for (int i=0; i<Count;i++)
	{
		ps.pid = aProcesses[i];
		PrintProcessNameAndID(aProcesses[i], ps.name);
		ProcessList.push_back(ps);
	}
}

void CProcessManage::Init2()
{
	HANDLE hSnapshot=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (!hSnapshot)
	{
		MessageBox(0, "create snapshot failed!", "", 0);
		return;
	}

	PROCESSENTRY32 pe;
	ProcessStruct ps;
	Count = 0;

	pe.dwSize=sizeof(PROCESSENTRY32);
	BOOL retval=Process32First(hSnapshot,&pe);
	while(retval)
	{
		Count++;
		ps.pid = pe.th32ProcessID;
		//判断pid是否为0或者4
		if (ps.pid == 0)
		{
			StrCpy(ps.name,"System Idle Process");
		} 
		else if (ps.pid == 4)
		{
			StrCpy(ps.name,"System");
		}
		else
		{
			//判断获取到的是否为空
			PrintProcessNameAndID(pe.th32ProcessID,ps.name);
			if (ps.name[0] == 0)
			{
				if (pe.szExeFile[0] != 0)
				{							
					StrCpy(ps.name,"\\\\?\\");
					StrCpy(ps.name+4, pe.szExeFile);
				} 
				else
				{
					StrCpy(ps.name, "unknow");
				}
			}
		}
		ProcessList.push_back(ps);
		retval=Process32Next(hSnapshot,&pe);
	}

	CloseHandle(hSnapshot);
}

int CProcessManage::GetCount()
{
	return Count;
}

ProcessStruct CProcessManage::GetProcessInfo(int i)
{
	return ProcessList[i];
}

//提升进程权限
BOOL  CProcessManage::AdjustPurview()
{
	TOKEN_PRIVILEGES TokenPrivileges;
	BOOL bRet;
	HANDLE hToken;

	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &TokenPrivileges.Privileges[0].Luid);   
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);

	TokenPrivileges.PrivilegeCount = 1;   
	TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	bRet = AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, 0, NULL, NULL);

	CloseHandle(hToken);
	return bRet;
}


void CProcessManage::PrintProcessNameAndID(DWORD processID,LPSTR pPathName)
{
	//取得进程的句柄
	HANDLE hProcess = OpenProcess( 
		PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, 
		processID );
	memset(pPathName, 0, MAX_PATH);
	//取得进程名称
	if ( hProcess )
	{
		//HMODULE hMod;
		//DWORD cbNeeded;
		//if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) )
		{
			GetModuleFileNameEx(hProcess,NULL,pPathName,MAX_PATH);   
		}
	}
	CloseHandle( hProcess );
}

BOOL CProcessManage::TerminateProcessById(DWORD dwId)
{
	BOOL bRet=FALSE;
	HANDLE hProcess=OpenProcess(PROCESS_ALL_ACCESS,FALSE,dwId);
	if(hProcess!=NULL)
	{
		bRet=TerminateProcess(hProcess,0);
	}
	CloseHandle(hProcess);
	return bRet;
}