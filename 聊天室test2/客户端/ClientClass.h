#pragma once
#pragma warning(disable:4996)
#include"../������test2/SocketInit.hpp"
#include <process.h>
#include<Windows.h>
#include<winsock2.h>
#include<WS2tcpip.h>
#include<graphics.h>
using namespace std;
class ClientClass {
private:

    SocketInit socketinit;//ȷ������Э��

    SOCKET ClntSock;// �����׽���

    int m_RoomID;//����ķ����

    string m_Name;//�ǳ�

public:
    ClientClass();

    ~ClientClass();

    void ConnectServer(const char* ip, unsigned short port);//���ӷ�����

    void SendData();//��������

    void RecvData();//��������

    SOCKET GetSocket();//��ȡsocket
};

