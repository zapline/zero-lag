#pragma once

class CPeInfo
{
public:
	CPeInfo(void);
public:
	~CPeInfo(void);

public:
	CString m_FileName;	

	void zInit(CString FileName);

	DWORD zGetFileSize()
	{
		return m_FileSize;
	}

	PIMAGE_DOS_HEADER zGetDosHeader()
	{
		return pDosHeader;
	}

	PIMAGE_NT_HEADERS zGetNtHeader()
	{
		return pNtHeader;
	}

	int zGetSecNum()
	{
		return SectionNum;
	}
	
	PIMAGE_SECTION_HEADER zGetSecHeader(int num)
	{
		return (PIMAGE_SECTION_HEADER)&(pSecHeader[num]);
	}

private:
	DWORD m_FileSize;
	LPVOID lpFile;
	HANDLE hFile,hMap;

	PIMAGE_DOS_HEADER pDosHeader;
	PIMAGE_NT_HEADERS pNtHeader;
	int SectionNum;
	PIMAGE_SECTION_HEADER pSecHeader;
};
