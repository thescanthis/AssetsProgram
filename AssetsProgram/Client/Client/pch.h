#pragma once

#include <wx/statbmp.h>    // wxStaticBitmap
#include <wx/dcbuffer.h>
#include <wx/statline.h>
#include <wx/treectrl.h>
#include "Types.h"

#include <windows.h>
#include <iostream>
#include <assert.h>
#include <array>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <string>
#include <queue>
#include <map>
#include <stack>
#include <list>
#include <set>
#include <tuple>
#include <typeindex>

#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>

#include <functional>
#include "TemplateFunc.h"

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

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