#include "RunManageUIHandler.h"				  
#include "stdafx.h"
#include "MainWnd.h"

void CRunManageUIHandler::init(CMainWnd *p)
{
	pMain = p;

	if( !RunTree.Create( pMain->GetViewHWND(), 3001 ) )
	{
		CKuiMsgBox::Show( _T("无法初始化树控件") );
	}
	else
	{
		HTREEITEM hItem = RunTree.InsertItem( _T("注册表启动项"), NULL, NULL, KUIMulStatusTree::EM_TVIS_CHECK );
		RunTree.InsertItem( _T("下属项目1"), hItem, NULL, KUIMulStatusTree::EM_TVIS_CHECK );
		RunTree.InsertItem( _T("下属项目2"), hItem, NULL, KUIMulStatusTree::EM_TVIS_CHECK );
		RunTree.InsertItem( _T("下属项目3"), hItem, NULL, KUIMulStatusTree::EM_TVIS_CHECK );
		RunTree.InsertItem( _T("下属项目4"), hItem, NULL, KUIMulStatusTree::EM_TVIS_CHECK );
		RunTree.InsertItem( _T("下属项目5"), hItem, NULL, KUIMulStatusTree::EM_TVIS_CHECK );

		hItem = RunTree.InsertItem( _T("目录启动项"), NULL, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		RunTree.InsertItem( _T("下属项目1"), hItem, NULL, KUIMulStatusTree::EM_TVIS_CHECK );
		RunTree.InsertItem( _T("下属项目2"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		RunTree.InsertItem( _T("下属项目3"), hItem, NULL, KUIMulStatusTree::EM_TVIS_CHECK );
		RunTree.InsertItem( _T("下属项目4"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		RunTree.InsertItem( _T("下属项目5"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );

		hItem = RunTree.InsertItem( _T("服务启动项"), NULL, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		RunTree.InsertItem( _T("下属项目1"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		RunTree.InsertItem( _T("下属项目2"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		RunTree.InsertItem( _T("下属项目3"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		RunTree.InsertItem( _T("下属项目4"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
		RunTree.InsertItem( _T("下属项目5"), hItem, NULL, KUIMulStatusTree::EM_TVIS_UNCHECK );
	}
}



CRunManageUIHandler::CRunManageUIHandler(void)
{
}


CRunManageUIHandler::~CRunManageUIHandler(void)
{
}
