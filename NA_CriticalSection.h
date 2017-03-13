#pragma once

//https://msdn.microsoft.com/en-us/library/windows/desktop/ms737629(v=vs.85).aspx
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
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
	bool tryEnter();
};

