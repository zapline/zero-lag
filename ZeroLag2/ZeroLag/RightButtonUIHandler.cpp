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
	MessageBox(0,"��ӳɹ�!","",MB_OK);
	
}

void CRightButtonUIHandler::OnDelSysRecycle()
{
	CRightButton::DelSystemRecycle();
	MessageBox(0,"ɾ���ɹ�!","",MB_OK);
}

void CRightButtonUIHandler::OnAddCutTo()
{
	CRightButton::AddSystemCutTo();
	MessageBox(0,"��ӳɹ�!","",MB_OK);
}

void CRightButtonUIHandler::OnDelCutTo()
{
	CRightButton::DelSystemCutTo();
	MessageBox(0,"ɾ���ɹ�!","",MB_OK);
}
