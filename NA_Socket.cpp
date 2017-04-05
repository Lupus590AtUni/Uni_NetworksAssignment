#include "NA_Socket.h"
#include "globals.h"
#include <iostream>
using std::cerr;


NA_Socket::NA_Socket()
{
}


NA_Socket::~NA_Socket()
{
}

bool NA_Socket::init(SOCK_TYPE sockType, SOCK_MODE sockMode)
{
	
	switch (sockType)
	{
		case SOCK_TYPE::NOT_SET:
			return false;
			break;
		case SOCK_TYPE::TCP:
			return initTCP(sockMode);
			break;
		case SOCK_TYPE::UDP:
			return initUDP(sockMode);
			break;
		default:
			NA_consoleOutputCritSect.enter();
			cerr << "NA_Socket::init - unhandled case\n";
			NA_consoleOutputCritSect.leave();
			return false;
			break;
	}
	

	return false;
}

bool NA_Socket::initUDP(SOCK_MODE sockMode)
{
	switch (sockMode)
	{
		case SOCK_MODE::NOT_SET:
			return false;
			break;
		case SOCK_MODE::CLIENT:
			return initUDPClient();
			break;
		case SOCK_MODE::SERVER:
			return initUDPServer();
			break;
		default:
			NA_consoleOutputCritSect.enter();
			cerr << "NA_Socket::initUDP - unhandled case\n";
			NA_consoleOutputCritSect.leave();
			return false;
			break;
	}

	return false;
}

bool NA_Socket::initTCP(SOCK_MODE sockMode)
{
	switch (sockMode)
	{
		case SOCK_MODE::NOT_SET:
			return false;
			break;
		case SOCK_MODE::CLIENT:
			return initTCPClient();
			break;
		case SOCK_MODE::SERVER:
			return initTCPServer();
			break;
		default:
			NA_consoleOutputCritSect.enter();
			cerr << "NA_Socket::initTCP - unhandled case\n";
			NA_consoleOutputCritSect.leave();
			return false;
			break;
	}

	return false;

	return false;
}

bool NA_Socket::initUDPClient()
{
	return false;
}

bool NA_Socket::initUDPServer()
{
	return false;
}

bool NA_Socket::initTCPClient()
{
	return false;
}

bool NA_Socket::initTCPServer()
{
	return false;
}
