#include "StdAfx.h"
#include "RunManage.h"

CRunManage::CRunManage(void)
{
	RegEnumer = new CRunRegEnumer();
	DirEnumer = new CRunDirEnumer();
}

CRunManage::~CRunManage(void)
{
	delete RegEnumer;
	delete DirEnumer;
}

void CRunManage::init()
{
	RegEnumer->DoEnum();
	DirEnumer->DoEnum();
}