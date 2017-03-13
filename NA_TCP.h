#pragma once
#include "NA_NetworkManager.h"

class NA_TCP : 	public NA_Thread
{
	friend class NA_NetworkManager;

public:
	NA_TCP();
	~NA_TCP();
};

