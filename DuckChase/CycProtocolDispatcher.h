#ifndef __CYCPROTOCOLDISPATCHER_H__
#define __CYCPROTOCOLDISPATCHER_H__

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "ClientSocket.h"
#include "BaseAI.h"

using namespace std;

class CycProtocolDispatcher
{
	enum CommunitationType{
		COMMUNICATIONTYPE_STD,
		COMMUNICATIONTYPE_SOCKET
	};
public:
	CycProtocolDispatcher( BaseAI* ai );
	CycProtocolDispatcher( BaseAI* ai, char* ip, int port );
	void initialize( ClientSocket* socket );
	void start();
	void start( const vector<string>& vCmds );
	void dispatch( const vector<string>& vCmds, bool& bExit);
	void askAction();
	void flip( const vector<string>& vCmds );
	void move( const vector<string>& vCmds );
	void surrender();
	void color( const vector<string>& vCmds);
	void sendCmd( string& str );
	void recvCmd( string& str );
	void tokenizer( vector<string>& vCmds, const string& sCmd );
	bool isOutsideOfBoard( const DarkChessPoint& point );
	int str2int( const string& str );
	string int2str( int i );
	~CycProtocolDispatcher(void);
private:
	int m_iSelfSeat;
	int m_iWhoFirst;
	BaseAI* m_ai;
	ClientSocket socket;
	CommunitationType m_eCommunitationType;
};

#endif