#include "SinicaProtocolDispatcher.h"


SinicaProtocolDispatcher::SinicaProtocolDispatcher(BaseAI* ai)
{
	m_ai = ai;
	m_iTurn = 0;

	m_mPieceValue['k'] = PIECETYPE_BLACK_KING;
	m_mPieceValue['g'] = PIECETYPE_BLACK_ADVISER;
	m_mPieceValue['m'] = PIECETYPE_BLACK_ELEPHANT;
	m_mPieceValue['r'] = PIECETYPE_BLACK_CHARIOT;
	m_mPieceValue['n'] = PIECETYPE_BLACK_HORSE;
	m_mPieceValue['c'] = PIECETYPE_BLACK_CANNON;
	m_mPieceValue['p'] = PIECETYPE_BLACK_PAWN;

	m_mPieceValue['K'] = PIECETYPE_RED_KING;
	m_mPieceValue['G'] = PIECETYPE_RED_ADVISER;
	m_mPieceValue['M'] = PIECETYPE_RED_ELEPHANT;
	m_mPieceValue['R'] = PIECETYPE_RED_CHARIOT;
	m_mPieceValue['N'] = PIECETYPE_RED_HORSE;
	m_mPieceValue['C'] = PIECETYPE_RED_CANNON;
	m_mPieceValue['P'] = PIECETYPE_RED_PAWN;

}

void SinicaProtocolDispatcher::start()
{
	parseBoardFile("board.txt");
	DarkChessPoint src;
	DarkChessPoint dst;
	color();
	m_ai->generateMove( src, dst );
	writeMoveFile("move.txt", src, dst );
}

void SinicaProtocolDispatcher::color()
{
	if( m_iTurn % 2 == 0) m_ai->color( m_iFirstColor );
	else m_ai->color( m_iFirstColor^EXCLUSIVE_OR_OPPOSITE_COLOR );
}

void SinicaProtocolDispatcher::parseBoardFile(char* filename)
{
	ifstream ifs;
	ifs.open( filename, ifstream::in );

	if( ifs.fail() ) exit(0);

	char buf[256];
	string sCmd;
	vector<string> vCmds;
	ifs.getline( buf, sizeof(buf) ); // date
	ifs.getline( buf, sizeof(buf) ); // player 1 v.s player 2

	ifs.getline( buf, sizeof(buf) ); // remain pieces( for 殘局 )
	sCmd  = buf;
	tokenizer( vCmds, sCmd );
	for( int i=0; i<PIECETYPE_COUNT; i++ ){
									//Index 0 = "*"
		m_iPieceCount[i] = str2int( vCmds[i+1] );
	}

	//前7 和 後7 互相換位置 要讓黑色棋子的個數放在前面
	for( int i=0; i<(PIECETYPE_COUNT >> 1); i++ ){
		int tmp = m_iPieceCount[i];
		m_iPieceCount[i] = m_iPieceCount[(PIECETYPE_COUNT >> 1)+i];
		m_iPieceCount[(PIECETYPE_COUNT >> 1)+i] = tmp;
	}
	vCmds.clear();

	/* Sinica Board
	8 X X X X
	7 X X X X
	6 X X X X
	5 X X X X
	4 X X X X
	3 X X X X
	2 X X X X
	1 X X X X
	  a b c d
	*/
	for( int i=BOARD_WIDTH-1; i>=0; i-- ){
		ifs.getline( buf, sizeof(buf) ); //board state
		sCmd  = buf;
		tokenizer( vCmds, sCmd );
		for( int j=0; j<BOARD_HEIGHT; j++ ){
			int iPiece;
			// Index 0 is "*"
			if( vCmds[j+1] == "-" ) iPiece = PIECETYPE_NONE;
			else if( vCmds[j+1] == "X" ) iPiece = PIECETYPE_COVERED;
			else iPiece = m_mPieceValue[ vCmds[j+1].at(0) ];

			m_iCurrentBoard[i+j*BOARD_WIDTH] = iPiece;
		}
		vCmds.clear();
	}

	m_ai->initBoardState( m_iPieceCount, m_iCurrentBoard );

	ifs.getline( buf, sizeof(buf) ); // who first
	sCmd = buf;
	tokenizer( vCmds, sCmd );

	//Sinica顏色表示 紅:0 黑:1
	//CYC顏色表示 黑:0 紅:1

	//先將顏色倒過來
	m_iFirstColor = vCmds[2].at(0) - '0';
	m_iFirstColor ^= EXCLUSIVE_OR_OPPOSITE_COLOR;
	vCmds.clear();
	
	ifs.getline( buf, sizeof(buf) ); // time
	sCmd = buf;
	tokenizer( vCmds, sCmd );
	limit( vCmds );
	vCmds.clear();

	do{
		vCmds.clear();
		ifs.getline( buf, sizeof(buf) );
		sCmd = buf;
		tokenizer( vCmds, sCmd );
	} while( parseMove(vCmds) );

	ifs.close();
}

void SinicaProtocolDispatcher::limit( const vector<string>& vCmds )
{
	m_ai->limit( str2int(vCmds[2])*1000 );
}

void SinicaProtocolDispatcher::writeMoveFile( char* filename, const DarkChessPoint& src, const DarkChessPoint& dst )
{
	ofstream ofs;
	ofs.open( filename, ofstream::out );

	string sMove = "";

	if( isOutsideOfBoard( src ) && isOutsideOfBoard( dst ) ) {
		
	} else if( isOutsideOfBoard( dst ) ){
		
		/*
		1 (模式: 0 = 走子, 1 = 翻子)
		b2 (翻子位置)
		0  (固定寫0)
		0  (提供亂數種子給伺服器, 可給任意值)
		*/
		sMove += "1\n";
		sMove += ('a' + src.y );
		sMove += ('1' + src.x );
		sMove += '\n';
		sMove += "0\n";
		sMove += "0\n";
	} else{
		/*0 (模式: 0 = 走子, 1 = 翻子)
		b5 (From)
		b4 (To)
		123  (提供亂數種子給伺服器, 可給任意值)*/
		sMove += "0\n";
		sMove += ('a' + src.y );
		sMove += ('1' + src.x );
		sMove += '\n';
		sMove += ('a' + dst.y );
		sMove += ('1' + dst.x );
		sMove += '\n';
		sMove += "0\n";
	}

	ofs << sMove;
	ofs << m_ai->m_sComment << endl;
	ofs.close();
}

bool SinicaProtocolDispatcher::isOutsideOfBoard( const DarkChessPoint& point )
{
	if( point.x < 0 || point.y < 0 || point.x >= 8 || point.y >= 4 ) return true;
	else  return false;
}

bool SinicaProtocolDispatcher::parseMove( const vector<string>& vCmds )
{
	if( vCmds[0] == "*" && vCmds[1].at( vCmds[1].length()-1 ) == '.' ){
		
		DarkChessPoint src;
		DarkChessPoint dst;
		//一行可能是一步 或是兩步
		//a8(G) b8(g) or a8(G) only
		unsigned int index = 2;

		while( index < vCmds.size() ){
			const string& sMove = vCmds[index];
			src.x = sMove[1] - '1';
			src.y = sMove[0] - 'a';

			if( sMove[2] == '(' ){
				int iFlipValue = m_mPieceValue[ sMove[3] ];
				m_ai->flip( src, iFlipValue );

			} else if( sMove[2] == '-' ){
				dst.x = sMove[4] - '1';
				dst.y = sMove[3] - 'a';
				m_ai->move( src, dst );
			}
			index++;
			m_iTurn++;
		}
		return true;

	} else return false;
}

void SinicaProtocolDispatcher::tokenizer( vector<string>& vCmds, const string& sCmd )
{
	size_t start = sCmd.find_first_not_of(" \r\n");
	size_t end = sCmd.find_first_of(" \r\n", start+1);
	while( start!=string::npos ){
		vCmds.push_back( sCmd.substr( start, end-start ) );
		start = sCmd.find_first_not_of(" \r\n", end );
		end = sCmd.find_first_of(" \r\n", start+1);
	}
}

int SinicaProtocolDispatcher::str2int( const string& str )
{
	stringstream ss;
	int i;
	ss << str;
	ss >> i;
	return i;
}

string SinicaProtocolDispatcher::int2str( int i )
{
		stringstream ss;
		string str;
		ss << i;
		ss >> str;
		return str;
}


SinicaProtocolDispatcher::~SinicaProtocolDispatcher(void)
{
}
