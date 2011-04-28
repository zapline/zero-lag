#pragma once


// CFileMd5Dlg 对话框

class CFileMd5Dlg : public CDialog
{
	DECLARE_DYNAMIC(CFileMd5Dlg)

public:
	CFileMd5Dlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CFileMd5Dlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_FILEMD5 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_PathName;
public:
	CString m_md5_16;
public:
	CString m_md5_32;
public:
	virtual BOOL OnInitDialog();
public:
	afx_msg void OnBnClickedFilemd516();
public:
	afx_msg void OnBnClickedFilemd532();
};
