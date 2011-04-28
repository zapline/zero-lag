// ProcessModuleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZeroLag.h"
#include "ProcessModuleDlg.h"
#include "ProcessModule.h"


// CProcessModuleDlg 对话框

IMPLEMENT_DYNAMIC(CProcessModuleDlg, CDialog)

CProcessModuleDlg::CProcessModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessModuleDlg::IDD, pParent)
{

}

CProcessModuleDlg::~CProcessModuleDlg()
{
}

void CProcessModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROCESS_MODULE, m_ProcessModuleList);
}


BEGIN_MESSAGE_MAP(CProcessModuleDlg, CDialog)
END_MESSAGE_MAP()


// CProcessModuleDlg 消息处理程序

BOOL CProcessModuleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ProcessModuleList.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	m_ProcessModuleList.InsertColumn(0,L"模塊鏡像路徑",LVCFMT_LEFT,360);
	m_ProcessModuleList.InsertColumn(1,L"模塊鏡像基地址",LVCFMT_LEFT,120);

	Init();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

int CProcessModuleDlg::Init()
{
	CProcessModule::GetModule(Pid,&m_ProcessModuleList);
	return 0;
}