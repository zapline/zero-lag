#pragma once

class CSystemInfoCpu
{
public:
	int GetTypeName(char *type);
	int GetName(char *name);
	int GetFamily();
	bool withMMX();
	bool hasFPU();
	DWORD GetSpeed();
	CSystemInfoCpu();
	~CSystemInfoCpu();

private:
	bool FPU;
	char *Name;
	bool MMX;
	int iFamily;
};
