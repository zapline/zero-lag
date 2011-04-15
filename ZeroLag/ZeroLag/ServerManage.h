#pragma once
#include <winsvc.h>

class CServerManage
{
public:
	CServerManage(void);
public:
	~CServerManage(void);

	void EnumServername(ENUM_SERVICE_STATUS** lpservice,
		DWORD serverType,
		DWORD serverState,
		DWORD* servicesReturned); //枚举系统的服务及其状态。
	BOOL ChangeServerStatusByname(wchar_t* servername,BOOL start = TRUE);

	BOOL GetServerStatusByname(wchar_t* servername,SERVICE_STATUS&  ssStatus);
};
