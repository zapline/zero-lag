#include "StdAfx.h"
#include "PeInfo.h"

CPeInfo::CPeInfo(void)
{
}

CPeInfo::~CPeInfo(void)
{
	UnmapViewOfFile(lpFile);  
	CloseHandle(hMap);  
	CloseHandle(hFile);
}

void CPeInfo::zInit(CString FileName)
{
	m_FileName = FileName;

	hFile = CreateFile(m_FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(0,L"打開文件出錯！",L"",0);
		return;
	}
	m_FileSize = GetFileSize(hFile, 0);
	hMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 0, NULL);
	if (hMap == 0)
	{
		MessageBox(0,L"映射文件出錯！",L"",0);
		CloseHandle(hFile);
		return;
	}
	lpFile = MapViewOfFile(hMap, FILE_MAP_READ, 0, 0, 0);

	pDosHeader = (PIMAGE_DOS_HEADER)lpFile;

	pNtHeader = (PIMAGE_NT_HEADERS)((DWORD)pDosHeader->e_lfanew + (DWORD)lpFile);

	SectionNum = pNtHeader->FileHeader.NumberOfSections;

	pSecHeader = (PIMAGE_SECTION_HEADER)((DWORD)pNtHeader + (DWORD)pNtHeader->FileHeader.SizeOfOptionalHeader + (DWORD)sizeof(IMAGE_FILE_HEADER) + (DWORD)sizeof(DWORD));
}