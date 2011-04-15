#ifndef _MICROSOFTVERIFY_H_ 
#define _MICROSOFTVERIFY_H_ 

#include "windows.h" 
typedef struct WINTRUST_FILE_INFO_ 
{ 
	DWORD   cbStruct; 
	LPCWSTR pcwszFilePath; 
	HANDLE  hFile; 
	GUID*   pgKnownSubject; 
} WINTRUST_FILE_INFO, *PWINTRUST_FILE_INFO; 

// typedef struct _CRYPTOAPI_BLOB { 
// 	DWORD   cbData; 
// 	BYTE    *pbData; 
// } CRYPT_INTEGER_BLOB, *PCRYPT_INTEGER_BLOB, 
// CRYPT_UINT_BLOB, *PCRYPT_UINT_BLOB, 
// CRYPT_OBJID_BLOB, *PCRYPT_OBJID_BLOB, 
// CERT_NAME_BLOB, *PCERT_NAME_BLOB, 
// CERT_RDN_VALUE_BLOB, *PCERT_RDN_VALUE_BLOB, 
// CERT_BLOB, *PCERT_BLOB, 
// CRL_BLOB, *PCRL_BLOB, 
// DATA_BLOB, *PDATA_BLOB,     // JEFFJEFF temporary (too generic) 
// CRYPT_DATA_BLOB, *PCRYPT_DATA_BLOB, 
// CRYPT_HASH_BLOB, *PCRYPT_HASH_BLOB, 
// CRYPT_DIGEST_BLOB, *PCRYPT_DIGEST_BLOB, 
// CRYPT_DER_BLOB, *PCRYPT_DER_BLOB, 
// CRYPT_ATTR_BLOB, *PCRYPT_ATTR_BLOB; 

// typedef struct _CTL_USAGE { 
// 	DWORD cUsageIdentifier; 
// 	LPSTR *rgpszUsageIdentifier;      // array of pszObjId 
// } CTL_USAGE, *PCTL_USAGE, 
// CERT_ENHKEY_USAGE, *PCERT_ENHKEY_USAGE; 
// typedef struct _CRYPT_ALGORITHM_IDENTIFIER { 
// 	LPSTR pszObjId; 
// 	CRYPT_OBJID_BLOB    Parameters; 
// } CRYPT_ALGORITHM_IDENTIFIER, *PCRYPT_ALGORITHM_IDENTIFIER; 
// typedef struct _CRYPT_ATTRIBUTE { 
// 	LPSTR pszObjId; 
// 	DWORD cValue; 
// 	PCRYPT_ATTR_BLOB    rgValue; 
// } CRYPT_ATTRIBUTE, *PCRYPT_ATTRIBUTE; 
// typedef struct _CTL_ENTRY { 
// 	CRYPT_DATA_BLOB     SubjectIdentifier;   // For example, its hash 
// 	DWORD cAttribute; 
// 	PCRYPT_ATTRIBUTE    rgAttribute;  // OPTIONAL 
// } CTL_ENTRY, *PCTL_ENTRY; 
// typedef struct _CERT_EXTENSION { 
// 	LPSTR pszObjId; 
// 	BOOL  fCritical; 
// 	CRYPT_OBJID_BLOB    Value; 
// } CERT_EXTENSION, *PCERT_EXTENSION; 
// typedef struct _CTL_INFO { 
// 	DWORD  dwVersion; 
// 	CTL_USAGE     SubjectUsage; 
// 	CRYPT_DATA_BLOB      ListIdentifier;     // OPTIONAL 
// 	CRYPT_INTEGER_BLOB   SequenceNumber;     // OPTIONAL 
// 	FILETIME      ThisUpdate; 
// 	FILETIME      NextUpdate;  // OPTIONAL 
// 	CRYPT_ALGORITHM_IDENTIFIER  SubjectAlgorithm; 
// 	DWORD  cCTLEntry; 
// 	PCTL_ENTRY    rgCTLEntry;  // OPTIONAL 
// 	DWORD  cExtension; 
// 	PCERT_EXTENSION      rgExtension; // OPTIONAL 
// } CTL_INFO, *PCTL_INFO; 
typedef void *HCERTSTORE; 
typedef void *HCRYPTMSG; 
// typedef struct _CTL_CONTEXT { 
// 	DWORD     dwMsgAndCertEncodingType; 
// 	BYTE      *pbCtlEncoded; 
// 	DWORD     cbCtlEncoded; 
// 	PCTL_INFO pCtlInfo; 
// 	HCERTSTORE hCertStore; 
// 	HCRYPTMSG hCryptMsg; 
// 	BYTE      *pbCtlContent; 
// 	DWORD     cbCtlContent; 
// } CTL_CONTEXT, *PCTL_CONTEXT; 
typedef const CTL_CONTEXT *PCCTL_CONTEXT; 
typedef struct WINTRUST_CATALOG_INFO_ 
{ 
	DWORD  cbStruct; 
	DWORD  dwCatalogVersion; 
	LPCWSTR pcwszCatalogFilePath; 
	LPCWSTR pcwszMemberTag; 
	LPCWSTR pcwszMemberFilePath; 
	HANDLE hMemberFile; 
	BYTE*  pbCalculatedFileHash; 
	DWORD  cbCalculatedFileHash; 
	PCCTL_CONTEXT pcCatalogContext; 
} WINTRUST_CATALOG_INFO, *PWINTRUST_CATALOG_INFO; 
typedef struct WINTRUST_BLOB_INFO_ 
{ 
	DWORD   cbStruct; 
	GUID    gSubject; 
	LPCWSTR pcwszDisplayName; 
	DWORD   cbMemObject; 
	BYTE*   pbMemObject; 
	DWORD   cbMemSignedMsg; 
	BYTE*   pbMemSignedMsg; 
} WINTRUST_BLOB_INFO, *PWINTRUST_BLOB_INFO; 
// typedef struct _CRYPT_ATTRIBUTES { 
// 	IN DWORD  cAttr; 
// 	IN PCRYPT_ATTRIBUTE     rgAttr; 
// } CRYPT_ATTRIBUTES, *PCRYPT_ATTRIBUTES; 
// typedef struct _CMSG_SIGNER_INFO { 
// 	DWORD  dwVersion; 
// 	CERT_NAME_BLOB Issuer; 
// 	CRYPT_INTEGER_BLOB   SerialNumber; 
// 	CRYPT_ALGORITHM_IDENTIFIER  HashAlgorithm; 
// 	CRYPT_ALGORITHM_IDENTIFIER  HashEncryptionAlgorithm; 
// 	CRYPT_DATA_BLOB      EncryptedHash; 
// 	CRYPT_ATTRIBUTES     AuthAttrs; 
// 	CRYPT_ATTRIBUTES     UnauthAttrs; 
// } CMSG_SIGNER_INFO, *PCMSG_SIGNER_INFO; 
typedef struct WINTRUST_SGNR_INFO_ 
{ 
	DWORD      cbStruct; 
	LPCWSTR    pcwszDisplayName; 
	CMSG_SIGNER_INFO* psSignerInfo; 
	DWORD      chStores; 
	HCERTSTORE*pahStores; 
} WINTRUST_SGNR_INFO, *PWINTRUST_SGNR_INFO; 
// typedef struct _CRYPT_BIT_BLOB { 
// 	DWORD   cbData; 
// 	BYTE    *pbData; 
// 	DWORD   cUnusedBits; 
// } CRYPT_BIT_BLOB, *PCRYPT_BIT_BLOB; 
// typedef struct _CERT_PUBLIC_KEY_INFO { 
// 	CRYPT_ALGORITHM_IDENTIFIER    Algorithm; 
// 	CRYPT_BIT_BLOB  PublicKey; 
// } CERT_PUBLIC_KEY_INFO, *PCERT_PUBLIC_KEY_INFO; 
// typedef struct _CERT_INFO { 
// 	DWORD  dwVersion; 
// 	CRYPT_INTEGER_BLOB   SerialNumber; 
// 	CRYPT_ALGORITHM_IDENTIFIER  SignatureAlgorithm; 
// 	CERT_NAME_BLOB Issuer; 
// 	FILETIME      NotBefore; 
// 	FILETIME      NotAfter; 
// 	CERT_NAME_BLOB Subject; 
// 	CERT_PUBLIC_KEY_INFO SubjectPublicKeyInfo; 
// 	CRYPT_BIT_BLOB IssuerUniqueId; 
// 	CRYPT_BIT_BLOB SubjectUniqueId; 
// 	DWORD  cExtension; 
// 	PCERT_EXTENSION      rgExtension; 
// } CERT_INFO, *PCERT_INFO; 
// typedef struct _CERT_CONTEXT { 
// 	DWORD     dwCertEncodingType; 
// 	BYTE      *pbCertEncoded; 
// 	DWORD     cbCertEncoded; 
// 	PCERT_INFO pCertInfo; 
// 	HCERTSTORE hCertStore; 
// } CERT_CONTEXT, *PCERT_CONTEXT; 
typedef struct WINTRUST_CERT_INFO_ 
{ 
	DWORD  cbStruct; 
	LPCWSTR pcwszDisplayName; 
	CERT_CONTEXT* psCertContext; 
	DWORD  chStores; 
	HCERTSTORE*   pahStores; 
	DWORD  dwFlags; 
	FILETIME*     psftVerifyAsOf; 
} WINTRUST_CERT_INFO, *PWINTRUST_CERT_INFO; 
typedef struct _WINTRUST_DATA 
{ 
	DWORD  cbStruct; 
	LPVOID pPolicyCallbackData; 
	LPVOID pSIPClientData; 
	DWORD  dwUIChoice; 
	DWORD  fdwRevocationChecks; 
	DWORD  dwUnionChoice; 
	union 
	{ 
		struct WINTRUST_FILE_INFO_*    pFile; 
		struct WINTRUST_CATALOG_INFO_* pCatalog; 
		struct WINTRUST_BLOB_INFO_*    pBlob; 
		struct WINTRUST_SGNR_INFO_*    pSgnr; 
		struct WINTRUST_CERT_INFO_*    pCert; 
	} DUMMYUNIONNAME; 
	DWORD  dwStateAction; 
	HANDLE hWVTStateData; 
	WCHAR* pwszURLReference; 
	DWORD  dwProvFlags; 
	DWORD  dwUIContext; 
} WINTRUST_DATA, *PWINTRUST_DATA; 
typedef struct CATALOG_INFO_  
{ 
	DWORD cbStruct; 
	WCHAR wszCatalogFile[MAX_PATH]; 
} CATALOG_INFO; 
typedef HANDLE HCATADMIN; 
typedef HANDLE HCATINFO; 

BOOL (WINAPI *CryptCATAdminAcquireContext)(HCATADMIN*,const GUID*,DWORD); 
BOOL (WINAPI *CryptCATAdminReleaseContext)(HCATADMIN,DWORD); 
BOOL (WINAPI *CryptCATAdminCalcHashFromFileHandle)(HANDLE,DWORD*,BYTE*,DWORD); 
HCATINFO  (WINAPI *CryptCATAdminEnumCatalogFromHash)(HCATADMIN,BYTE*,DWORD,DWORD,HCATINFO*); 
BOOL (WINAPI *CryptCATAdminReleaseCatalogContext)(HCATADMIN,HCATINFO,DWORD); 
BOOL (WINAPI *CryptCATCatalogInfoFromContext)(HCATINFO,CATALOG_INFO*,DWORD); 
LONG (WINAPI *WinVerifyTrust)( HWND hwnd,GUID *ActionID,LPVOID  ActionData); 
/* dwUIChoice */ 
#define WTD_UI_ALL  1 
#define WTD_UI_NONE 2 
#define WTD_UI_NOBAD3 
#define WTD_UI_NOGOOD      4 
/* fdwRevocationChecks */ 
#define WTD_REVOKE_NONE    0 
#define WTD_REVOKE_WHOLECHAIN     1 
/* dwUnionChoice */ 
#define WTD_CHOICE_FILE    1 
#define WTD_CHOICE_CATALOG 2 
#define WTD_CHOICE_BLOB    3 
#define WTD_CHOICE_SIGNER  4 
#define WTD_CHOICE_CERT    5 
#define WTD_STATEACTION_IGNORE    0 
#define WTD_STATEACTION_VERIFY    1 
#define WTD_STATEACTION_CLOSE     2 
#define WTD_STATEACTION_AUTO_CACHE3 
#define WTD_STATEACTION_AUTO_CACHE_FLUSH 4 
#define WTD_SAFER_FLAG     0x00000100 
#define WINTRUST_ACTION_GENERIC_VERIFY_V2 { 0xaac56b,   0xcd44, 0x11d0, { 0x8c,0xc2,0x00,0xc0,0x4f,0xc2,0x95,0xee }} 


BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD dwSize)
{ 
	DWORD dwMinSize;
	dwMinSize = MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, NULL, 0);
	if(dwSize < dwMinSize)
	{
		return FALSE;
	}
	MultiByteToWideChar (CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize); 
	return TRUE;
}

BOOL WCharToMByte(LPCWSTR lpcwszStr, LPSTR lpszStr, DWORD dwSize)
{
	DWORD dwMinSize;
	dwMinSize = WideCharToMultiByte(CP_OEMCP,NULL,lpcwszStr,-1,NULL,0,NULL,FALSE);
	if(dwSize < dwMinSize)
	{
		return FALSE;
	}
	WideCharToMultiByte(CP_OEMCP,NULL,lpcwszStr,-1,lpszStr,dwSize,NULL,FALSE);
	return TRUE;
}

#endif