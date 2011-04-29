#include "StdAfx.h"
#include "RightButton.h"
#include "./public/RegEdit.h"

CRightButton::CRightButton(void)
{
}

CRightButton::~CRightButton(void)
{
}

int CRightButton::AddSystemRecycle()
{
	CRegEdit::CreateKey(HKEY_CLASSES_ROOT,_T("\\*\\shellex\\ContextMenuHandlers"),_T("{645FF040-5081-101B-9F08-00AA002F954E}"));
	return 0;
}

int CRightButton::DelSystemRecycle()
{
	CRegEdit::DeleteKey(HKEY_CLASSES_ROOT,_T("\\*\\shellex\\ContextMenuHandlers"),_T("{645FF040-5081-101B-9F08-00AA002F954E}"));
	return 0;
}

int CRightButton::AddSystemCutTo()
{
	CRegEdit::CreateKey(HKEY_CLASSES_ROOT,_T("\\AllFilesystemObjects\\shellex\\ContextMenuHandlers"),_T("Cut To"));
	TCHAR Str[] = _T("{C2FBB631-2971-11D1-A18C-00C04FD75D13}");
	CRegEdit::SetValue_S(HKEY_CLASSES_ROOT,_T("\\AllFilesystemObjects\\shellex\\ContextMenuHandlers\\Cut To"),_T(""),Str);
	return 0;
}

int CRightButton::DelSystemCutTo()
{
	CRegEdit::DeleteKey(HKEY_CLASSES_ROOT,_T("\\AllFilesystemObjects\\shellex\\ContextMenuHandlers"),_T("Cut To"));
	return 0;
}