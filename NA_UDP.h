#pragma once
#include "NA_Thread.h"
#include <WinSock2.h>
#include <WS2tcpip.h>

class NA_UDP : 	public NA_Thread
{
private:
	SOCKET sock = INVALID_SOCKET;
	WSADATA wsaData;

protected:
	//inhearet and override to add encrytion direct reference method to persorm the actual send/recive in the override
	//https://www.programiz.com/cpp-programming/function-overriding
	void send(); // NA_TCP::send
	void recive(); // NA_TPC::recive
	
public:
	NA_UDP();
	~NA_UDP();
	bool init();
};

