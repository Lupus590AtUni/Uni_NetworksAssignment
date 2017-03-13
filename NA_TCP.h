#pragma once
#include "NA_Thread.h"
#include <WinSock2.h>
#include <WS2tcpip.h>

class NA_TCP : 	public NA_Thread
{

public:
	NA_TCP();
	~NA_TCP();
};

