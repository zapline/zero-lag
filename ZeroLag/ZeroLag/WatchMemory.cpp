#include "StdAfx.h"
#include "WatchMemory.h"

CWatchMemory::CWatchMemory(void)
{
}

CWatchMemory::~CWatchMemory(void)
{
}

int CWatchMemory::GetMemoryUsage( int *Usage ,int *Total )
{
	MEMORYSTATUS m_MemStat;
	GlobalMemoryStatus(&m_MemStat);	

	DWORD dwTotalMemory;
	DWORD dwAvailMemory;
	DWORD dwHasUse;
	//总的
	dwTotalMemory=m_MemStat.dwTotalPageFile;
	dwTotalMemory=dwTotalMemory/1024;
	dwTotalMemory=dwTotalMemory/1024;
	//可用
	dwAvailMemory=m_MemStat.dwAvailPageFile;
	dwAvailMemory=dwAvailMemory/1024;
	dwAvailMemory=dwAvailMemory/1024;
	//已经
	dwHasUse=dwTotalMemory-dwAvailMemory;

	*Usage = (int)dwHasUse;
	*Total = (int)dwTotalMemory;

	return 0;
}