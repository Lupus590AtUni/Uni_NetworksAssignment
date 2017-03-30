#pragma once
#include <WinSock2.h>
#include <string>
using std::string;

class NA_Message
{
public:
	NA_Message();
	~NA_Message();
	string str;
	sockaddr senderAddress;
	sockaddr destinationAddress;
};

