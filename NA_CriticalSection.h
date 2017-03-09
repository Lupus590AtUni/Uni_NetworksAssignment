#pragma once
#include <Windows.h>

class NA_CriticalSection
{
private:
	CRITICAL_SECTION nativeCritSect;
	bool ready = false;

public:
	NA_CriticalSection();
	~NA_CriticalSection();
	void enter();
	void leave();
};

