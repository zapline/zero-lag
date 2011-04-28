#pragma once


// CMemoryModifyDlg 对话框

class CMemoryModifyDlg : public CDialog
{
	DECLARE_DYNAMIC(CMemoryModifyDlg)

public:
	CMemoryModifyDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMemoryModifyDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_MEMORYMODIFY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DWORD HexToDword(CString hex);

	DECLARE_MESSAGE_MAP()
public:
	CString m_tName;
public:
	CString m_tAddr;
public:
	CString m_tNewHex;
public:
	afx_msg void OnBnClickedOk();
};
