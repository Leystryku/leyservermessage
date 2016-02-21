#pragma once

#include "stdafx.h"


#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

#ifdef _WIN32
#pragma once
#define lastneterror() WSAGetLastError()
#else
#define lastneterror() errno
#endif