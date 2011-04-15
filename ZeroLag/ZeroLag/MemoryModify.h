#pragma once

class CMemoryModify
{
public:
	CMemoryModify(void);
public:
	~CMemoryModify(void);

public:
	CString Name;
	void Init();
	BOOL zWriteMemory(DWORD addr, DWORD data);
};
