#pragma once
#include "NA_NetworkManager.h"
#include "NA_CriticalSection.h"
#include "NA_Queue.h"
#include "NA_Thread.h"
#include "NA_Message.h"
#include <string>
using std::string;

extern NA_NetworkManager na_netMan;

class NA_UDP : 	public NA_Thread
{

private:
	NA_Queue<NA_Message> reciveQueue;
	NA_CriticalSection queueCritSec;

	static const unsigned int bufferLength = 10000;
	struct addrinfo hints;
	
	socketRole sockRole = socketRole::invalid;
	bool ready = false;
	SOCKET sock = INVALID_SOCKET;
	//LOW: if socket becomes invalid
		//assume that NA_NetworkManager wants to cleanup 
	DWORD threadFunc(); //background recive


protected:
	//LOW: some whay to allow user added encryption
	//inhearet and override to add encrytion direct reference method to persorm the actual send/recive in the override
	//this may not be the best/clearest way
	//https://www.programiz.com/cpp-programming/function-overriding
	//void send(); 
	//void recive(); 


	
public:
	NA_UDP();
	~NA_UDP();
	bool init(socketRole role);
	bool s(NA_Message m);
	NA_Message r();
	bool hasMessage(); //returns true when recive func will return a string, false if it will return null
};

