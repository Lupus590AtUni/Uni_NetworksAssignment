#include "NA_TCP.h"

#include "globals.h"
#include <iostream>
using std::cerr;

//NOTE: scrap and restart?

DWORD NA_TCP::threadFunc() //background recive
{
	//Do any setup

	while (!terminateRequested)
	{
		//TODO: UDP listen for messages and add to queue


		recv(sock, recvbuf, recvbuflen, 0);
	}

	//Do any cleanup

	return 0;
}

NA_TCP::NA_TCP()
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
}

NA_TCP::~NA_TCP()
{
	if (ready)
		closesocket(sock);
}

bool NA_TCP::c(string address, string port)
{
	if (!ready) //should call init first
		return false;

	addrinfo *addrInfoResult;
	int result = getaddrinfo(address.c_str, port.c_str, &hints, &addrInfoResult); //looking for all servers which can do what I need
	if (result != 0)
	{
		return false;
	}

	sock = socket(addrInfoResult->ai_family, addrInfoResult->ai_socktype, addrInfoResult->ai_protocol); //create the socket
	int result = connect(sock, addrInfoResult->ai_addr, (int)addrInfoResult->ai_addrlen); //attempt to connect to the first result of getaddrinfo

																						  //LOW: attempt connecton to other addresses
	if (result != 0)
	{
		closesocket(sock);
		return false;
	}

	freeaddrinfo(addrInfoResult);
	if (sock == INVALID_SOCKET)
		return false; //had a problem somewhere
					  //else
	return true; //connection made

}

bool NA_TCP::init()
{
	if (!ready)
	{
		//Init
		if (!na_netMan.isReady())
		{
			if (!na_netMan.init())
				return false; //na_netMan not ready and failed to init
		}

		//na_netMan is ready, do own init



	}
	//else already ready
	ready = true;
	return ready;
}

void NA_TCP::s(string str)
{
	//LOW: special packing

	send(sock, str.c_str, str.length, 0); //NOTE: check if loses /n
										  //+1 to length if it does
										  //somptom: tons of junk is appended to message
}

string NA_TCP::r()
{
	string str;

	queueCritSec.enter();//lock the queue
	if (!reciveQueue.isEmpty())
	{
		str = reciveQueue.dequeue();//pull item from queue
	}
	queueCritSec.leave();//unlock the queue



						 //LOW:special unpacking



	return string();
}

bool NA_TCP::hasMessage()
{
	return !reciveQueue.isEmpty();
}
