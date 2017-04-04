#pragma once
#include "NA_NetworkManager.h"
#include "NA_Message.h"
class NA_Socket
{
private:
	SOCKET sock;

public:
	static enum MODE {NOT_SET, UDP, TCP};
	NA_Socket();
	~NA_Socket();
	bool init(MODE mode);
};

