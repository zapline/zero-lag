#define _RICHEDIT_VER   0x0200

#define _SECURE_ATL 0
//#define _WTL_USE_CSTRING

#include <atlbase.h>
#include <atlwin.h>
#include <atlstr.h>
#include <atltrace.h>
#include <atlfile.h>

#define _WTL_NO_CSTRING


#include <exdisp.h>
#include <exdispid.h>
#include <mshtml.h>
#include <mshtmdid.h>
#include <math.h>


#include "../3Party/tinyxml/tinyxml.h"
#include "../3Party/zlib/zlib.h"
//WTL//
#include "../3Party/wtl/atlapp.h"
#include "../3Party/wtl/atlframe.h"
#include "../3Party/wtl/atlctrls.h"
#include "../3Party/wtl/atlctrlw.h"
#include "../3Party/wtl/atlctrlx.h"
#include "../3Party/wtl/atldlgs.h"
#include "../3Party/wtl/atlcrack.h"
#include "../3Party/wtl/atlmisc.h"
//WTL//

#include <atltime.h>

#include "kuiwin/kuilistview.h"
#include "kuiwin/realwnd/KuiRealHead.h"
#include "wtlhelper/whwindow.h"

#include <Shlwapi.h>

extern CAppModule* _ModulePtr;
extern HINSTANCE g_hInstance;