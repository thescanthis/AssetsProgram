#pragma once

#include "Types.h"
#include "CoreMacro.h"
#include "CoreTLS.h"
#include "CoreGlobal.h"

#include <array>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>

#include <windows.h>
#include <iostream>
#include <assert.h>
#include <iterator>
#include <algorithm>
#include <string>
#include <tuple>
#include <typeindex>

#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
using namespace std;

#include <winsock2.h>
#include <mswsock.h>
#include <ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#include "SendBuffer.h"
#include "Session.h"
#include "JobQueue.h"


