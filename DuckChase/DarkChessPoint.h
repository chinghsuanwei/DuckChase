#ifndef  __DARKCHESSPOINT_H__
#define __DARKCHESSPOINT_H__

class DarkChessPoint
{
public:
	DarkChessPoint(void);
	DarkChessPoint( int x, int y );
	~DarkChessPoint(void);

	int x;
	int y;
};

#endif