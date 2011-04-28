#pragma once

class CWatchMemory
{
public:
	CWatchMemory(void);
public:
	~CWatchMemory(void);

	int GetMemoryUsage(int *Usage,int *Total);
};
