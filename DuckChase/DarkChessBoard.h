#ifndef __DARKCHESSBOARD_H__
#define __DARKCHESSBOARD_H__

#include <iostream>
#include <fstream>

#include "DarkChessPiece.h"
#include "DarkChessPoint.h"

using namespace std;

#define BOARD_HEIGHT 4
#define BOARD_WIDTH 8
#define BOARD_SIZE 32

class DarkChessBoard
{
public:
	DarkChessBoard(void);
	void initBoardState( int iCurrentBoard[BOARD_SIZE] );
	void move( const DarkChessPoint& from, const DarkChessPoint& to );
	void flip( const DarkChessPoint& point, int iType );

	inline DarkChessPiece& at( const DarkChessPoint& point ){
		return m_board[ point.y*BOARD_WIDTH + point.x ];
	}
	inline DarkChessPiece& at( int x, int y ){
		return m_board[ y*BOARD_WIDTH + x ];
	}
	inline DarkChessPiece& at( int cord ){
		return m_board[ cord ];
	}
	void showBoard(ostream& out);
	~DarkChessBoard(void);
public:
	DarkChessPiece m_board[BOARD_SIZE];
};

#endif