#define USER_MODE 1
#define CYC_MODE 2
#define SINICA_MODE 3

#define MODE SINICA_MODE

#if MODE == USER_MODE
#include "UserModeProtocolDispatcher.h"
#elif MODE == CYC_MODE
#include "CycProtocolDispatcher.h"
#elif MODE == SINICA_MODE
#include "SinicaProtocolDispatcher.h"
#endif

#include <iostream>
#include "DarkChessAI.h"


using namespace std;

int main(int argc , char **argv)
{
	DarkChessAI ai; //換成你的AI

#if MODE == USER_MODE
	UserModeProtocolDispatcher( &ai ).start(); //將你的AI當參數帶進去 and enter infinite loop
#elif MODE == CYC_MODE
	char* ip;
	int port;
	switch( argc ){
		case 1:
			CycProtocolDispatcher( &ai ).start();
			break;
		case 3:
			ip = argv[1];
			port = atoi( argv[2] );
			CycProtocolDispatcher( &ai, ip, port ).start();
			break;
		default:
			cout << "Error: usage: [ip] [port]" << endl;
			exit(0);
			break;
	}
	
#elif MODE == SINICA_MODE
	SinicaProtocolDispatcher( &ai ).start();
#endif
}

