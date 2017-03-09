
#include "NA_Timer.h"
#include <time.h>
#ifdef  _WIN32
#include <Windows.h>
#endif



NA_Timer::NA_Timer(double d)
{
	duration = d;
	start = time(NULL);
}

NA_Timer::~NA_Timer(void)
{
}

void NA_Timer::setDuration(double d)
{
	duration = d;
}

bool NA_Timer::hasElapsed()
{
	if(duration < difftime(time(NULL),start))
		return true;
	//else
	return false;
}

void NA_Timer::restart()
{
	start = time(NULL);
}

void NA_Timer::wait()
{
	while (!hasElapsed())
	{
		#ifdef  _WIN32
			Sleep(250*(duration - difftime(time(NULL), start))); //quarter of a second mulitplied by remianing duration (which is in seconds)
		#endif
	}
}
