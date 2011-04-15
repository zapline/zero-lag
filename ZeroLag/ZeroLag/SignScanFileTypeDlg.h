#pragma once


// CSignScanFileTypeDlg 对话框

class CSignScanFileTypeDlg : public CDialog
{
	DECLARE_DYNAMIC(CSignScanFileTypeDlg)

public:
	CSignScanFileTypeDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSignScanFileTypeDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_SIGNSCAN_FILETYPE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int m_FileType;
public:
	BOOL m_HideHave;
};
