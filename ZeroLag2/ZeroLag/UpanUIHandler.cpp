#include "UpanUIHandler.h"
#include "stdafx.h"
#include "MainWnd.h"

void CUpanUIHandler::init(CMainWnd *p)
{
	pMain = p;

	DWORD dwStyle = WS_CHILD|WS_VISIBLE|WS_VSCROLL|CBS_DROPDOWNLIST;
	m_DriveList.Create(  pMain->GetRichWnd(), CRect(60,165,260,305), NULL, dwStyle, 0, 7001);
	m_UpanList.Create( pMain->GetRichWnd(), NULL, NULL, dwStyle, 0, 7002);
}

CUpanUIHandler::CUpanUIHandler(void)
{
}


CUpanUIHandler::~CUpanUIHandler(void)
{
}

void CUpanUIHandler::OnCreateAutorun()
{
	int index = m_DriveList.GetCurSel();
	if (index == CB_ERR)
	{
		CKuiMsgBox::Show("请先选择盘符再点击设置按钮！");
	}
	else
	{
		CString name;
		m_DriveList.GetLBText(index, name);
		WCHAR ch = name.GetAt(0);
		char n = *(char *)&ch;
		Upan.StopAutorun(n);
		CKuiMsgBox::Show("免疫完成！");
	}
}

void CUpanUIHandler::OnKillHide()
{
	int index = m_UpanList.GetCurSel();
	if (index == CB_ERR)
	{
		CKuiMsgBox::Show("请先选择盘符再点击设置按钮！");
	}
	else
	{
		CString name;
		m_UpanList.GetLBText(index, name);
		WCHAR ch = name.GetAt(0);
		char n = *(char *)&ch;
		CKuiMsgBox::Show("接下来请耐心等候命令行窗口自动关闭！");
		Upan.KillHide(n);
		CKuiMsgBox::Show("设置完成！");
	}
}

LRESULT CUpanUIHandler::OnList1(DWORD whParam, DWORD wlParam, HWND lParam,BOOL bHandled)
{
	m_DriveList.ResetContent();
	CString temp;
	for (char ch='C';ch<='Z';ch++)
	{
		if (Upan.IsEnableDrive(ch) == TRUE)
		{
			temp.Format("%c:",ch);
			m_DriveList.AddString(temp);
		}
	}
	return TRUE;
}

LRESULT CUpanUIHandler::OnList2(DWORD whParam, DWORD wlParam, HWND lParam,BOOL bHandled)
{
	m_UpanList.ResetContent();
	CString temp;
	for (char ch='D';ch<='Z';ch++)
	{
		if (Upan.IsRemoveDrive(ch) == TRUE)
		{
			temp.Format("%c:",ch);
			m_UpanList.AddString(temp);
		}
	}
	return TRUE;
}