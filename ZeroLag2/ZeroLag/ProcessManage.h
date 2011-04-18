#pragma once
#include "tlhelp32.h"
#include "psapi.h"
#pragma comment(lib,"psapi.lib")
#include "Shlwapi.h"
#include "vector"
using namespace std;

typedef struct _ProcessStruct
{
	DWORD pid;
	char name[MAX_PATH];
}ProcessStruct;

class CProcessManage
{
public:
	CProcessManage(void);
public:
	~CProcessManage(void);

	void Init();
	void Init2();
	int GetCount();
	ProcessStruct GetProcessInfo(int i);
	BOOL TerminateProcessById(DWORD dwId);

private:
	vector<ProcessStruct> ProcessList;
	int Count;

	BOOL  AdjustPurview();
	void PrintProcessNameAndID(DWORD processID, LPSTR pPathName);
};
