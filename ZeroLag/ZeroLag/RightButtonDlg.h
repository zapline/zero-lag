#pragma once

#include "RightButton.h"

// CRightButtonDlg 对话框

class CRightButtonDlg : public CDialog
{
	DECLARE_DYNAMIC(CRightButtonDlg)

public:
	CRightButtonDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRightButtonDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_RIGHTBUTTON };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	CRightButton RightButton;

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRightRecycle();
public:
	afx_msg void OnBnClickedRightRecycle2();
public:
	afx_msg void OnBnClickedRightMoveto();
public:
	afx_msg void OnBnClickedRightMoveto2();
};
