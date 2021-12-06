#include "UserModeBoard.h"

UserModeBoard::UserModeBoard(void)
{
	//將暗棋盤面上所有棋子設為Covered 並指定一個Type
	for( int i=0; i<BOARD_SIZE; i++){
		m_board[i].bCovered = true;
		m_board[i].m_iPieceType = PIECES[i];
	}

	//覆蓋著棋子洗牌
	random_shuffle(m_board, m_board + BOARD_SIZE);
}

void UserModeBoard::move( const DarkChessPoint& from, const DarkChessPoint& to )
{
	int iFromIndex = from.y*BOARD_WIDTH + from.x;
	int iToIndex = to.y*BOARD_WIDTH + to.x;

	int iFromType = m_board[ iFromIndex ].m_iPieceType;
	m_board[ iFromIndex ].m_iPieceType = PIECETYPE_NONE;
	m_board[ iToIndex ].m_iPieceType = iFromType;
}

void UserModeBoard::flip( const DarkChessPoint& position )
{
	int iPositionIndex = position.y*BOARD_WIDTH + position.x;

	m_board[ iPositionIndex ].bCovered = false;
}


void UserModeBoard::showBoard()
{
	int index = 0;
	for(int i=0; i<BOARD_HEIGHT; i++){ //outer for
		for(int j=0; j<BOARD_WIDTH; j++){ //inner for

			if( m_board[ index ].bCovered ) cout << "●";
			else{
				switch( m_board[ index ].m_iPieceType ){
					case PIECETYPE_BLACK_KING: cout << "將"; break;
					case PIECETYPE_BLACK_ADVISER: cout << "士"; break;
					case PIECETYPE_BLACK_ELEPHANT: cout << "象"; break;
					case PIECETYPE_BLACK_CHARIOT: cout << "車"; break;
					case PIECETYPE_BLACK_HORSE: cout << "馬"; break;
					case PIECETYPE_BLACK_CANNON: cout << "包"; break;
					case PIECETYPE_BLACK_PAWN: cout << "卒"; break;
				
					case PIECETYPE_RED_KING: cout << "帥"; break;
					case PIECETYPE_RED_ADVISER: cout << "仕"; break;
					case PIECETYPE_RED_ELEPHANT: cout << "相"; break;
					case PIECETYPE_RED_CHARIOT: cout << "硨"; break;  
					case PIECETYPE_RED_HORSE: wcout << "傌"; break; 
					case PIECETYPE_RED_CANNON: cout << "炮"; break; 
					case PIECETYPE_RED_PAWN: cout << "兵"; break;

					case PIECETYPE_NONE: cout << "○"; break;
					default: cout << "？"; break;
				}
			}


			cout << " ";
			index++;
		}//inner for end
		cout << endl;
	}//outer for end
}

UserModeBoard::~UserModeBoard(void)
{
}