#include "NA_UDP.h"

#include "globals.h"
#include <iostream>
using std::cerr;


NA_UDP::NA_UDP()
{
}


NA_UDP::~NA_UDP()
{
}

bool NA_UDP::init()
{
	int r = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (r != 0)
	{
		consoleOutputCritSect.enter();
		cerr << "NA_UDP::init - WSAStartup failer. returned: " << r << "\n";
		consoleOutputCritSect.leave();
		return false;
	}

	return true;
}
