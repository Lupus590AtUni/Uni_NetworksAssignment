#pragma once
#include "NA_NetworkManager.h"
#include "NA_CriticalSection.h"
#include "NA_Queue.h"
#include <string>
using std::string;

extern NA_NetworkManager na_networkManager;

class NA_UDP : 	public NA_Thread
{
	friend class NA_NetworkManager;

private:
	NA_Queue<string> reciveQueue;

	bool ready = false;
	SOCKET socket = INVALID_SOCKET;
	//TODO: if socket becomes invalid, assume that NA_NetworkManager wants to cleanup 
	unsigned short port = 0; // http://www.webopedia.com/quick_ref/portnumbers.asp https://msdn.microsoft.com/en-us/library/s3f49ktz.aspx 
	
	DWORD threadFunc();


protected:
	//inhearet and override to add encrytion direct reference method to persorm the actual send/recive in the override
	//this may not be the best/clearest way
	//https://www.programiz.com/cpp-programming/function-overriding
	void send(); 
	void recive(); 

	
public:
	NA_UDP();
	~NA_UDP();
	bool init();
};

