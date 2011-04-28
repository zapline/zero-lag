// stdafx.h : 标准系统包含文件的包含文件，
// 或是常用但不常更改的项目特定的包含文件
//

#pragma once


//#define WIN32_LEAN_AND_MEAN		// 从 Windows 头中排除极少使用的资料
// Windows 头文件:
//#include <windows.h>

#pragma warning(disable: 4995)
#pragma warning(disable: 4996)
#pragma warning(disable: 4819)

#define WINVER          0x0500
#define _WIN32_WINNT    0x0501
#define _WIN32_IE       0x0601

#include "Include/KuiHead.h"

#ifndef ASSERT
#ifdef _DEBUG
#define ASSERT assert
#else
#define ASSERT
#endif
#endif