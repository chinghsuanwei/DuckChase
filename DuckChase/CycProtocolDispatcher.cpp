#include <sstream>

#include "CycProtocolDispatcher.h"
#include "DarkChessPoint.h"


CycProtocolDispatcher::CycProtocolDispatcher( BaseAI* ai )
:m_eCommunitationType( COMMUNICATIONTYPE_STD ), m_ai(ai)
{

}

CycProtocolDispatcher::CycProtocolDispatcher( BaseAI* ai, char* ip, int port )
:m_eCommunitationType( COMMUNICATIONTYPE_SOCKET ), m_ai(ai)
{
	socket.initSocket( ip, port );
}

void CycProtocolDispatcher::start()
{
	bool bExit = false;
	while( !bExit ){
		string sInput;
		vector<string> vCmds;
		recvCmd( sInput );
		tokenizer( vCmds, sInput );
		dispatch( vCmds, bExit );
	}
}

void CycProtocolDispatcher::start( const vector<string>& vCmds )
{
	m_iSelfSeat = str2int( vCmds[1] );
	m_iWhoFirst = str2int( vCmds[2] );

	int iPieceCount[PIECETYPE_COUNT] = { 1, 2, 2, 2, 2, 2, 5, 1, 2 ,2, 2, 2, 2, 5 };
	int iCurrentPosition[BOARD_SIZE];
	for( int i=0; i<BOARD_SIZE; i++ ) iCurrentPosition[i] = PIECETYPE_COVERED;
	m_ai->initBoardState( iPieceCount, iCurrentPosition );
}

void CycProtocolDispatcher::dispatch(const vector<string>& vCmds, bool& bExit)
{	
	if( vCmds.size() == 0 ) return;

	if( vCmds[0] == "/start" ) start( vCmds );
	else if( vCmds[0] == "/askAction" ) askAction();
	else if( vCmds[0] == "/flip" ) flip( vCmds );
	else if( vCmds[0] == "/move" ) move( vCmds );
	else if( vCmds[0] == "/surrender" ) surrender();
	else if( vCmds[0] == "/color" ) color( vCmds );
	else if( vCmds[0] == "/exit" ) bExit = true;
}

void CycProtocolDispatcher::askAction()
{
	DarkChessPoint from;
	DarkChessPoint to;
	string sAction;
	
	m_ai->generateMove( from, to );

	if( isOutsideOfBoard(from) && isOutsideOfBoard(to) ){
		sAction = "/surrender";
	} else if( isOutsideOfBoard(to) ){
		sAction = "/flip ";
		sAction += int2str(from.x);
		sAction += " ";
		sAction += int2str(from.y);
	} else {
		sAction = "/move ";
		sAction += int2str(from.x);
		sAction += " ";
		sAction += int2str(from.y);
		sAction += " ";
		sAction += int2str(to.x);
		sAction += " ";
		sAction += int2str(to.y);
	}
	/*char input[256];
	cin.getline(input, sizeof input);
	sAction = input;
	Sleep(5000);*/
	sendCmd( sAction );
}

void CycProtocolDispatcher::flip( const vector<string>& vCmds )
{
	DarkChessPoint point;
	
	point.x = str2int( vCmds[1] );
	point.y = str2int( vCmds[2] );
	int iPieceId = str2int( vCmds[3] ) >> CYC_SHIFT_TYPE;
	m_ai->flip( point, iPieceId );
}

void CycProtocolDispatcher::move( const vector<string>& vCmds )
{
	DarkChessPoint from;
	DarkChessPoint to;
	
	from.x = str2int( vCmds[1] );
	from.y = str2int( vCmds[2] );
	to.x = str2int( vCmds[3] );
	to.y = str2int( vCmds[4] );
	m_ai->move( from, to );
}

void CycProtocolDispatcher::surrender()
{

}

void CycProtocolDispatcher::sendCmd( string& str )
{
	if( m_eCommunitationType == COMMUNICATIONTYPE_SOCKET )
		socket << str + "\r\n";
	else{
		cout << str << endl;
	}
}

void CycProtocolDispatcher::recvCmd( string& str )
{
	if( m_eCommunitationType == COMMUNICATIONTYPE_SOCKET )
		socket >> str;
	else{
		//ofstream ofs( "c:\\cycgame\\log\\DuckChase.txt", ofstream::app );
		//ofs << "recv command:" << endl;
		
		getline(cin, str);
		
		//ofs << str << endl;
		if( cin.bad() || cin.fail() ) exit(0);
	}
}

void CycProtocolDispatcher::color( const vector<string>& vCmds )
{
	string sColor = vCmds[1];
	if( sColor == "r" ) m_ai->color( COLOR_RED );
	else if( sColor == "b" ) m_ai->color( COLOR_BLACK );
}

bool CycProtocolDispatcher::isOutsideOfBoard( const DarkChessPoint& point )
{
	if( point.x < 0 || point.y < 0 || point.x >= 8 || point.y >= 4 ) return true;
	else  return false;
}

void CycProtocolDispatcher::tokenizer( vector<string>& vCmds, const string& sCmd )
{
	size_t start = sCmd.find_first_not_of(" \r\n");
	size_t end = sCmd.find_first_of(" \r\n", start+1);
	while( start!=string::npos ){
		vCmds.push_back( sCmd.substr( start, end-start ) );
		start = sCmd.find_first_not_of(" \r\n", end );
		end = sCmd.find_first_of(" \r\n", start+1);
	}
}


int CycProtocolDispatcher::str2int( const string& str )
{
	stringstream ss;
	int i;
	ss << str;
	ss >> i;
	return i;
}

string CycProtocolDispatcher::int2str( int i ){
		stringstream ss;
		string str;
		ss << i;
		ss >> str;
		return str;
}

CycProtocolDispatcher::~CycProtocolDispatcher(void)
{
}
