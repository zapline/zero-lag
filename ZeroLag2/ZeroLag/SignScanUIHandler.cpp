#include "SignScanUIHandler.h"
#include "stdafx.h"
#include "MainWnd.h"
#include "SignScanOptionDlg.h"

CSignScanUIHandler::CSignScanUIHandler(void)
{
}


CSignScanUIHandler::~CSignScanUIHandler(void)
{
}

void CSignScanUIHandler::init(CMainWnd *p)
{
	pMain = p;
	SignScanPath = L"c:\\windows\\system32\\";

	DWORD dwStyle = WS_CHILD|LVS_REPORT|LVS_SHOWSELALWAYS|LVS_SINGLESEL|LVS_OWNERDRAWFIXED;

	if( SignScanListCtrl.Create( pMain->GetRichWnd(),  NULL, NULL, dwStyle, 0, 1001 ) )
	{
		if( SignScanPathEdit.Create( pMain->GetRichWnd(), NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER , 0, 1002 ) )
		{
			SignScanPathEdit.SetDlgCtrlID( 1002 );
			SignScanPathEdit.SetWindowText(SignScanPath);
		}

		DWORD dwExStyle = LVS_EX_FULLROWSELECT;
		dwExStyle |= SignScanListCtrl.GetExtendedListViewStyle();
		SignScanListCtrl.SetExtendedListViewStyle(dwExStyle);

		SignScanListCtrl.InsertColumn( 0, _T("�ļ���"), LVCFMT_LEFT, 500);
		SignScanListCtrl.InsertColumn( 1, _T("����ǩ��"), LVCFMT_LEFT, 100);

		SignScanListCtrl.Init();

		pMain->SetItemVisible(1103,FALSE);
		pMain->SetItemVisible(1104,FALSE);
		SignScanThreadStatus = 0;

		SignScanFileType = 0;
		SignScanHideHave = FALSE;
	}
}

CString CSignScanUIHandler::GetDirector(CString title)
{
	ITEMIDLIST *ppidl; 
	SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP ,&ppidl); 
	if ( ppidl == NULL) 
	{ 
		pMain->MessageBox(_T("����·�����ʧ��") ) ; 
		return _T("error"); 
	} 
	TCHAR path[255] = _T(""); 
	BROWSEINFO *bi=new BROWSEINFO; 
	bi->hwndOwner=NULL; 
	bi->pidlRoot=ppidl; 
	bi->pszDisplayName=NULL; 
	bi->lpszTitle=title; 
	bi->lpfn=NULL; 
	bi->ulFlags=/*BIF_BROWSEINCLUDEFILES|*/BIF_EDITBOX |BIF_RETURNONLYFSDIRS ; 
	ppidl = SHBrowseForFolder(bi); 
	if ( !SHGetPathFromIDList(ppidl,path) ) 
	{ 
		delete bi; 
		return _T("error") ; 
	} 
	delete bi; 
	CString s = path ; 
	if ( s.Right( 1 ) != _T("\\") ) 
		s+= _T("\\") ; 
	return s ;
}

void CSignScanUIHandler::OnSignScanChoicePath()
{
	SignScanPathEdit.SetWindowTextA(GetDirector( "ѡ��ɨ��Ŀ¼"));
}

void CSignScanUIHandler::OnSignScanBegin()
{
	SignScanListCtrl.DeleteAllItems();
	SignScanPathEdit.GetWindowTextA(SignScanPath);

	//��ֹ�� \ �Yβ��Ŀ������ж���oЧ
	if (SignScanPath.GetAt(SignScanPath.GetLength()-1) == '\\')
	{
		SignScanPath.Delete(SignScanPath.GetLength()-1);
	}

	//���ֺ�������Ŀ���Ч���Д�
	WIN32_FIND_DATA wfd;
	bool rValue = false;
	HANDLE hFind = FindFirstFile(SignScanPath, &wfd);
	if ((hFind != INVALID_HANDLE_VALUE) && (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		FindClose(hFind);
	}
	else
	{
		pMain->MessageBox("Ŀ¼��Ч��");
		return;
	}
	SignScan.SetInitDir(SignScanPath);

	pMain->SetItemVisible(1102,FALSE);
	pMain->SetItemVisible(1103,TRUE);
	pMain->SetItemVisible(1104,TRUE);

	SignScanThreadStatus = 1;

	SignScan.pList = &SignScanListCtrl;

	SignScanhThread = CreateThread(0,0,(LPTHREAD_START_ROUTINE)SignScanThread,this,0,0);
}

void CSignScanUIHandler::OnSignScanPause()
{
	if (SignScanThreadStatus == 1)
	{
		SignScanThreadStatus = 2;
		SuspendThread(SignScanhThread);
		pMain->SetItemText(1103, "����ɨ��" );
	} 
	else if (SignScanThreadStatus == 2)
	{
		SignScanThreadStatus = 1;
		ResumeThread(SignScanhThread);
		pMain->SetItemText(1103, "��ͣɨ��" );
	}

}

void CSignScanUIHandler::OnSignScanEnd()
{
	SignScanThreadStatus = 0;
	TerminateThread(SignScanhThread,0);
	CloseHandle(SignScanhThread);
	pMain->SetItemText(1103, "��ͣɨ��" );
	pMain->SetItemVisible(1102,TRUE);
	pMain->SetItemVisible(1103,FALSE);
	pMain->SetItemVisible(1104,FALSE);
}

void CSignScanUIHandler::OnSignScanOption()
{
	CSignScanOptionDlg dlg(SignScanHideHave,SignScanFileType);
	if (dlg.DoModal() == IDOK)
	{
		SignScanFileType = dlg.SignScanFileType;
		SignScanHideHave = dlg.SignScanHideHave;
	}
}

void SignScanThread( LPVOID param )
{
	CSignScanUIHandler *p = (CSignScanUIHandler *)param;

	p->SignScan.SetFileCount(0);
	p->SignScan.SetSubdirCount(0);

	p->SignScan.HideHave = p->SignScanHideHave;
	switch (p->SignScanFileType)
	{
	case 0:
		p->SignScan.BeginBrowse("*.exe");
		break;
	case 1:
		p->SignScan.BeginBrowse("*.*");
		break;
	default:
		p->pMain->MessageBox( "ɨ���ļ����ʹ���" );
	}

	CString temp;
	temp.Format( "��ɨ�� %d ��Ŀ¼��%d ���ļ���", p->SignScan.GetSubdirCount(), p->SignScan.GetFileCount());
	p->pMain->MessageBox(temp);

	CloseHandle(p->SignScanhThread);

	p->SignScanThreadStatus = 0;

	p->pMain->SetItemText(1103, "��ͣɨ��" );
	p->pMain->SetItemVisible(1102,TRUE);
	p->pMain->SetItemVisible(1103,FALSE);
	p->pMain->SetItemVisible(1104,FALSE);

	ExitThread(0);
}