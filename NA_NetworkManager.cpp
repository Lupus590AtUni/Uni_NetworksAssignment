#include "NA_NetworkManager.h"

#include "globals.h"
#include <iostream>
using std::cerr;


NA_NetworkManager::NA_NetworkManager()
{
}


NA_NetworkManager::~NA_NetworkManager()
{
	if (ready)
	{
		WSACleanup(); //Sockets will become invalid which NA_TCP and NA_UDP check for and exit on, user of these two classes should check if it's still a valid object (although they probably destroyed NA_NetworkManager)
	}
}

bool NA_NetworkManager::init()
{
	int r = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (r != 0)
	{
		extern NA_CriticalSection NA_consoleOutputCritSect;
		NA_consoleOutputCritSect.enter();
		cerr << "NA_UDP::init - WSAStartup failer. returned: " << r << "\n";
		NA_consoleOutputCritSect.leave();
		return false;
	}

	ready = true;
	return true;
}

void NA_NetworkManager::cleanup()
{
	// Tell all objects to terminate
	// clean up WinSock2
	WSACleanup();
}
