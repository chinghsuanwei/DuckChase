#ifndef __BASEAI_H__
#define __BASEAI_H__

#include "string"

#include "PieceType.h"
#include "DarkChessPoint.h"

#define BOARD_SIZE 32

using namespace std;

class BaseAI
{
public:
	virtual void initBoardState( int iPieceCount[PIECETYPE_COUNT], int iCurrentPosition[BOARD_SIZE] ) = 0;
	virtual void generateMove( DarkChessPoint& src, DarkChessPoint& dst ) = 0;
	virtual void move( const DarkChessPoint& src, const DarkChessPoint& dst ) = 0;
	virtual void flip( const DarkChessPoint& position, int iType ) = 0;
	virtual void color( int c ) = 0;
	virtual void limit( int ms ) = 0;
public:
	string m_sComment;
};

#endif

