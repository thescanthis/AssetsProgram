#pragma once

#include <wx/statbmp.h>    // wxStaticBitmap
#include <wx/dcbuffer.h>
#include <wx/statline.h>
#include <wx/treectrl.h>
#include <wx/notebook.h>
#include <wx/srchctrl.h>
#include <wx/accel.h>
#include <wx/sysopt.h>
#include <wx/settings.h>
#include <wx/datectrl.h>
#include <wx/dateevt.h>
#include "WidgetTypes.h"
#include "CorePch.h"

#include "TemplateFunc.h"
#include "WidgetUtilsFunc.h"
#include "DBTest.h"

#if _DEBUG
#pragma comment (lib,"wxbase32ud.lib")
#pragma comment (lib,"wxbase32ud_net.lib")
#pragma comment (lib,"wxbase32ud_xml.lib")
#pragma comment (lib,"wxexpatd.lib")
#pragma comment (lib,"wxjpegd.lib")
#pragma comment (lib,"wxmsw32ud_adv.lib")
#pragma comment (lib,"wxmsw32ud_aui.lib")
#pragma comment (lib,"wxmsw32ud_core.lib")
#pragma comment (lib,"wxmsw32ud_gl.lib")
#pragma comment (lib,"wxmsw32ud_html.lib")
#pragma comment (lib,"wxmsw32ud_media.lib")
#pragma comment (lib,"wxmsw32ud_propgrid.lib")
#pragma comment (lib,"wxmsw32ud_qa.lib")
#pragma comment (lib,"wxmsw32ud_ribbon.lib")
#pragma comment (lib,"wxmsw32ud_richtext.lib")
#pragma comment (lib,"wxmsw32ud_stc.lib")
#pragma comment (lib,"wxmsw32ud_webview.lib")
#pragma comment (lib,"wxmsw32ud_xrc.lib")
#pragma comment (lib,"wxpngd.lib")
#pragma comment (lib,"wxregexud.lib")
#pragma comment (lib,"wxscintillad.lib")
#pragma comment (lib,"wxtiffd.lib")
#pragma comment (lib,"wxzlibd.lib")
#pragma comment (lib,"Rpcrt4.lib")
#pragma comment (lib,"Comctl32.lib")
#elif Relelase Librarys
#endif

#ifdef _DEBUG
#pragma comment(lib, "ServerCore\\Debug\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Debug\\libprotobufd.lib")
#else
#pragma comment(lib, "ServerCore\\Release\\ServerCore.lib")
#pragma comment(lib, "Protobuf\\Release\\libprotobuf.lib")
#endif


//#ifdef _MSC_VER
//#  ifdef _DEBUG
//#    define _CRTDBG_MAP_ALLOC
//#    include <crtdbg.h>
//#    define DBG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
//#    define new DBG_NEW
//#  endif
// Main Header에 맨윗줄에_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);  // 자동 릭 체크
//#endif