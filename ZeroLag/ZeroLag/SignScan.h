#pragma once
#include ".\public\browsedir.h"

class CSignScan :
	public CBrowseDir
{
public:
	CSignScan(void);
public:
	~CSignScan(void);

	//返回子目录个数 
	int GetSubdirCount() 
	{ 
		return m_nSubdirCount; 
	}
	//返回文件个数 
	int GetFileCount() 
	{ 
		return m_nFileCount; 
	}

	void SetSubdirCount(int n) 
	{ 
		m_nSubdirCount = n; 
	}
	void SetFileCount(int n) 
	{ 
		m_nFileCount = n; 
		m_DisplayCount = n;
	}

	CListCtrl *pList;
	BOOL HideHave;

protected:
	int m_nFileCount; //保存文件个数
	int m_nSubdirCount; //保存子目录个数
	int m_DisplayCount; //顯示文件個數

	virtual bool ProcessFile(const char *filename);

	virtual void ProcessDir(const char *currentdir,const char *parentdir);

	BOOL InitFunc();
	BOOL CheckFileTrust( LPCWSTR lpFileName );
};
