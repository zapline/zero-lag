// ZeroLagDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ZeroLag.h"
#include "ZeroLagDlg.h"
#include "AboutDlg.h"
#include "PeInfoDlg.h"
#include "MemoryModifyDlg.h"
#include "FileMd5Dlg.h"
#include "AutoShutDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CZeroLagDlg 对话框




CZeroLagDlg::CZeroLagDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZeroLagDlg::IDD, pParent)
	, m_CpuUsage(_T(""))
	, m_MemoryUsage(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CZeroLagDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB_MAIN, m_tcMain);
	DDX_Text(pDX, IDC_STATIC_CPUUSAGE, m_CpuUsage);
	DDX_Text(pDX, IDC_STATIC_MEMORYUSAGE, m_MemoryUsage);
}

BEGIN_MESSAGE_MAP(CZeroLagDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB_MAIN, &CZeroLagDlg::OnTcnSelchangeTabMain)
	ON_COMMAND(ID_MABOUT, &CZeroLagDlg::OnMabout)
	ON_COMMAND(ID_MCLOSE, &CZeroLagDlg::OnMclose)
	ON_COMMAND(ID_MENU_VIEWPEINFO, &CZeroLagDlg::OnMenuViewpeinfo)
	ON_COMMAND(ID_MEMU_MEMORYMODIFY, &CZeroLagDlg::OnMemuMemorymodify)
	ON_COMMAND(ID_MEMU_FILEMD5, &CZeroLagDlg::OnMemuFilemd5)
	ON_COMMAND(ID_MENE_AUTOSHUT, &CZeroLagDlg::OnMeneAutoshut)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CZeroLagDlg 消息处理程序

BOOL CZeroLagDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	
	//監視CPU使用率和內存使用率
	SetTimer(1,1000,NULL);

	Init();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CZeroLagDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CZeroLagDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CZeroLagDlg::OnTcnSelchangeTabMain(NMHDR *pNMHDR, LRESULT *pResult)
{
/*	switch (m_tcMain.GetCurSel())
	{
	case 0:
		m_pdSignScan->ShowWindow(SW_SHOW);
		m_pdRunManage->ShowWindow(SW_HIDE);
		m_pdProcessManage->ShowWindow(SW_HIDE);
		break;
	case 1:
		m_pdSignScan->ShowWindow(SW_HIDE);
		m_pdRunManage->ShowWindow(SW_SHOW);
		m_pdProcessManage->ShowWindow(SW_HIDE);
		break;
	case 2:
		m_pdSignScan->ShowWindow(SW_HIDE);
		m_pdRunManage->ShowWindow(SW_HIDE);
		m_pdProcessManage->ShowWindow(SW_SHOW);
		break;
		
	default:
		break;
	}
*/

	TabCtrlSetShow(m_tcMain.GetCurSel());

	*pResult = 0;
}

void CZeroLagDlg::Init()
{
	m_tcMain.InsertItem(0,L"數字簽名掃描");
	m_tcMain.InsertItem(1,L"啟動項管理");
	m_tcMain.InsertItem(2,L"進程管理");
	m_tcMain.InsertItem(3,L"計算機信息");
	m_tcMain.InsertItem(4,L"服務管理");
	m_tcMain.InsertItem(5,L"U盤維護");
	m_tcMain.InsertItem(6,L"右鍵菜單管理");
	m_pdSignScan = new CSignScanDlg();
	m_pdRunManage = new CRunManageDlg();
	m_pdProcessManage = new CProcessManageDlg();
	m_pdSystemInfo = new CSystemInfoDlg();
	m_pdServerManage = new CServerManageDlg();
	m_pdUpanManage = new CUpanDialog();
	m_pdRightButton = new CRightButtonDlg();
	m_pdSignScan->Create(IDD_DIALOG_SIGNSCAN,&m_tcMain);
	m_pdRunManage->Create(IDD_DIALOG_RUNMANAGE,&m_tcMain);
	m_pdProcessManage->Create(IDD_DIALOG_PROCESSMANAGE,&m_tcMain);
	m_pdSystemInfo->Create(IDD_DIALOG_SYSTEMINFO,&m_tcMain);
	m_pdServerManage->Create(IDD_DIALOG_SERVERMANAGE,&m_tcMain);
	m_pdUpanManage->Create(IDD_DIALOG_UPAN,&m_tcMain);
	m_pdRightButton->Create(IDD_DIALOG_RIGHTBUTTON,&m_tcMain);
// 	m_pdSignScan->CenterWindow();
// 	m_pdRunManage->CenterWindow();
// 	m_pdProcessManage->CenterWindow();
// 	m_pdSignScan->ShowWindow(SW_SHOW);
// 	m_pdRunManage->ShowWindow(SW_HIDE);
// 	m_pdProcessManage->ShowWindow(SW_HIDE);
	m_pPages.Add(m_pdSignScan);
	m_pPages.Add(m_pdRunManage);
	m_pPages.Add(m_pdProcessManage);
	m_pPages.Add(m_pdSystemInfo);
	m_pPages.Add(m_pdServerManage);
	m_pPages.Add(m_pdUpanManage);
	m_pPages.Add(m_pdRightButton);
	for (int i=0;i<m_pPages.GetCount();i++)
	{
		m_pPages[i]->CenterWindow();
	}
	TabCtrlSetShow(0);
}
void CZeroLagDlg::OnMabout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

void CZeroLagDlg::OnMclose()
{
	for (int i=0;i<m_pPages.GetCount();i++)
	{
		m_pPages[i]->DestroyWindow();
		delete m_pPages[i];
	}
// 	m_pdRunManage->DestroyWindow();
// 	m_pdSignScan->DestroyWindow();
// 	m_pdProcessManage->DestroyWindow();
// 	delete m_pdSignScan;
// 	delete m_pdRunManage;
// 	delete m_pdProcessManage;
	CZeroLagDlg::OnOK();
}

void CZeroLagDlg::OnMenuViewpeinfo()
{
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		CPeInfoDlg PeDlg;
		PeDlg.FileName = dlg.GetFileName();
		PeDlg.PathName = dlg.GetPathName();
		PeDlg.DoModal();
	}
}

void CZeroLagDlg::OnMemuMemorymodify()
{
	CMemoryModifyDlg dlg;
	dlg.DoModal();
}

void CZeroLagDlg::OnMemuFilemd5()
{
	CFileDialog dlg(TRUE);
	if (dlg.DoModal() == IDOK)
	{
		CFileMd5Dlg PeDlg;
		PeDlg.m_PathName = dlg.GetPathName();
		PeDlg.DoModal();
	}
}

void CZeroLagDlg::TabCtrlSetShow(int i)
{
	for (int n=0;n<m_pPages.GetCount();n++)
	{
		m_pPages[n]->ShowWindow(SW_HIDE);
	}
	m_pPages[i]->ShowWindow(SW_SHOW);
}
void CZeroLagDlg::OnMeneAutoshut()
{
	CAutoShutDlg *dlg = new CAutoShutDlg();
	dlg->Create(IDD_DIALOG_AUTOSHUT);
	dlg->ShowWindow(SW_SHOW);
}

void CZeroLagDlg::OnTimer(UINT_PTR nIDEvent)
{
	//監視CPU和內存使用率
	if (nIDEvent == 1)
	{
		if (WatchCpu.GetCpuUsage(&CpuUsage) == 0)
		{
			m_CpuUsage.Format(L"CPU使用率：%2d%c",CpuUsage,'%');
		}
		else
		{
			//獲取失敗則直接顯示50%
			m_CpuUsage.Format(L"CPU使用率：%2d%c",50,'%');
			
		}
		WatchMemory.GetMemoryUsage(&MemoryUsage,&MemoryTotal);
		m_MemoryUsage.Format(L"Memory使用率：%4dM/%4dM",MemoryUsage,MemoryTotal);
		UpdateData(FALSE);
	}

	CDialog::OnTimer(nIDEvent);
}
