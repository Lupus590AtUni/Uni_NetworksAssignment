#include "NA_TCP.h"

#include "globals.h"
#include <iostream>
using std::cerr;

NA_TCP::NA_TCP()
{
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
}


NA_TCP::~NA_TCP()
{
}
