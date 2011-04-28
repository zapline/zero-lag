#include "StdAfx.h"
#include "SignScan.h"
#include "Public/MicrosoftVerify.h"

CSignScan::CSignScan(void)
{
	InitFunc();
	HideHave = TRUE;
}

CSignScan::~CSignScan(void)
{
}

bool CSignScan::ProcessFile(const char *filename) 
{
	LPWSTR temp = new WCHAR[strlen(filename)+1];
	MByteToWChar(filename,temp,(DWORD)strlen(filename)+1);
	if (CheckFileTrust(temp) == TRUE && HideHave == FALSE)
	{
		pList->InsertItem(m_DisplayCount,"");
		pList->SetItemText(m_DisplayCount,0,filename);
		pList->EnsureVisible(m_DisplayCount, FALSE);
		pList->SetItemText(m_DisplayCount,1,"ÓÐ");
		m_DisplayCount++;
	}									
	else
	{	 
		pList->InsertItem(m_DisplayCount,"");
		pList->SetItemText(m_DisplayCount,0,filename);
		pList->EnsureVisible(m_DisplayCount, FALSE);
		pList->SetItemText(m_DisplayCount,1,"Ÿo");
		m_DisplayCount++;
	}
	m_nFileCount++;
	delete[] temp;
	return TRUE; 
} 

void CSignScan::ProcessDir(const char *currentdir,const char *parentdir)
{
	m_nSubdirCount++;
}

BOOL CSignScan::CheckFileTrust( LPCWSTR lpFileName )
{
	BOOL bRet = FALSE;
	WINTRUST_DATA wd = { 0 };
	WINTRUST_FILE_INFO wfi = { 0 };
	WINTRUST_CATALOG_INFO wci = { 0 };
	CATALOG_INFO ci = { 0 };

	HCATADMIN hCatAdmin = NULL;
	if ( !CryptCATAdminAcquireContext( &hCatAdmin, NULL, 0 ) )
	{
		return FALSE;
	}

	HANDLE hFile = CreateFileW( lpFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL );
	if ( INVALID_HANDLE_VALUE == hFile )
	{
		CryptCATAdminReleaseContext( hCatAdmin, 0 );
		return FALSE;
	}
	DWORD dwCnt = 100;
	BYTE byHash[100];
	CryptCATAdminCalcHashFromFileHandle( hFile, &dwCnt, byHash, 0 );
	CloseHandle( hFile );

	LPWSTR pszMemberTag = new WCHAR[dwCnt * 2 + 1];
	for ( DWORD dw = 0; dw < dwCnt; ++dw )
	{
		wsprintfW( &pszMemberTag[dw * 2], L"%02X", byHash[dw] );
	}

	HCATINFO hCatInfo = CryptCATAdminEnumCatalogFromHash( hCatAdmin, byHash, dwCnt, 0, NULL );
	if ( NULL == hCatInfo )
	{
		wfi.cbStruct= sizeof( WINTRUST_FILE_INFO );
		wfi.pcwszFilePath  = lpFileName;
		wfi.hFile   = NULL;
		wfi.pgKnownSubject = NULL;

		wd.cbStruct     = sizeof( WINTRUST_DATA );
		wd.dwUnionChoice= WTD_CHOICE_FILE;
		wd.pFile = &wfi;
		wd.dwUIChoice   = WTD_UI_NONE;
		wd.fdwRevocationChecks = WTD_REVOKE_NONE;
		wd.dwStateAction= WTD_STATEACTION_IGNORE;
		//wd.dwProvFlags  = WTD_SAFER_FLAG;
		//“þximoÕf£¬¿ÉÄÜŒ§ÖÂ¿¨ËÀ
		wd.dwProvFlags = 0;
		wd.hWVTStateData= NULL;
		wd.pwszURLReference    = NULL;
	}
	else      
	{
		CryptCATCatalogInfoFromContext( hCatInfo, &ci, 0 );
		wci.cbStruct      = sizeof( WINTRUST_CATALOG_INFO );
		wci.pcwszCatalogFilePath = ci.wszCatalogFile;
		wci.pcwszMemberFilePath  = lpFileName;
		wci.pcwszMemberTag= pszMemberTag;

		wd.cbStruct     = sizeof( WINTRUST_DATA );
		wd.dwUnionChoice= WTD_CHOICE_CATALOG;
		wd.pCatalog     = &wci;
		wd.dwUIChoice   = WTD_UI_NONE;
		wd.fdwRevocationChecks = WTD_STATEACTION_VERIFY;
		wd.dwProvFlags  = 0;
		wd.hWVTStateData= NULL;
		wd.pwszURLReference    = NULL;
	}
	GUID action = WINTRUST_ACTION_GENERIC_VERIFY_V2;
	HRESULT hr  = WinVerifyTrust( NULL, &action, &wd );
	bRet = SUCCEEDED( hr );

	if ( NULL != hCatInfo )
	{
		CryptCATAdminReleaseCatalogContext( hCatAdmin, hCatInfo, 0 );
	}
	CryptCATAdminReleaseContext( hCatAdmin, 0 );  
	delete[] pszMemberTag;
	return bRet;
}      
BOOL CSignScan::InitFunc()   
{   
	HMODULE dllHandle = NULL;   
	dllHandle = LoadLibrary("wintrust.dll");   
	if (NULL == dllHandle)   
	{   
		//printf("LoadLibrary wintrust.dll error!%d\n",GetLastError());   
		return FALSE;   
	}   
	(FARPROC &)CryptCATAdminAcquireContext =    
		GetProcAddress(dllHandle,"CryptCATAdminAcquireContext");   
	(FARPROC &)CryptCATAdminReleaseContext =   
		GetProcAddress(dllHandle,"CryptCATAdminReleaseContext");   
	(FARPROC &)CryptCATAdminCalcHashFromFileHandle =   
		GetProcAddress(dllHandle,"CryptCATAdminCalcHashFromFileHandle");   
	(FARPROC &)CryptCATAdminEnumCatalogFromHash =   
		GetProcAddress(dllHandle,"CryptCATAdminEnumCatalogFromHash");   
	(FARPROC &)CryptCATAdminReleaseCatalogContext =   
		GetProcAddress(dllHandle,"CryptCATAdminReleaseCatalogContext");   
	(FARPROC &)CryptCATCatalogInfoFromContext =    
		GetProcAddress(dllHandle,"CryptCATCatalogInfoFromContext");   
	(FARPROC &)WinVerifyTrust = GetProcAddress(dllHandle,"WinVerifyTrust");   
	if (CryptCATAdminAcquireContext == NULL   
		|| CryptCATAdminReleaseContext == NULL   
		|| CryptCATAdminCalcHashFromFileHandle == NULL   
		|| CryptCATAdminEnumCatalogFromHash == NULL   
		|| CryptCATAdminReleaseCatalogContext == NULL   
		|| CryptCATCatalogInfoFromContext == NULL    
		|| WinVerifyTrust == NULL)    
	{   
		//printf("GetProcAddress error 1%d\n",GetLastError());   
		return FALSE;   
	}   
	return TRUE;   
}