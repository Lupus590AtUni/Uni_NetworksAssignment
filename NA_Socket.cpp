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

bool NA_Socket::init(SOCK_TYPE sockType, SOCK_MODE sockMode, PCSTR port, PCSTR address)
{
	
	switch (sockType)
	{
		case SOCK_TYPE::NOT_SET:
			return false;
			break;
		case SOCK_TYPE::TCP:
			return initTCP(sockMode, port, address);
			break;
		case SOCK_TYPE::UDP:
			return initUDP(sockMode, port, address);
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

bool NA_Socket::initUDP(SOCK_MODE sockMode, PCSTR port, PCSTR address)
{
	switch (sockMode)
	{
		case SOCK_MODE::NOT_SET:
			return false;
			break;
		case SOCK_MODE::CLIENT:
			return initUDPClient(port, address);
			break;
		case SOCK_MODE::SERVER:
			return initUDPServer(port);
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

bool NA_Socket::initTCP(SOCK_MODE sockMode, PCSTR port, PCSTR address)
{
	switch (sockMode)
	{
		case SOCK_MODE::NOT_SET:
			return false;
			break;
		case SOCK_MODE::CLIENT:
			return initTCPClient(port, address);
			break;
		case SOCK_MODE::SERVER:
			return initTCPServer(port);
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

bool NA_Socket::initUDPClient(PCSTR port, PCSTR address)
{
	if (address == NULL)
		return false;

	struct addrinfo *addressList = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;

	int r = getaddrinfo(address, port, &hints, &addressList);

	sock = socket(addressList->ai_family, addressList->ai_socktype, addressList->ai_protocol);
	return false;
}

bool NA_Socket::initUDPServer(PCSTR port)
{

	sockaddr_in	rx_addr;

	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	

	rx_addr.sin_family = AF_INET; // TCPIP
	rx_addr.sin_port = htons((u_short)atol(port));
	rx_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	int r = bind(sock, (SOCKADDR*)&rx_addr, sizeof(rx_addr));


	return false;
}

bool NA_Socket::initTCPClient(PCSTR port, PCSTR address)
{
	if (address == NULL)
		return false;

	struct addrinfo *addressList = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	//TODO: let user do connection
	int r = getaddrinfo(address, port, &hints, &addressList);
	for (ptr = addressList; ptr != NULL; ptr = ptr->ai_next)
	{
		sock = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		int r = connect(sock, ptr->ai_addr, (int)ptr->ai_addrlen);
		break;
	}
	freeaddrinfo(addressList);

	return false;
}

bool NA_Socket::initTCPServer(PCSTR port)
{
	struct addrinfo *addressList = NULL;
	struct addrinfo *ptr = NULL;
	struct addrinfo hints;

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	int r = getaddrinfo(NULL, port, &hints, &addressList);

	sock = socket(addressList->ai_family, addressList->ai_socktype, addressList->ai_protocol);
	int r = bind(sock, addressList->ai_addr, (int)addressList->ai_addrlen);

	freeaddrinfo(addressList);

	int r = listen(sock, SOMAXCONN);
	
	return false;
}
