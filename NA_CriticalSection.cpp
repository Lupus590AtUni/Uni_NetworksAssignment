#include "NA_CriticalSection.h"


NA_CriticalSection::NA_CriticalSection()
{
	//Init is doen in enter/leave as constructers must never fail
}


NA_CriticalSection::~NA_CriticalSection()
{
	//cleaning up memory in a destructor is fine though
	if(ready)
		DeleteCriticalSection(&nativeCritSect);
	//ready = false; //technically probably should but nothing should use the object at this point anyway
}

void NA_CriticalSection::enter()
{
	if(!ready)
		InitializeCriticalSection(&nativeCritSect);
	EnterCriticalSection(&nativeCritSect);
}

void NA_CriticalSection::leave()
{
	if (!ready)
		InitializeCriticalSection(&nativeCritSect);
	LeaveCriticalSection(&nativeCritSect);
}

bool NA_CriticalSection::tryEnter()
{
	if (!ready)
		InitializeCriticalSection(&nativeCritSect);
	return TryEnterCriticalSection(&nativeCritSect);
}

