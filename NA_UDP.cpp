#include "NA_UDP.h"

#include "globals.h"
#include <iostream>
using std::cerr;
extern NA_CriticalSection NA_consoleOutputCritSect;

DWORD NA_UDP::threadFunc() //background recive
{
	//Do any setup
	sockaddr sender_addr;
	int sender_addr_size = sizeof(sender_addr);
	char buffer[bufferLength];
	while (!terminateRequested)
	{
		static int r = recvfrom(sock, buffer, bufferLength, 0, &sender_addr, &sender_addr_size);
		if(r == SOCKET_ERROR)
		{
			//had an error
			//TODO: identify error, we may need to terminate
		}
		else
		{
			//all good
			NA_Message m;
			m.str = buffer;
			m.str.shrink_to_fit(); //may as well try to use a bit less memory
			m.senderAddress = sender_addr;
			queueCritSec.enter();
			reciveQueue.enqueue(m);
			queueCritSec.leave();
		}

		
	}

	//Do any cleanup

	return 0;
}

NA_UDP::NA_UDP()
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
}


NA_UDP::~NA_UDP()
{
	if (ready)
		closesocket(sock);
}

bool NA_UDP::init(socketRole role)
{
	if (!ready)
	{
		//Init
		if (!na_netMan.isReady())
		{
			if (!na_netMan.init())
				return false; //na_netMan not ready and failed to init
		}

		sockRole = role;

		//na_netMan is ready, do own init
		if (sockRole == socketRole::client)
		{
			

			if (getaddrinfo(nodeName, port, &hints, &addressList) != 0)
			{
				NA_consoleOutputCritSect.enter();
				cerr << "NA_UDP:init - getaddrinfo failed\n";
				NA_consoleOutputCritSect.leave();
				return false;
			}

			sock = socket(addressList->ai_family, addressList->ai_socktype, addressList->ai_protocol);
			ready = true;
			return ready;
		}
		else if (sockRole == socketRole::server)
		{
			sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

			sockaddr_in rx_addr;
			rx_addr.sin_family = AF_INET;
			rx_addr.sin_port = htons((u_short)atol(port));
			rx_addr.sin_addr.s_addr = htonl(INADDR_ANY);

			if (bind(sock, (SOCKADDR*)&rx_addr, sizeof(rx_addr)) != 0)
			{
				NA_consoleOutputCritSect.enter();
				cerr << "NA_UDP:init - socket bind failed\n";
				NA_consoleOutputCritSect.leave();
				return false;
			}

		}
		else if (sockRole == socketRole::invalid)
		{
			return false;
		}
		else
		{
			NA_consoleOutputCritSect.enter();
			cerr << "NA_UDP:init - Unhandled socketRole\n";
			NA_consoleOutputCritSect.leave();
			return false;
		}
	

	}
	//else already ready
	ready = true;
	return ready;
}

bool NA_UDP::s(NA_Message m)
{
	//LOW: special packing

	int r = sendto(sock, m.str.c_str, m.str.length,0, &m.destinationAddress, sizeof(m.destinationAddress)); //NOTE: check if loses /n
											//+1 to length if it does
											//somptom: tons of junk is appended to message
	if (r == SOCKET_ERROR)
	{
		//TODO: check what error was
		return false;
	}
	else
	{
		return true;
	}
}

NA_Message NA_UDP::r()
{
	NA_Message m;

	queueCritSec.enter();//lock the queue
	if (!reciveQueue.isEmpty())
	{
		m = reciveQueue.dequeue();//pull item from queue
	}
	queueCritSec.leave();//unlock the queue

	
	
	//LOW:special unpacking

	

	return m;
}

bool NA_UDP::hasMessage()
{
	queueCritSec.enter();//lock the queue
	bool r = !reciveQueue.isEmpty();
	queueCritSec.leave();//unlock the queue
	return r;
}
