#pragma once
#include "afxcmn.h"
#include "SignScan.h"
#include "SignScanFileTypeDlg.h"
#include "afxwin.h"


// CSignScanDlg 对话框

class CSignScanDlg : public CDialog
{
	DECLARE_DYNAMIC(CSignScanDlg)

public:
	CSignScanDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSignScanDlg();

	friend void SignScanThread(LPVOID param);

// 对话框数据
	enum { IDD = IDD_DIALOG_SIGNSCAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	CString GetDirector(CString title);
	CString GetFilenameInPathname(CString pathname);
	
	CSignScan scan;
	HANDLE hThread;
	int ThreadStatus;
	int FileType;
	BOOL HideHave;

	DECLARE_MESSAGE_MAP()
public:
	CString m_path;
public:
	afx_msg void OnBnClickedButtonSignscanmenu();
public:
	afx_msg void OnBnClickedButtonSignscanbegin();
public:
	CListCtrl m_lcScan;
public:
	virtual BOOL OnInitDialog();
public:
	CButton m_bbegin;
public:
	CButton m_bp;
public:
	CButton m_bend;
public:
	afx_msg void OnBnClickedButtonSignscanp();
public:
	afx_msg void OnBnClickedButtonSignscanend();
public:
	afx_msg void OnBnClickedButtonSignscanfiletype();
public:
	afx_msg void OnMsignscanGoto();
public:
	afx_msg void OnMsignscanBaidu();
public:
	afx_msg void OnMsignscanPeinfo();
public:
	afx_msg void OnNMRclickListSignsang(NMHDR *pNMHDR, LRESULT *pResult);
public:
	afx_msg void OnMsignscanFilemd5();
};
