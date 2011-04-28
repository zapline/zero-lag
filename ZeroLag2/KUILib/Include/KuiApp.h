#pragma once
#include "..\3party\wtl\atlapp.h"
#include <gdiplus.h>
using namespace Gdiplus;

template <class CWndT>
class CKuiApp :
	public CAppModule
{
public:
	CKuiApp(void){};
	virtual ~CKuiApp(void){};

public:
	HRESULT Init(HINSTANCE hInstance){
		DWORD dwRet = 1;
		HRESULT hRet;
		CRegKey reg;
		GUID guid;
		hRet = __super::Init(NULL, hInstance, &guid);
		if (FAILED(hRet))
			return hRet;
		
		//Get install path
		DWORD dwRet1 = ::GetModuleFileName(NULL, m_strAppFileName.GetBuffer(MAX_PATH + 1), MAX_PATH);
		if (0 == dwRet1)
		{
			m_strAppFileName.ReleaseBuffer(0);

			hRet = E_FAIL;
		}
		else
		{
			m_strAppFileName.ReleaseBuffer();

			m_strAppPath = m_strAppFileName;
			m_strAppPath = m_strAppPath.Left(m_strAppPath.ReverseFind(L'\\'));
		}

		GdiplusStartup(&m_gdiplusToken, &m_gdiplusStartupInput, NULL);

		InitUIResource();

		return hRet;
	};
	VOID UnInit(){
		GdiplusShutdown(m_gdiplusToken);
	};
	UINT_PTR Main(){
		CMessageLoop theLoop;
		CWndT mainwnd;

		_Module.AddMessageLoop(&theLoop);

		RECT rt = {0, 0, 600, 470};
		if (mainwnd.Create(::GetActiveWindow(), &rt) == NULL) 
		{
			return 0;
		}

		mainwnd.ShowWindow(SW_SHOW);

		int nRet = theLoop.Run();

		_Module.RemoveMessageLoop();
		return nRet;
	};

	LPCTSTR	GetAppFilePath(){
		return m_strAppFileName;
	};
	LPCTSTR GetAppDirPath(){
		return m_strAppPath;
	};
    LPCTSTR GetAppVersion();	//get product version
	LPCTSTR GetAppFileVersion();//get file version	
protected:
	KUILIB_API void InitUIResource(){
		KAppRes& appRes = KAppRes::Instance();
		std::string strXml;

		KuiFontPool::SetDefaultFont( _T("ËÎÌו"), -12);

		appRes.GetXmlData("IDR_KSC_SKIN", strXml);
		KuiSkin::LoadSkins(strXml);

		appRes.GetXmlData("IDR_KSC_STYLE", strXml);
		KuiStyle::LoadStyles(strXml);
	};
protected:
	CString m_strAppFileName;
	CString m_strAppPath;
	CString m_strAppVersion;
	CString m_strFileVersion;
	LONG    m_lAppVersionNumber;
	GdiplusStartupInput m_gdiplusStartupInput;
	ULONG_PTR           m_gdiplusToken;
};

