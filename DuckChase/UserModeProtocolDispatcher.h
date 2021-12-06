#ifndef __USERMODEPROTOCOLDISPATCHER_H__
#define __USERMODEPROTOCOLDISPATCHER_H__

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "DarkChessPoint.h"
#include "UserModeBoard.h"
#include "BaseAI.h"

using namespace std;

class UserModeProtocolDispatcher
{
public:
	UserModeProtocolDispatcher(BaseAI* ai);
	void init();
	void start();
	bool dispatchUserAction( const string& sCmd );
	void dispatchAIAction();

	bool move( DarkChessPoint& src, DarkChessPoint& dst );
	bool flip( DarkChessPoint& position );
	bool surrender( );

	bool checkMoveFormat( const vector<string>& vCmds, DarkChessPoint& src, DarkChessPoint& dst );
	bool checkFlipFormat( const vector<string>& vCmds, DarkChessPoint& position );
	void tokenizer( vector<string>& vCmds, const string& sCmd );
	bool isInsideOfBoard( int x, int y );
	bool isOutsideOfBoard( const DarkChessPoint& point );
	int str2int( const string& str );
	string int2str( int i );
	~UserModeProtocolDispatcher(void);
private:
	bool m_bUserTurn;
	bool m_bFirstFlip;
	string m_sUserColor;
	string m_sAIColor;
	UserModeBoard board;
	BaseAI* m_ai;
};

#endif