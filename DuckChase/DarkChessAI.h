#ifndef __DARKCHESSAI_H__
#define __DARKCHESSAI_H__

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#include "BaseAI.h"
#include "PieceType.h"
#include "DarkChessBoard.h"
#include "DarkChessPiece.h"

using namespace std;

class DarkChessAI : public BaseAI
{
public:
	DarkChessAI(void);
	void initBoardState( int iPieceCount[PIECETYPE_COUNT], int iCurrentState[BOARD_SIZE] );
	void generateMove( DarkChessPoint& src, DarkChessPoint& dst );
	void move( const DarkChessPoint& src, const DarkChessPoint& dst );
	string int2str( int i );
	void flip( const DarkChessPoint& position, int iType );
	void color( int c );
	void limit( int ms );

	DarkChessBoard* getBoard();
	int transferCycPieceId( int iCycPieceId );
	bool isMyColor(PIECETYPE ePieceType );
	void showBoard(ostream& out);
	~DarkChessAI(void);
private:
	COLOR m_eColor;
	DarkChessBoard m_darkChessBoard;
};

#endif