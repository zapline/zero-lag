#include "StdAfx.h"
#include "Upan.h"
#include <direct.h>

CUpan::CUpan(void)
{
}

CUpan::~CUpan(void)
{
}

BOOL CUpan::IsEnableDrive(char ch)
{
	CStringA dname;
	dname.Format("%c:",ch);
	UINT Type = GetDriveTypeA(dname);
	if (Type == DRIVE_REMOVABLE || Type == DRIVE_FIXED)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CUpan::IsRemoveDrive(char ch)
{
	CStringA dname;
	dname.Format("%c:",ch);
	UINT Type = GetDriveTypeA(dname);
	if (Type == DRIVE_REMOVABLE)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

int CUpan::StopAutorun(char ch)
{
	char str1[]="C:\\autorun.inf\\bat";
	char str2[]="C:\\autorun.inf\\ZeroLag..\\";
	char str3[]="mkdir C:\\autorun.inf\\bat";
	str1[0] = ch;
	str2[0] = ch;
	str3[6] = ch;
	system(str3);
	rename(str1,str2);
	return 0;
}

int CUpan::KillHide(char ch)
{
	char str[]="attrib a:\\*.* -S -H /S /D";
	str[7] = ch;
	system(str);
	return 0;
}