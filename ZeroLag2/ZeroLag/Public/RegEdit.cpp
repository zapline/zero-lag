#include ".\..\StdAfx.h"
#include "RegEdit.h"

CRegEdit::CRegEdit(void)
{
}

CRegEdit::~CRegEdit(void)
{
}

//�����ַ���ֵ����
int CRegEdit::SetValue_S (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,TCHAR *ReSetContent_S)
{
	HKEY hKey;
	int i=0;	//���������0==succeed

	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		//!!!!!�@�e�L�ȿ���߀���چ��}!!!!!
		if(RegSetValueEx(hKey,ReValueName,NULL,REG_SZ,(BYTE *)ReSetContent_S,CString(ReSetContent_S).GetLength()*2)!=ERROR_SUCCESS)
		{
			//MessageBox("�����޷������йص�ע�����Ϣ");
			i=1;
		}
		RegCloseKey(hKey);
	}
	else
	{
		//MessageBox("�����޷���ѯ�йص�ע�����Ϣ");
		i=2;
	}
	return i;
}

//����DWORDֵ����
int CRegEdit::SetValue_D (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,int ReSetContent_D[256])
{
	HKEY hKey;
	int i=0;	//���������0==succeed
	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,ReValueName,NULL,REG_DWORD,(const unsigned char *)ReSetContent_D,4)!=ERROR_SUCCESS)
		{
			//MessageBox("�����޷������йص�ע�����Ϣ");
			i=1;
		}
		RegCloseKey(hKey);
	}
	else
	{
		//MessageBox("�����޷���ѯ�йص�ע�����Ϣ");
		i=2;
	}
	return i;
}

//���ö�����ֵ����
int CRegEdit::SetValue_B (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,BYTE ReSetContent_B[256])
{
	HKEY hKey;
	int i=0;	//���������0==succeed
	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegSetValueEx(hKey,ReValueName,NULL,REG_BINARY,(const unsigned char *)ReSetContent_B,4)!=ERROR_SUCCESS)
		{
			//MessageBox("�����޷������йص�ע�����Ϣ");
			i=1;
		}
		RegCloseKey(hKey);
	}
	else
	{
		//MessageBox("�����޷���ѯ�йص�ע�����Ϣ");
		i=2;
	}
	return i;
}

//ɾ�������
int CRegEdit::DeleteKey (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReKeyName)
{
	HKEY hKey;
	int i=0;	//���������0==succeed
	if((RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey))==ERROR_SUCCESS)
	{
		if((RegDeleteKey(hKey,ReKeyName))!=ERROR_SUCCESS)
		{
			//MessageBox("���ָ����ʧ�ܣ�");
			i=1;
		}
		RegCloseKey(hKey);
	}
	else
	{
		//MessageBox("�����޷����йص�hKEY");
		i=2;
	}
	return i;
}

//ɾ����ֵ����
int CRegEdit::DeleteValue (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName)
{
	HKEY hKey;
	int i=0;	//���������0==succeed
	if(RegOpenKeyEx(ReRootKey,ReSubKey,0,KEY_WRITE,&hKey)==ERROR_SUCCESS)
	{
		if(RegDeleteValue(hKey,ReValueName)!=ERROR_SUCCESS)
		{
			//MessageBox("���ָ��ֵʧ�ܣ�");
			i=1;
		}
		RegCloseKey(hKey);
	}
	else
	{
		//MessageBox("�����޷����йص�hKEY");
		i=2;
	}
	return i;
}

//�����µ��]�Ա��I
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
