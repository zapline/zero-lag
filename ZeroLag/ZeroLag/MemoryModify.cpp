#include "StdAfx.h"
#include "MemoryModify.h"

CMemoryModify::CMemoryModify(void)
{
}

CMemoryModify::~CMemoryModify(void)
{
}

BOOL CMemoryModify::zWriteMemory(DWORD addr, DWORD data)
{
	HWND hwnd = FindWindow(NULL, Name);
	if (hwnd == 0)
	{
		return FALSE;
	}
	DWORD dwProcessId;
	GetWindowThreadProcessId(hwnd, &dwProcessId);
	HANDLE hProcess = OpenProcess(PROCESS_VM_WRITE |PROCESS_VM_READ ,FALSE,dwProcessId);
	if (INVALID_HANDLE_VALUE == hProcess)
	{
		return FALSE;
	}
	BOOL f = WriteProcessMemory(hProcess, (LPVOID)addr, (LPVOID)&data, sizeof(DWORD), NULL);
	CloseHandle(hProcess);
	return f;
}

void CMemoryModify::Init()
{
	TOKEN_PRIVILEGES TokenPrivileges;
	HANDLE hToken;

	LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &TokenPrivileges.Privileges[0].Luid);   
	OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);

	TokenPrivileges.PrivilegeCount = 1;   
	TokenPrivileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

	AdjustTokenPrivileges(hToken, FALSE, &TokenPrivileges, 0, NULL, NULL);
	CloseHandle(hToken);
}