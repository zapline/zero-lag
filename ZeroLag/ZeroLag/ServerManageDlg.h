#pragma once
#include "ServerManage.h"
#include "afxcmn.h"


// CServerManageDlg 对话框

class CServerManageDlg : public CDialog
{
	DECLARE_DYNAMIC(CServerManageDlg)

public:
	CServerManageDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CServerManageDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SERVERMANAGE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedServerFlush();

	CServerManage ServerManage;
public:
	CListCtrl m_ServerList;
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnServerStatus();
public:
	afx_msg void OnNMRclickListServer(NMHDR *pNMHDR, LRESULT *pResult);

private:
	BOOL m_ServerHide;
	afx_msg void OnBnClickedCheckServerhide();
};
