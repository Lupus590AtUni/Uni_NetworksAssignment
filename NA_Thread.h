#pragma once

//https://msdn.microsoft.com/en-us/library/windows/desktop/ms737629(v=vs.85).aspx
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>


// http://www.flipcode.com/archives/Simple_Win32_Thread_Class.shtml
// http://kaisar-haque.blogspot.co.uk/2007/07/c-nice-thread-class_23.html <- mainly used this one


class NA_Thread //To make a thread, inherit this class and overload threadFunc, information will need to be global (or within the overloading object)
	//threads should check if terminateRequested is true and cleanup and return
	//code will not exit properly if thread doesn't eventually terminate
{
private:
	bool ready = false;
	bool terminateRequested = false;
	
	HANDLE threadHandle = NULL;
	LPDWORD threadID;
	static DWORD WINAPI threadProc(LPVOID lpParameter)
	{
		NA_Thread* t = reinterpret_cast<NA_Thread*> (lpParameter);
		return t->threadFunc();
		
	}

protected:
	virtual DWORD threadFunc() = 0;

public:
	void startThread();
	NA_Thread();
	virtual ~NA_Thread();
	void requestSelfTerminate();
	LPDWORD getExitCode();
	bool waitForTerminate(DWORD milliseconds = INFINITE);
	bool isActive();
};


