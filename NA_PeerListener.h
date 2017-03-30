#pragma once
#include <WinSock2.h>
#include "NA_Thread.h"
class NA_PeerListener : public NA_Thread
{
private:
	DWORD threadFunc();

public:
	NA_PeerListener();
	~NA_PeerListener();

	SOCKET sock;

	
};

