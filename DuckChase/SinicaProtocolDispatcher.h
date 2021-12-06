#ifndef __SINICAPROTOCOLDISPATCHER_H__
#define __SINICAPROTOCOLDISPATCHER_H__

#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <iostream>

#include "BaseAI.h"
#include "DarkChessPoint.h"
#include "PieceType.h"

using namespace std;

#define BOARD_SIZE 32
#define BOARD_WIDTH 8
#define BOARD_HEIGHT 4

class SinicaProtocolDispatcher
{
public:
	SinicaProtocolDispatcher(BaseAI* ai);
	void start();
	void color();
	void limit( const vector<string>& vCmds );
	void parseBoardFile(char* filename);
	void setWhoFirst();
	bool parseMove( const vector<string>& vCmds );
	void tokenizer( vector<string>& vCmds, const string& sCmd );
	bool isOutsideOfBoard( const DarkChessPoint& point );
	void writeMoveFile( char* filename, const DarkChessPoint& src, const DarkChessPoint& dst );
	int str2int( const string& str );
	string int2str( int i );
	~SinicaProtocolDispatcher(void);
private:
	BaseAI* m_ai;
	int m_iTurn;
	int m_iPieceCount[PIECETYPE_COUNT] ;
	int m_iCurrentBoard[BOARD_SIZE];
	COLOR m_iFirstColor;
	bool m_bFirstFlip;
	map<char, int> m_mPieceValue;
};

#endif