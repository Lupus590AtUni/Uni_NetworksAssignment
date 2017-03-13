#pragma once
#include "NA_NetworkManager.h"

class NA_UDP : 	public NA_Thread
{
	friend class NA_NetworkManager;

private:
	bool ready = false;
	SOCKET socket = INVALID_SOCKET;
	//TODO: if socket becomes invalid, assume that NA_NetworkManager wants to cleanup 
	unsigned short port = 0; // http://www.webopedia.com/quick_ref/portnumbers.asp https://msdn.microsoft.com/en-us/library/s3f49ktz.aspx 

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

