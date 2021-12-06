#include "DarkChessAI.h"

#include <ctime>
#include <Windows.h>

DarkChessAI::DarkChessAI(void)
:m_eColor(COLOR_INIT)
{
	srand( static_cast<unsigned int>( time(NULL)));
}

void DarkChessAI::initBoardState( int iPieceCount[PIECETYPE_COUNT], int iCurrentState[BOARD_SIZE] )
{
	getBoard()->initBoardState( iCurrentState );
}

void DarkChessAI::generateMove( DarkChessPoint& from, DarkChessPoint& to )
{
	vector< pair<DarkChessPoint, DarkChessPoint> > Vector;
	
	for(int i=0; i<BOARD_SIZE; i++ ){
		DarkChessPiece source = m_darkChessBoard.m_board[i];

		if ( source.isVacancy() ){ //空地
			
		} else if( source.isCovered() ){ //覆蓋得棋子
			DarkChessPoint first;
			DarkChessPoint second;

			first.x = i & 0x00000007; // 等同於%8
			first.y = i >> 3; // 等同於/8
			second.x = -1;
			second.y = -1;

			Vector.push_back( make_pair( first, second ) );

		} else if ( source.isSameColor(m_eColor) ){ //我方棋子
			DarkChessPiece target;

			if( source.isCannon() ){ //炮
				if( source.canJumpUp( target ) ){ // 可以往上跳
					Vector.push_back( make_pair( source.getPoint(), target.getPoint() ) );
				}
				if( source.canJumpDown( target ) ){
					Vector.push_back( make_pair( source.getPoint(), target.getPoint() ) );
				}
				if( source.canJumpLeft( target ) ){
					Vector.push_back( make_pair( source.getPoint(), target.getPoint() ) );
				}
				if( source.canJumpRight( target ) ){
					Vector.push_back( make_pair( source.getPoint(), target.getPoint() ) );
				}
			}

			if( source.canMoveUp( target ) ){ // 可以往上走
				Vector.push_back( make_pair( source.getPoint(), target.getPoint() ) );
			}
			if( source.canMoveDown( target ) ){
				Vector.push_back( make_pair( source.getPoint(), target.getPoint() ) );
			}
			if( source.canMoveLeft( target ) ){
				Vector.push_back( make_pair( source.getPoint(), target.getPoint() ) );
			}
			if( source.canMoveRight( target ) ){
				Vector.push_back( make_pair( source.getPoint(), target.getPoint() ) );
			}

		}
	} // end for
	
	//random choose
	if( Vector.size() == 0 ){
		from = DarkChessPoint( -1, -1 );
		to = DarkChessPoint( -1, -1 );
	} else {
		int random = rand() % Vector.size();
		from = Vector[ random ].first;
		to = Vector[ random ].second;
	}
	
	//目前只有Sinica有用到m_sComment
	m_sComment = "src = ";
	m_sComment += int2str( from.x );
	m_sComment += " ";
	m_sComment += int2str( from.y );

	m_sComment += ", dst= ";
	m_sComment += int2str( to.x );
	m_sComment += " ";
	m_sComment += int2str( to.y );

	//Sleep(10000);
}

string DarkChessAI::int2str( int i )
{
		stringstream ss;
		string str;
		ss << i;
		ss >> str;
		return str;
}

bool DarkChessAI::isMyColor(PIECETYPE ePieceType )
{	
	COLOR eColor = (ePieceType & FILTER_COLOR) >> SHIFT_COLOR;
	if( m_eColor == eColor ) return true;
	else return false;
}

void DarkChessAI::move( const DarkChessPoint& src, const DarkChessPoint& dst )
{
	getBoard()->move( src, dst );
}

void DarkChessAI::flip( const DarkChessPoint& position, int iType )
{
	getBoard()->flip( position, iType );
}

void DarkChessAI::limit( int ms )
{
}

DarkChessBoard* DarkChessAI::getBoard()
{
	return &m_darkChessBoard;
}

void DarkChessAI::color( COLOR eColor )
{
	m_eColor = eColor;
}

void DarkChessAI::showBoard(ostream& out)
{
	getBoard()->showBoard(out);
}

DarkChessAI::~DarkChessAI(void)
{
}
