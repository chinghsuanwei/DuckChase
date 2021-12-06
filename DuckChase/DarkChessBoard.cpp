#include "DarkChessBoard.h"

DarkChessBoard::DarkChessBoard(void)
{
	//將暗棋盤面initialize成 全部為UNKNOWN棋子
	for( int i=0; i<BOARD_SIZE; i++){
		m_board[i].setType( PIECETYPE_COVERED );
		m_board[i].setCordinate( i );
	}

	DarkChessPiece::setBoard(this);
}

void DarkChessBoard::initBoardState( int iCurrentBoard[BOARD_SIZE] )
{
	for( int i=0; i<BOARD_SIZE; i++){
		m_board[i].setType( iCurrentBoard[i] );
		m_board[i].setCordinate( i );
	}
}

void DarkChessBoard::move( const DarkChessPoint& from, const DarkChessPoint& to )
{
	PIECETYPE fromType = this->at(from).getType();
	this->at(from).setType( PIECETYPE_NONE );
	this->at(to).setType( fromType );
}

void DarkChessBoard::flip( const DarkChessPoint& point, int iType )
{
	this->at(point).setType(iType);
}


void DarkChessBoard::showBoard(ostream& out)
{
	for(int i=0; i<BOARD_HEIGHT; i++){
		for(int j=0; j<BOARD_WIDTH; j++){
			switch( m_board[i*BOARD_WIDTH + j].getType() ){
				case PIECETYPE_BLACK_KING: out << "將"; break;
				case PIECETYPE_BLACK_ADVISER: out << "士"; break;
				case PIECETYPE_BLACK_ELEPHANT: out << "象"; break;
				case PIECETYPE_BLACK_CHARIOT: out << "車"; break;
				case PIECETYPE_BLACK_HORSE: out << "馬"; break;
				case PIECETYPE_BLACK_CANNON: out << "包"; break;
				case PIECETYPE_BLACK_PAWN: out << "卒"; break;
				
				case PIECETYPE_RED_KING: out << "帥"; break;
				case PIECETYPE_RED_ADVISER: out << "仕"; break;
				case PIECETYPE_RED_ELEPHANT: out << "相"; break;
				case PIECETYPE_RED_CHARIOT: out << "硨"; break;
				case PIECETYPE_RED_HORSE: out << "傌"; break;
				case PIECETYPE_RED_CANNON: out << "炮"; break;
				case PIECETYPE_RED_PAWN: out << "兵"; break;

				case PIECETYPE_NONE: out << "○"; break;
				case PIECETYPE_COVERED: out << "●"; break;
				default: out << "？"; break;
			}
			out << " ";
		}
		out << endl;
	}
}

DarkChessBoard::~DarkChessBoard(void)
{
}
