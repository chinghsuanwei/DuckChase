#include "UserModeProtocolDispatcher.h"


UserModeProtocolDispatcher::UserModeProtocolDispatcher(BaseAI* ai)
{
	m_ai = ai;
}

void UserModeProtocolDispatcher::init()
{
	m_bFirstFlip = true;
	m_sUserColor = "none";
	m_sAIColor = "none";
	
	int iPieceCount[PIECETYPE_COUNT] = { 1, 2, 2, 2, 2, 2, 5, 1, 2 ,2, 2, 2, 2, 5 };
	int iCurrentPosition[BOARD_SIZE];
	for( int i=0; i<BOARD_SIZE; i++ ) iCurrentPosition[i] = PIECETYPE_COVERED;
	m_ai->initBoardState( iPieceCount, iCurrentPosition );

	cout << "Welcome to AI-to-User Mode" << endl;
	cout << "You want play first? [y or n] ";
	string sYesOrNo;
	getline( cin, sYesOrNo );
	if( sYesOrNo[0] == 'y' || sYesOrNo[0] == 'Y' ) m_bUserTurn = true;
	else m_bUserTurn = false;
}

void UserModeProtocolDispatcher::start()
{
	init();
	while( true )
	{
		board.showBoard();

		if( m_bUserTurn ){
			// User's Turn

			cout << "Your turn " << "[" << m_sUserColor << "]" <<  " :" ;
			string sCmd;
			getline( cin, sCmd );

			if ( !dispatchUserAction( sCmd ) ) continue; //«ü¥O¿ù»~

		} else {

			// AI's Turn
			DarkChessPoint src;
			DarkChessPoint dst;
			cout << "AI turn " << "[" << m_sAIColor << "]" <<  " :" ;
			m_ai->generateMove( src, dst );
			if( isOutsideOfBoard( src ) && isOutsideOfBoard( dst ) ) {
				surrender();
				break;
			} else if( isOutsideOfBoard( dst ) ){
				cout << "F " << src.x << " " << src.y << endl;
				flip( src );
			} else{
				cout << "M " << src.x << " " << src.y << " " << dst.x << " " << dst.y  << endl;
				move( src, dst );
			}
		}

		m_bUserTurn = !m_bUserTurn;
	}
}

bool UserModeProtocolDispatcher::dispatchUserAction( const string& sCmd )
{
	vector<string> vCmds;
	tokenizer( vCmds, sCmd );

	if( vCmds.size() == 0 ) return false;

	if( vCmds[0] == "M" || vCmds[0] == "m" ){
		DarkChessPoint src;
		DarkChessPoint dst;
		if( checkMoveFormat( vCmds, src, dst ) ) return move( src, dst );

	} else if( vCmds[0] == "F" || vCmds[0] == "f"){
		DarkChessPoint position;
		if( checkFlipFormat( vCmds, position ) ) return flip( position );

	} else if( vCmds[0] == "S" || vCmds[0] == "s" ){
		return surrender();

	} else{
		cout << "Unknown Command \"" << vCmds[0] << "\"" << endl;
	}

	return false;
}

void UserModeProtocolDispatcher::tokenizer( vector<string>& vCmds, const string& sCmd )
{
	size_t start = sCmd.find_first_not_of(" \r\n");
	size_t end = sCmd.find_first_of(" \r\n", start+1);
	while( start!=string::npos ){
		vCmds.push_back( sCmd.substr( start, end-start ) );
		start = sCmd.find_first_not_of(" \r\n", end );
		end = sCmd.find_first_of(" \r\n", start+1);
	}
}

bool UserModeProtocolDispatcher::checkMoveFormat( const vector<string>& vCmds, DarkChessPoint& src, DarkChessPoint& dst )
{
	if( vCmds.size() != 5 ) {
		cout << "===Format Error: M [x1] [y1] [x2] [y2] ===" << endl;
		return false;
	}

	int x1 = str2int( vCmds[1] );
	int y1 = str2int( vCmds[2] );
	int x2 = str2int( vCmds[3] );
	int y2 = str2int( vCmds[4] );

	if( isInsideOfBoard( x1, y1 ) && isInsideOfBoard( x2, y2 ) ){
		src.x = x1;
		src.y = y1;
		dst.x = x2;
		dst.y = y2;
		return true;
	} else {
		cout << "===Number Format Error: M [x1] [y1] [x2] [y2] ===" << endl;
		return false;
	}
}

bool UserModeProtocolDispatcher::checkFlipFormat( const vector<string>& vCmds, DarkChessPoint& position )
{
	if( vCmds.size() != 3 ){
		cout << "===Format Error: F [x1] [y1] ===" << endl;
		return false;
	}

	int x1 = str2int( vCmds[1] );
	int y1 = str2int( vCmds[2] );

	if( isInsideOfBoard( x1, y1 ) ){
		position.x = x1;
		position.y = y1;
		return true;
	} else {
		cout << "===Number Format Error: F [x1] [y1] ===" << endl;
		return false;
	}
}

bool UserModeProtocolDispatcher::move( DarkChessPoint& src, DarkChessPoint& dst )
{
	board.move( src, dst );
	m_ai->move( src, dst );
	return true;
}

bool UserModeProtocolDispatcher::flip( DarkChessPoint& position )
{
	board.flip( position );
	int iType = board.m_board[ position.y*BOARD_WIDTH + position.x ].m_iPieceType;
	m_ai->flip( position, iType );
	if( m_bFirstFlip ){
		int iColor = (iType & FILTER_COLOR) >> SHIFT_COLOR;
		if( m_bUserTurn ) m_ai->color( !iColor );
		else m_ai->color( iColor );
		
		if( (iColor == COLOR_BLACK) ^ m_bUserTurn ){
			m_sUserColor = "red";
			m_sAIColor = "black";
		} else {
			m_sUserColor = "black";
			m_sAIColor = "red";
		}
		m_bFirstFlip = false;
	}
	return true;
}

bool UserModeProtocolDispatcher::surrender( )
{
	return true;
}

bool UserModeProtocolDispatcher::isOutsideOfBoard( const DarkChessPoint& point )
{
	if( point.x < 0 || point.y < 0 || point.x >= 8 || point.y >= 4 ) return true;
	else  return false;
}

bool UserModeProtocolDispatcher::isInsideOfBoard( int x, int y )
{
	if(x >= 0 && y >= 0 && x < 8 && y < 4 ) return true;
	else  return false;
}

int UserModeProtocolDispatcher::str2int( const string& str )
{
	stringstream ss;
	int i;
	ss << str;
	ss >> i;
	return i;
}

string UserModeProtocolDispatcher::int2str( int i )
{
		stringstream ss;
		string str;
		ss << i;
		ss >> str;
		return str;
}


UserModeProtocolDispatcher::~UserModeProtocolDispatcher(void)
{
}
