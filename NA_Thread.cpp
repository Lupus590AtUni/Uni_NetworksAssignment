#include "NA_Thread.h"
#include "globals.h"
#include <iostream>
using std::cerr;

void NA_Thread::startThread()
{
	threadHandle = CreateThread(NULL, 0, threadProc, this, 0, threadID);
}

NA_Thread::NA_Thread()
{
}


NA_Thread::~NA_Thread()
{
	requestSelfTerminate();
	if (threadHandle)
	{
		LPDWORD exitCode = getExitCode();
		if ((DWORD)exitCode == STILL_ACTIVE)
			WaitForSingleObject(threadHandle, INFINITE);
		CloseHandle(threadHandle);
	}
	
}


void NA_Thread::requestSelfTerminate()
{
	terminateRequested = true;
}

LPDWORD NA_Thread::getExitCode()
{
	LPDWORD exitCode;
	if (GetExitCodeThread(threadHandle, exitCode) != 0);
	{
		consoleOutputCritSect.enter();
		cerr << "NA_Thread::Destructor - failed to get thread exit code. Error: " << GetLastError() << "\n";
		consoleOutputCritSect.leave();
	}
	return exitCode;
}

bool NA_Thread::waitForTerminate(DWORD milliseconds)
{
	DWORD w = WaitForSingleObject(threadHandle, milliseconds);
	
	return !(w == WAIT_TIMEOUT); //LOW: Should check for errors https://msdn.microsoft.com/en-us/library/windows/desktop/ms687032(v=vs.85).aspx
}



