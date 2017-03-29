#include "NA_UDP.h"

#include "globals.h"
#include <iostream>
using std::cerr;

//NOTE:scrap and restart?
//alot of this is TCP

DWORD NA_UDP::threadFunc() //background recive
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

bool NA_UDP::init()
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

		sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	}
	//else already ready
	ready = true;
	return ready;
}

void NA_UDP::s(string str)
{
	//LOW: special packing

	send(sock, str.c_str, str.length, 0); //NOTE: check if loses /n
											//+1 to length if it does
											//somptom: tons of junk is appended to message
}

string NA_UDP::r()
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

bool NA_UDP::hasMessage()
{
	return !reciveQueue.isEmpty();
}
