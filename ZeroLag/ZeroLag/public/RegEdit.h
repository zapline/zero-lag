#pragma once

class CRegEdit
{
public:
	CRegEdit(void);
public:
	~CRegEdit(void);

	static int SetValue_S (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,TCHAR *ReSetContent_S);
	static int SetValue_D (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,int ReSetContent_D[256]);
	static int SetValue_B (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName,BYTE ReSetContent_B[256]);
	static int DeleteKey (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReKeyName);
	static int DeleteValue (struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReValueName);
	static int CreateKey(struct HKEY__*ReRootKey,TCHAR *ReSubKey,TCHAR *ReKeyName);
};
