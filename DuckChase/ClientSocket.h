#ifndef __CLIENTSOCKET_H__
#define __CLIENTSOCKET_H__

//#include <windows.h>
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define MAXRECV 256
#pragma comment(lib,"ws2_32.lib")
using namespace std;

class ClientSocket
{
public:
    ClientSocket();
    ClientSocket(const string &sIp, const int &iPort);
    ~ClientSocket();

    void initSocket(const string &sIp, const int &iPort);
    void closeSocket() const;
    void sendData(const string &sData) const;
    void recvData(string &sData) const ;
    const ClientSocket & operator << (const string &) const;
    const ClientSocket & operator >> (string &) const;
private:
    SOCKET m_sock;
};

#endif