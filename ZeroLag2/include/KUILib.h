// 下列 ifdef 块是创建使从 DLL 导出更简单的
//宏的标准方法。此 DLL 中的所有文件都是用命令行上定义的 KUILIB_EXPORTS
// 符号编译的。在使用此 DLL 的
//任何其他项目上不应定义此符号。这样，源文件中包含此文件的任何其他项目都会将 
// KUILIB_API 函数视为是从此 DLL 导入的，而此 DLL 则将用此宏定义的
// 符号视为是被导出的。
#ifndef _KUILIB_H
#define _KUILIB_H
#define KUILIB_API

#pragma warning(disable: 4996)

#include "../KUILib/include/kuihead.h"
#include "../KUILib/include/kuiwin/kuiwnd.h"
#include "../KUILib/Include/KuiApp.h"
#include "../KuiLib/Include/wtlhelper/whwindow.h"

#include "../KuiLib/Include/wtlhelper/billext/extentwindow.h"

#define LIBPATH(p,f) p##f 

#ifdef _DEBUG
#pragma comment(lib,LIBPATH(__FILE__, ".dir/../../KUILib/lib/kscbaseD.lib") )
#else
#pragma comment(lib,LIBPATH(__FILE__, ".dir/../../KUILib/lib/kscbase.lib") )
#endif
#pragma comment(lib,"gdiplus.lib")

#endif