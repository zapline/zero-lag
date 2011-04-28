#pragma once

#include "PeInfo.h"
#include "afxcmn.h"
#include "afxwin.h"

// CPeInfoDlg 对话框

class CPeInfoDlg : public CDialog
{
	DECLARE_DYNAMIC(CPeInfoDlg)

public:
	CPeInfoDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPeInfoDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_PEINFO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

public:
	CPeInfo PeInfo;
	CString FileName,PathName;
public:
	virtual BOOL OnInitDialog();
public:
	CListCtrl m_SecList;
public:
	CString m_eFileSize;
public:
	CString m_eFileName;
};
