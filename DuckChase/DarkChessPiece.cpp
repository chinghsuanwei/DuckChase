#include "DarkChessPiece.h"
#include "DarkChessBoard.h"

DarkChessBoard* DarkChessPiece::m_pBoard;
DarkChessPiece DarkChessPiece::DARKCHESSPIECE_ILLEGAL( -1, -1 );

DarkChessPiece::DarkChessPiece(void)
{
}

DarkChessPiece::DarkChessPiece( PIECETYPE ePieceType, int iCord )
{
	this->m_eType = ePieceType;
	this->m_iCord = iCord;
}

void  DarkChessPiece::setBoard( DarkChessBoard* pBoard)
{
	m_pBoard = pBoard;
}

bool DarkChessPiece::isAtLeftBorder( )
{
	//cord%8
	return (m_iCord & 0x07) == 0;
}

bool DarkChessPiece::isAtRightBorder( )
{
	return ((m_iCord+1) & 0x07) == 0;
}

bool DarkChessPiece::isOnTheCeiling( )
{
	return m_iCord < BOARD_WIDTH;
}

bool DarkChessPiece::isOnTheFloor( )
{
	return (m_iCord + BOARD_WIDTH) >= BOARD_SIZE;
}

bool DarkChessPiece::isInsideOfBoard() const 
{ 
	return m_iCord >= 0 && m_iCord < BOARD_SIZE; 
}

bool DarkChessPiece::isOutsideOfBoard() const
{ 
	return !isInsideOfBoard(); 
}

DarkChessPiece& DarkChessPiece::getUp()
{
	if( isOnTheCeiling() ) return DARKCHESSPIECE_ILLEGAL;
	else return m_pBoard->at( m_iCord - BOARD_WIDTH );
}

DarkChessPiece& DarkChessPiece::getDown()
{
	if( isOnTheFloor() ) return DARKCHESSPIECE_ILLEGAL;
	else return m_pBoard->at( m_iCord + BOARD_WIDTH );
}

DarkChessPiece& DarkChessPiece::getLeft()
{
	if( isAtLeftBorder() ) return DARKCHESSPIECE_ILLEGAL;
	else return m_pBoard->at( m_iCord - 1 );
}

DarkChessPiece& DarkChessPiece::getRight()
{
	if( isAtRightBorder() ) return DARKCHESSPIECE_ILLEGAL;
	else return m_pBoard->at( m_iCord + 1 );
}

bool DarkChessPiece::canMoveUp( DarkChessPiece& target )
{
	if( this->isOnTheCeiling() ) return false;

	target = this->getUp();
	
	if( target.isVacancy() ) return true; //上面為空地 所以可往上走
	if( target.isCovered() ) return false; //上面為覆蓋子 不能走

	if( this->isSameColor( target ) ) return false; // 同顏色 不能走
	if( this->canEatByMove( target ) ) return true; // 可以吃
	else return false;
}

bool DarkChessPiece::canMoveDown( DarkChessPiece& target )
{
	if( this->isOnTheFloor() ) return false;

	target = this->getDown();

	if( target.isVacancy() ) return true; //上面為空地 所以可往上走
	if( target.isCovered() ) return false;

	if( this->isSameColor( target ) ) return false; // 同顏色 不能走
	if( this->canEatByMove( target ) ) return true; // 可以吃
	else return false;
}

bool DarkChessPiece::canMoveLeft( DarkChessPiece& target )
{
	if( this->isAtLeftBorder() ) return false;

	target = this->getLeft();

	if( target.isVacancy() ) return true; //上面為空地 所以可往上走
	if( target.isCovered() ) return false;

	if( this->isSameColor( target ) ) return false; // 同顏色 不能走
	if( this->canEatByMove( target ) ) return true; // 可以吃
	else return false;
}

bool DarkChessPiece::canMoveRight( DarkChessPiece& target )
{
	if( this->isAtRightBorder() ) return false;

	target = this->getRight();

	if( target.isVacancy() ) return true; //上面為空地 所以可往上走
	if( target.isCovered() ) return false;

	if( this->isSameColor( target ) ) return false; // 同顏色 不能走
	if( this->canEatByMove( target ) ) return true; // 可以吃
	else return false;
}

bool DarkChessPiece::canJumpUp( DarkChessPiece& target )
{
	target = findUpSecondPiece();
	// 1. insideOfBoard		2. isNotCovered		3. isDifferentColor
	if( target.isInsideOfBoard() && target.isNotCovered() && this->isDifferentColor(target) ) return true;
	else return false;
}

DarkChessPiece& DarkChessPiece::findUp( )
{
	DarkChessPiece& target = getUp();
	if( target.isOutsideOfBoard() ) return DARKCHESSPIECE_ILLEGAL;
	else{
		if( target.isOccupy() ) return target;
		else return target.findUp( );
	}
}

DarkChessPiece& DarkChessPiece::findUpSecondPiece()
{
	DarkChessPiece& fort = findUp();
	if( fort.isOutsideOfBoard() ) return DARKCHESSPIECE_ILLEGAL;

	DarkChessPiece& target = fort.findUp();
	if( target.isOutsideOfBoard() ) return DARKCHESSPIECE_ILLEGAL;

	return target;
}

bool DarkChessPiece::canJumpDown( DarkChessPiece& target )
{
	target = findDownSecondPiece();
	// 1. insideOfBoard		2. isNotCovered		3. isDifferentColor
	if( target.isInsideOfBoard() && target.isNotCovered() && this->isDifferentColor(target) ) return true;
	else return false;
}

DarkChessPiece& DarkChessPiece::findDown( )
{
	DarkChessPiece& target = getDown();
	if( target.isOutsideOfBoard() ) return DARKCHESSPIECE_ILLEGAL;
	else{
		if( target.isOccupy() ) return target;
		else return target.findDown( );
	}
}

DarkChessPiece& DarkChessPiece::findDownSecondPiece()
{
	DarkChessPiece& fort = findDown();
	if( fort.isOutsideOfBoard() ) return DARKCHESSPIECE_ILLEGAL;

	DarkChessPiece& target = fort.findDown();
	if( target.isOutsideOfBoard() ) return DARKCHESSPIECE_ILLEGAL;

	return target;
}


bool DarkChessPiece::canJumpLeft( DarkChessPiece& target )
{	
	target = findLeftSecondPiece();
	// 1. insideOfBoard		2. isNotCovered		3. isDifferentColor
	if( target.isInsideOfBoard() && target.isNotCovered() && this->isDifferentColor(target) ) return true;
	else return false;
}

DarkChessPiece& DarkChessPiece::findLeft( )
{
	DarkChessPiece& target = getLeft();
	if( target.isOutsideOfBoard() ) return DARKCHESSPIECE_ILLEGAL;
	else{
		if( target.isOccupy() ) return target;
		else return target.findLeft( );
	}
}

DarkChessPiece& DarkChessPiece::findLeftSecondPiece()
{
	DarkChessPiece& fort = findLeft();
	if( fort.isOutsideOfBoard() ) return DARKCHESSPIECE_ILLEGAL;

	DarkChessPiece& target = fort.findLeft();
	if( target.isOutsideOfBoard() ) return DARKCHESSPIECE_ILLEGAL;

	return target;
}


bool DarkChessPiece::canJumpRight( DarkChessPiece& target )
{
	target = findRightSecondPiece();
	// 1. insideOfBoard		2. isNotCovered		3. isDifferentColor
	if( target.isInsideOfBoard() && target.isNotCovered() && this->isDifferentColor(target) ) return true;
	else return false;
}

DarkChessPiece& DarkChessPiece::findRight( )
{
	DarkChessPiece& target = getRight();
	if( target.isOutsideOfBoard() ) return DARKCHESSPIECE_ILLEGAL;
	else{
		if( target.isOccupy() ) return target;
		else return target.findRight( );
	}
}

DarkChessPiece& DarkChessPiece::findRightSecondPiece()
{
	DarkChessPiece& fort = findRight();
	if( fort.isOutsideOfBoard() ) return DARKCHESSPIECE_ILLEGAL;

	DarkChessPiece& target = fort.findRight();
	if( target.isOutsideOfBoard() ) return DARKCHESSPIECE_ILLEGAL;

	return target;
}


bool DarkChessPiece::canEatByMove( DarkChessPiece& target ) const
{
	if( isSameColor(target) ) return false;

	if( this->isPawn() ){ // 兵卒
		if( target.isPawn() || target.isKing() ) return true;
		else return false;
	} else if( this->isCannon() ) return false; //包炮
	else if( this->isKing() ){ //將帥
		if( target.isPawn() ) return false;
		else return true;
	} else {
		// 將顏色排除之後 比較棋力大小(kind編號越小 棋力越大) 
		if( this->getKind() <= target.getKind() ) return true;
		else return false;
	}
}

DarkChessPiece::~DarkChessPiece(void)
{
}
