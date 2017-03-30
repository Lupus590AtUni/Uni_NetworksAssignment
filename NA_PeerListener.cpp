#include "NA_PeerListener.h"
#include "NA_MessageDefines.h"

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
		iResult = recvfrom(sock, recvbuf, recvbuflen, 0, &sender_addr, &iSenderAddrSize);


		//if message it request to join
			//if we are connected to a gap (or at the loop point)
				//send a reply with the number of the gap
			//else
				//reply with can't help, sorry
	}
	return 0;
}
