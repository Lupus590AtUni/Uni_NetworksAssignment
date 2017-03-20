#pragma once
#include "NA_NetworkManager.h"

extern NA_NetworkManager na_networkManager;

class NA_TCP : 	public NA_Thread
{
	friend class NA_NetworkManager;

public:
	NA_TCP();
	~NA_TCP();
};

