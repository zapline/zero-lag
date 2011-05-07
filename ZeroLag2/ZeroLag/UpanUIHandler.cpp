#include "UpanUIHandler.h"
#include "stdafx.h"
#include "MainWnd.h"

void CUpanUIHandler::init(CMainWnd *p)
{
	pMain = p;

	DWORD dwStyle = WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST;
	m_DriveList.Create( pMain->GetRichWnd(), NULL, NULL, dwStyle, 0, 7001 );
	m_UpanList.Create( pMain->GetRichWnd(), NULL, NULL, dwStyle, 0, 7002 );

// 	m_wndComboBox.InsertString(nIndex++,_T("≤‚ ‘œÓ0"));
// 	m_wndComboBox.SetCurSel(0);
	int nIndex = 0;
	m_DriveList.InsertString(nIndex, "111");
	m_UpanList.InsertString(nIndex++,"222");
	m_DriveList.InsertString(nIndex, "111");
	m_UpanList.InsertString(nIndex++,"222");
	m_DriveList.InsertString(nIndex, "111");
	m_UpanList.InsertString(nIndex++,"222");
}

CUpanUIHandler::CUpanUIHandler(void)
{
}


CUpanUIHandler::~CUpanUIHandler(void)
{
}
