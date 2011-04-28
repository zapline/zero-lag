#pragma once
#include "SystemInfo.h"


// CSystemInfoDlg 对话框

class CSystemInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CSystemInfoDlg)

public:
	CSystemInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSystemInfoDlg();

	CSystemInfo SystemInfo;

// 对话框数据
	enum { IDD = IDD_DIALOG_SYSTEMINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCpu();
};
