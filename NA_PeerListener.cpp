#include "NA_PeerListener.h"


NA_PeerListener::NA_PeerListener()
{
}


NA_PeerListener::~NA_PeerListener()
{
}

DWORD NA_PeerListener::threadFunc()
{
	while (!terminateRequested)
	{
		//Listen for and reply to peer connections

	}
	return 0;
}
