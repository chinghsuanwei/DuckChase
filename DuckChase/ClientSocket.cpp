#include "ClientSocket.h"

ClientSocket::ClientSocket()
{

}
ClientSocket::ClientSocket(const string &sIp, const int &iPort)
{
    initSocket(sIp, iPort);
}

ClientSocket::~ClientSocket()
{

}

const ClientSocket &
    ClientSocket::operator << (const std::string & s) const
{
    sendData(s);
    return *this;
}

const ClientSocket &
    ClientSocket::operator >> (std::string & s) const
{
    recvData(s);
    return *this;
}

void ClientSocket::initSocket(const string &sIp, const int &iPort) 
{
    SOCKET lhSocket;
    SOCKADDR_IN lSockAddr;
    WSADATA wsaData;
    int lConnect;
    if(WSAStartup(MAKEWORD(2,0),&wsaData) != 0)
    {
        cout<<"Socket Initialization Error. Program aborted\n";
        return;
    }
    lhSocket = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    if(lhSocket == INVALID_SOCKET)
    {
        cout<<"Invalid Socket "<<GetLastError()<<". Program Aborted\n"<<endl;
    }
    memset(&lSockAddr,0, sizeof(lSockAddr));
    lSockAddr.sin_family = AF_INET;
    lSockAddr.sin_port = htons(iPort);
    lSockAddr.sin_addr.s_addr = inet_addr(sIp.c_str());
    lConnect = connect(lhSocket,(SOCKADDR *)&lSockAddr,sizeof(SOCKADDR_IN));
    if(lConnect != 0)
    {
        cout<<"Connect Error. Program aborted\n";
        return;
    }
    m_sock = lhSocket;
    return;
}

void ClientSocket::closeSocket() const
{
    closesocket(m_sock);
}

void ClientSocket::sendData(const string &sData) const
{
    int iLength = send(m_sock,sData.c_str(),sData.size(),0);
    if(iLength < (int)sData.size())
    {
        cout<<"Send Error.\n";
    }
}

void ClientSocket::recvData(string &sData) const
{
    char buf[2];
    sData = "";
    memset (buf, 0, 2);

    while(true)
    {
        int status = recv (m_sock, buf, 1, 0);
        if (status == -1)
        {
            cout << "status == -1   errno == " << errno <<"  in Socket::recv\n";
            exit(1);
            return;
        }
        else if (status == 0) return;
        else
        {
            if(buf[0] !='\n') sData += buf[0]; 
            else 
            {
                sData += "\n\0";
                return;
            }
        }
    }
}

