#pragma once
#include <WinSock2.h>
enum socketRole { invalid, client, server };

class NA_NetworkManager
{
private:
	WSADATA wsaData;
	bool ready = false;

public:
	NA_NetworkManager();
	~NA_NetworkManager();
	bool init();
	bool isReady();
	void cleanup();
};

