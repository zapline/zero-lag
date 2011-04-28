#pragma once

#include "RunManageBase.h"

class CRunManage
{
public:
	CRunManage(void);
public:
	~CRunManage(void);

	void init();
public:
	CRunDirEnumer *DirEnumer;
	CRunRegEnumer *RegEnumer;
};
