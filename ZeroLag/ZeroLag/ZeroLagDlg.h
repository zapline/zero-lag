// ZeroLagDlg.h : 头文件
//

#pragma once
#include "afxcmn.h"
#include "SignScanDlg.h"
#include "RunManageDlg.h"
#include "ProcessManageDlg.h"
#include "SystemInfoDlg.h"
#include "ServerManageDlg.h"
#include "UpanDialog.h"
#include "RightButtonDlg.h"

#include "WatchCpu.h"
#include "WatchMemory.h"

// CZeroLagDlg 对话框
class CZeroLagDlg : public CDialog
{
// 构造
public:
	CZeroLagDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_ZEROLAG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CSignScanDlg *m_pdSignScan;
	CRunManageDlg *m_pdRunManage;
	CProcessManageDlg *m_pdProcessManage;
	CSystemInfoDlg *m_pdSystemInfo;
	CServerManageDlg *m_pdServerManage;
	CUpanDialog *m_pdUpanManage;
	CRightButtonDlg *m_pdRightButton;

	typedef CDialog* PDIALOG;
	CArray<PDIALOG, PDIALOG> m_pPages;

	void TabCtrlSetShow(int i);
	void Init();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CTabCtrl m_tcMain;
	afx_msg void OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnMabout();
	afx_msg void OnMclose();
	afx_msg void OnMenuViewpeinfo();
	afx_msg void OnMemuMemorymodify();
	afx_msg void OnMemuFilemd5();
	afx_msg void OnMeneAutoshut();
	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CString m_CpuUsage;
	int CpuUsage;
	CWatchCpu WatchCpu;
	int MemoryUsage,MemoryTotal;
	CWatchMemory WatchMemory;
public:
	CString m_MemoryUsage;
};
