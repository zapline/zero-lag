// KUILib.cpp : 定义 DLL 应用程序的入口点。
//

#include "stdafx.h"
#include "KUILib.h"

CAppModule * _ModulePtr;
HINSTANCE g_hInstance;

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
    return TRUE;
}

// 这是导出变量的一个示例
KUILIB_API int nKUILib=0;

// 这是导出函数的一个示例。
KUILIB_API int fnKUILib(void)
{
	return 42;
}

// 这是已导出类的构造函数。
// 有关类定义的信息，请参阅 KUILib.h
CKUILib::CKUILib()
{ 
	return; 
}
