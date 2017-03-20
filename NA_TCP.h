#pragma once
#include "NA_NetworkManager.h"

extern NA_NetworkManager na_netMan;

class NA_TCP : 	public NA_Thread
{
private:
	NA_Queue<string> reciveQueue;

	struct addrinfo hints;

	bool ready = false;
	SOCKET socket = INVALID_SOCKET;
	//LOW: if socket becomes invalid
		//assume that NA_NetworkManager wants to cleanup 
	DWORD threadFunc(); //background recive


public:
	NA_TCP();
	~NA_TCP();
};

