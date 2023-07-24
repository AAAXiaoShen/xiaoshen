#pragma once
#pragma warning(disable:4996)
#include"../聊天室test2/SocketInit.hpp"
#include <process.h>
#include<Windows.h>
#include<winsock2.h>
#include<WS2tcpip.h>
#include<graphics.h>
using namespace std;
class ClientClass {
private:

    SocketInit socketinit;//确认网络协议

    SOCKET ClntSock;// 监听套接字

    int m_RoomID;//加入的房间号

    string m_Name;//昵称

public:
    ClientClass();

    ~ClientClass();

    void ConnectServer(const char* ip, unsigned short port);//连接服务器

    void SendData();//发送数据

    void RecvData();//接收数据

    SOCKET GetSocket();//获取socket
};

