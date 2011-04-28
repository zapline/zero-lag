#pragma once
#include "afxcmn.h"


// CProcessModuleDlg 对话框

class CProcessModuleDlg : public CDialog
{
	DECLARE_DYNAMIC(CProcessModuleDlg)

public:
	CProcessModuleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CProcessModuleDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PROCESS_MODULE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ProcessModuleList;
public:
	virtual BOOL OnInitDialog();
	int Init();
	int Pid;
};
