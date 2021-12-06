#ifndef __DARKCHESSPIECE_H__
#define __DARKCHESSPIECE_H__

#include <string>
#include <assert.h>

#include "PieceType.h"
#include "DarkChessPoint.h"

using namespace std;

/*
int BLACK_KING1 = 0;//將
int BLACK_ADVISER1 = 8;//士
int BLACK_ADVISER2 = 9;//士
int BLACK_ELEPHANT1 = 16;//象
int BLACK_ELEPHANT2 = 17;//象
int BLACK_CHARIOT1 = 24;//車
int BLACK_CHARIOT2 = 25;//車
int BLACK_HORSE1 = 32;//馬
int BLACK_HORSE2 = 33;//馬
int BLACK_CANNON1 = 40;//包
int BLACK_CANNON2 = 41;//包
int BLACK_PAWN1 = 48;//卒
int BLACK_PAWN2 = 49;//卒
int BLACK_PAWN3 = 50;//卒
int BLACK_PAWN4 = 51;//卒
int BLACK_PAWN5 = 52;//卒

int RED_KING1 = 64;//帥
int RED_ADVISER1 = 72;//仕
int RED_ADVISER2 = 73;//仕
int RED_ELEPHANT1 = 80;//相
int RED_ELEPHANT2 = 81;//相
int RED_CHARIOT1 = 88;//人車
int RED_CHARIOT2 = 89;//人車
int RED_HORSE1 = 96;//人馬
int RED_HORSE2 = 97;//人馬
int RED_CANNON1 = 104;//炮
int RED_CANNON2 = 105;//炮
int RED_PAWN1 = 112;//兵
int RED_PAWN2 = 113;//兵
int RED_PAWN3 = 114;//兵
int RED_PAWN4 = 115;//兵
int RED_PAWN5 = 116;//兵
*/

//const int PIECETYPE_BLACK_KING = 0; //將
//const int PIECETYPE_BLACK_ADVISER = 1; //士
//const int PIECETYPE_BLACK_ELEPHANT = 2; //象
//const int PIECETYPE_BLACK_CHARIOT = 3; //車
//const int PIECETYPE_BLACK_HORSE = 4; //馬
//const int PIECETYPE_BLACK_CANNON = 5; //包
//const int PIECETYPE_BLACK_PAWN = 6; //卒
//
//const int PIECETYPE_NONE = 7; 
//
//const int PIECETYPE_RED_KING = 8; //帥
//const int PIECETYPE_RED_ADVISER = 9; //人仕
//const int PIECETYPE_RED_ELEPHANT = 10; //人相
//const int PIECETYPE_RED_CHARIOT = 11; //人車
//const int PIECETYPE_RED_HORSE = 12; //人馬
//const int PIECETYPE_RED_CANNON = 13; //炮
//const int PIECETYPE_RED_PAWN = 14; //兵

//const int PIECETYPE_COVERED = 15; //未知的覆蓋棋子

class DarkChessBoard;

class DarkChessPiece
{
public:
	static void setBoard( DarkChessBoard* pBoard );
private:
	static DarkChessPiece DARKCHESSPIECE_ILLEGAL;
	static DarkChessBoard* m_pBoard;
public:
	DarkChessPiece(void);
	DarkChessPiece( PIECETYPE ePieceType, int iCord );
	inline PIECETYPE getType() const { return m_eType; }
	inline DarkChessPoint getPoint() const {
		DarkChessPoint point;
		point.x = m_iCord & 0x07; // m_iCord%8
		point.y = m_iCord >> 3; // m_iCord/8
		return point;
	}
	inline void setType( PIECETYPE eType ) { m_eType = eType; }
	inline void setCordinate( int iCord ) { m_iCord = iCord; }
	inline bool isVacancy() const { return m_eType == PIECETYPE_NONE; }
	inline bool isOccupy() const { return m_eType != PIECETYPE_NONE; }

	inline bool isCovered() const { 
		assert( m_eType != PIECETYPE_NONE );
		return m_eType == PIECETYPE_COVERED; 
	}
	inline bool isNotCovered() const { return !isCovered(); }

	inline bool isKing() const { return  (m_eType & FILTER_KIND) == PIECETYPE_KING; }
	inline bool isCannon() const { return (m_eType & FILTER_KIND) == PIECETYPE_CANNON; }
	inline bool isPawn() const { return  (m_eType & FILTER_KIND) == PIECETYPE_PAWN; }
	inline bool isSameColor ( COLOR eColor ) const { return ((m_eType & FILTER_COLOR) >> SHIFT_COLOR) == eColor; }
	inline bool isSameColor ( const DarkChessPiece& target ) const {
		COLOR eMyColor = (m_eType & FILTER_COLOR) >> SHIFT_COLOR;
		COLOR eTargetColor = (target.getType() & FILTER_COLOR) >> SHIFT_COLOR;
		return eMyColor == eTargetColor;
	}
	inline bool isDifferentColor( COLOR eColor ) const { return !isSameColor( eColor ); }
	inline bool isDifferentColor( const DarkChessPiece& target ) const { return !isSameColor( target ); }

	inline bool isInsideOfBoard() const;
	inline bool isOutsideOfBoard() const;
	
	inline int getKind() const { return m_eType & FILTER_KIND; }

	inline bool isAtLeftBorder( );
	inline bool isAtRightBorder( );
	inline bool isOnTheCeiling( );
	inline bool isOnTheFloor( );

	DarkChessPiece& getUp();
	DarkChessPiece& getDown();
	DarkChessPiece& getLeft();
	DarkChessPiece& getRight();

	//recursively find
	DarkChessPiece& findUp( );
	DarkChessPiece& findDown( );
	DarkChessPiece& findLeft( );
	DarkChessPiece& findRight( );

	bool canMoveUp( DarkChessPiece& target );
	bool canMoveDown( DarkChessPiece& target );
	bool canMoveLeft( DarkChessPiece& target );
	bool canMoveRight( DarkChessPiece& target );

	bool canJumpUp( DarkChessPiece& target );
	DarkChessPiece& findUpSecondPiece();

	bool canJumpDown( DarkChessPiece& target );
	DarkChessPiece& findDownSecondPiece();

	bool canJumpLeft( DarkChessPiece& target );
	DarkChessPiece& findLeftSecondPiece();

	bool canJumpRight( DarkChessPiece& target );
	DarkChessPiece& findRightSecondPiece();


	bool canEatByMove( DarkChessPiece& target ) const;
	~DarkChessPiece(void);

private:
	PIECETYPE m_eType;
	int m_iCord;
};

#endif