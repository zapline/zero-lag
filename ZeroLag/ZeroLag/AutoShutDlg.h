#pragma once
#include "afxwin.h"


// CAutoShutDlg 对话框

class CAutoShutDlg : public CDialog
{
	DECLARE_DYNAMIC(CAutoShutDlg)

public:
	CAutoShutDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAutoShutDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_AUTOSHUT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAutoshutSet();

private:
	int status;
	CButton m_ButtonSet;
	CTime m_ShutTime;
	BOOL AdjustToken();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
