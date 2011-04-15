#pragma once
#include "SystemInfoCpu.h"

class CSystemInfo
{
public:
	CSystemInfo(void);
public:
	~CSystemInfo(void);

public:
	CSystemInfoCpu Cpu;
};
