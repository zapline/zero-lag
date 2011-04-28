#include "StdAfx.h"
#include "ServerManage.h"

CServerManage::CServerManage(void)
{
}

CServerManage::~CServerManage(void)
{
}

/* 功能：枚举服務。
/  调用方式：

	ENUM_SERVICE_STATUS* lpservice;
	SERVICE_STATUS  servicestatus;
	DWORD servicesReturned = 0;
	lpservice = NULL;
	EnumServername(&lpservice,SERVICE_WIN32|SERVICE_DRIVER,
		SERVICE_STATE_ALL,&servicesReturned);
	返回值回显：
	for(int i=0;i < servicesReturned;i++)
	{
		cout <<lpservice[i].lpServiceName;
		cout << lpservice[i].lpDisplayName;
		servicestatus = lpservice[i].ServiceStatus;
	}*/
void CServerManage::EnumServername(ENUM_SERVICE_STATUS** lpservice,DWORD serverType,DWORD serverState,DWORD* servicesReturned)
{
	SC_HANDLE       hService = NULL;
	DWORD bytesNeeded,resumeHandle = 0;
	ENUM_SERVICE_STATUS  service,*pservice;
	BOOL	rc;
	hService = OpenSCManager(NULL,NULL,SC_MANAGER_ENUMERATE_SERVICE);
	rc = ::EnumServicesStatus(hService,serverType,serverState,
		&service,sizeof(service),
		&bytesNeeded,servicesReturned,&resumeHandle);
	DWORD lperror = ::GetLastError();
	if ((rc == FALSE) && (lperror == ERROR_MORE_DATA))
	{
		resumeHandle = 0;
		DWORD bytes = bytesNeeded + sizeof(ENUM_SERVICE_STATUS);
		pservice = new ENUM_SERVICE_STATUS [bytes];
		*lpservice = pservice;
		::EnumServicesStatus(hService,serverType,serverState,
			pservice,bytes,
			&bytesNeeded,servicesReturned,&resumeHandle);
    }
	CloseServiceHandle(hService);
	//內存洩漏，尚未解決!!!
}

/*功能：启动或停止servername服务。成功返回TRUE，失败返回FALSE
//start== TRUE启动服务
/ start = false停止服务*/
BOOL CServerManage::ChangeServerStatusByname(wchar_t* servername,BOOL start)
{
	if(servername[0] == '\0')
		return FALSE;
	BOOL         hr;
	SC_HANDLE       hSCM;
	SC_HANDLE       hService;
	SERVICE_STATUS  ssStatus;
	DWORD           dwStartTime;
	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
	hService = OpenService(hSCM, servername, SERVICE_STOP|SERVICE_START|SERVICE_QUERY_STATUS);
	dwStartTime = GetTickCount();
	hr = QueryServiceStatus(hService, &ssStatus);
	if (!hr) 
	{
		CloseServiceHandle(hService);
		CloseServiceHandle(hSCM);
		return FALSE;
	}
	if(start) //启动服务；
	{
		if (ssStatus.dwCurrentState != SERVICE_RUNNING)
		{
			hr = StartService(hService, 0, NULL);//启动
			if (!hr) 
			{
				CloseServiceHandle(hService);
				CloseServiceHandle(hSCM);
				return FALSE;
			}
		}
	}
	else //停止服务
	{
		if (ssStatus.dwCurrentState != SERVICE_STOPPED)
		{
			
			while (ssStatus.dwCurrentState == SERVICE_STOP_PENDING)
			{
				hr = QueryServiceStatus(hService, &ssStatus);
				if (!hr)
				{
					CloseServiceHandle(hService);
					CloseServiceHandle(hSCM);
					return FALSE;
				}
				if (ssStatus.dwCurrentState == SERVICE_STOPPED)
					break;
			}
			hr = ControlService(hService, SERVICE_CONTROL_STOP, &ssStatus);//停止
			if (!hr)
			{
				CloseServiceHandle(hService);
				CloseServiceHandle(hSCM);
				return FALSE;
			}
		}
	}
	CloseServiceHandle(hService);
	CloseServiceHandle(hSCM);
	return TRUE;
}

/*得到服务的状态*/
BOOL CServerManage::GetServerStatusByname(wchar_t* servername,SERVICE_STATUS&  ssStatus)
{
	if(servername[0] == '\0')
		return FALSE;
	HRESULT         hr;
	SC_HANDLE       hSCM;
	SC_HANDLE       hService;
	DWORD           dwStartTime;
	hSCM = OpenSCManager(NULL, NULL, SC_MANAGER_CONNECT);
	hService = OpenService(hSCM, servername,SERVICE_QUERY_STATUS);
	dwStartTime = GetTickCount();
	hr = QueryServiceStatus(hService, &ssStatus);
	if (!hr) 
	{
		CloseServiceHandle(hService);
		CloseServiceHandle(hSCM);
		return FALSE;
	}
	CloseServiceHandle(hService);
	CloseServiceHandle(hSCM);
	return TRUE;
}