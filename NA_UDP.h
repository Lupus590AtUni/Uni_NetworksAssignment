#pragma once
#include "NA_NetworkManager.h"
#include "NA_CriticalSection.h"
#include "NA_Queue.h"
#include <string>
using std::string;

extern NA_NetworkManager na_netMan;

class NA_UDP : 	public NA_Thread
{

private:
	NA_Queue<string> reciveQueue;
	NA_CriticalSection queueCritSec;

	struct addrinfo hints;
	
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
	bool init();
	void s(string str);
	string r();
	bool hasMessage(); //returns true when recive func will return a string, false if it will return null
};

