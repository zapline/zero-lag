#include "RightButtonUIHandler.h"	 
#include "stdafx.h"
#include "MainWnd.h"

void CRightButtonUIHandler::init(CMainWnd *p)
{
	pMain = p;
}



CRightButtonUIHandler::CRightButtonUIHandler(void)
{
	
}


CRightButtonUIHandler::~CRightButtonUIHandler(void)
{
}

void CRightButtonUIHandler::OnAddSysRecycle()
{
	CRightButton::AddSystemRecycle();
	MessageBox(0,"添加成功!","",MB_OK);
	
}

void CRightButtonUIHandler::OnDelSysRecycle()
{
	CRightButton::DelSystemRecycle();
	MessageBox(0,"删除成功!","",MB_OK);
}

void CRightButtonUIHandler::OnAddCutTo()
{
	CRightButton::AddSystemCutTo();
	MessageBox(0,"添加成功!","",MB_OK);
}

void CRightButtonUIHandler::OnDelCutTo()
{
	CRightButton::DelSystemCutTo();
	MessageBox(0,"删除成功!","",MB_OK);
}
