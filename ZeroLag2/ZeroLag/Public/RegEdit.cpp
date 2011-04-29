#include ".\..\StdAfx.h"
#include "RegEdit.h"

CRegEdit::CRegEdit(void)
{
}

CRegEdit::~CRegEdit(void)
{
}

//设置字符串值函数
int CRegEdit::SetValue_S (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,TCHAR *ReSetContent_S)
{
	HKEY hKey;
	int i=0;	//操作结果：0==succeed

	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		//!!!!!這裡長度可能還存在問題!!!!!
		if(RegSetValueEx(hKey,ReValueName,NULL,REG_SZ,(BYTE *)ReSetContent_S,CString(ReSetContent_S).GetLength()*2)!=ERROR_SUCCESS)
		{
			//MessageBox("错误：无法设置有关的注册表信息");
			i=1;
		}
		RegCloseKey(hKey);
	}
	else
	{
		//MessageBox("错误：无法查询有关的注册表信息");
		i=2;
	}
	return i;
}

//设置DWORD值函数
int CRegEdit::SetValue_D (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,int ReSetContent_D[256])
{
	HKEY hKey;
	int i=0;	//操作结果：0==succeed
	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,ReValueName,NULL,REG_DWORD,(const unsigned char *)ReSetContent_D,4)!=ERROR_SUCCESS)
		{
			//MessageBox("错误：无法设置有关的注册表信息");
			i=1;
		}
		RegCloseKey(hKey);
	}
	else
	{
		//MessageBox("错误：无法查询有关的注册表信息");
		i=2;
	}
	return i;
}

//设置二进制值函数
int CRegEdit::SetValue_B (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,BYTE ReSetContent_B[256])
{
	HKEY hKey;
	int i=0;	//操作结果：0==succeed
	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,ReValueName,NULL,REG_BINARY,(const unsigned char *)ReSetContent_B,4)!=ERROR_SUCCESS)
		{
			//MessageBox("错误：无法设置有关的注册表信息");
			i=1;
		}
		RegCloseKey(hKey);
	}
	else
	{
		//MessageBox("错误：无法查询有关的注册表信息");
		i=2;
	}
	return i;
}

//删除子项函数
int CRegEdit::DeleteKey (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReKeyName)
{
	HKEY hKey;
	int i=0;	//操作结果：0==succeed
	if((RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey))==ERROR_SUCCESS)
	{
		if((RegDeleteKey(hKey,ReKeyName))!=ERROR_SUCCESS)
		{
			//MessageBox("清除指定项失败！");
			i=1;
		}
		RegCloseKey(hKey);
	}
	else
	{
		//MessageBox("错误：无法打开有关的hKEY");
		i=2;
	}
	return i;
}

//删除键值函数
int CRegEdit::DeleteValue (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName)
{
	HKEY hKey;
	int i=0;	//操作结果：0==succeed
	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegDeleteValue(hKey,ReValueName)!=ERROR_SUCCESS)
		{
			//MessageBox("清除指定值失败！");
			i=1;
		}
		RegCloseKey(hKey);
	}
	else
	{
		//MessageBox("错误：无法打开有关的hKEY");
		i=2;
	}
	return i;
}

//創建新的註冊表鍵
int CRegEdit::CreateKey(struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReKeyName)
{
	HKEY hKey,hSubKey;
	DWORD dwDisp;
	int i=0;
	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		
		if (RegCreateKeyEx(hKey,ReKeyName,0,NULL,REG_OPTION_NON_VOLATILE,
			KEY_ALL_ACCESS, NULL, &hSubKey, &dwDisp) == ERROR_SUCCESS)
		{
			RegCloseKey(hSubKey);
		}
		else
		{
			i=1;
		}
		RegCloseKey(hKey);
	}
	else
	{
		i=2;
	}
	return i;
}
