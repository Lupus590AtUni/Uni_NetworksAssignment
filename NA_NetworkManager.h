#pragma once
// Creates NA_TCP and NA_UDP objects in properly configured states, also manages WinSock2;

#include "NA_Thread.h"
#include <WinSock2.h>
#include <WS2tcpip.h>

#include "NA_TCP.h"
#include "NA_UDP.h"

enum NA_NetworkMode { client = 0, sever, };

class NA_NetworkManager
{
private:
	WSADATA wsaData;
	bool ready = false;

public:
	
	NA_NetworkManager();
	~NA_NetworkManager();
	bool init();
	void cleanup();
};

