#pragma once
#include "NA_NetworkManager.h"
#include "NA_Message.h"
class NA_Socket
{

public:
	static enum SOCK_TYPE {NOT_SET, UDP, TCP};
	static enum SOCK_MODE {NOT_SET, SERVER, CLIENT};
	NA_Socket();
	~NA_Socket();
	bool init(SOCK_TYPE sockType, SOCK_MODE sockMode, PCSTR port, PCSTR address = NULL); //leave address as null for servers

private:
	SOCKET sock;
	bool initUDP(SOCK_MODE sockMode, PCSTR port, PCSTR address);
	bool initTCP(SOCK_MODE sockMode, PCSTR port, PCSTR address);
	bool initUDPClient(PCSTR port, PCSTR address);
	bool initUDPServer(PCSTR port);
	bool initTCPClient(PCSTR port, PCSTR address);
	bool initTCPServer(PCSTR port);
};

