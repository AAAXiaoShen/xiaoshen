#pragma once
#pragma warning(disable:4996)
#include<vector>
#include <process.h>
#include<string>
#include<map>
#include"SocketInit.hpp"
#include"MsgType.hpp"
#include<Windows.h>
#include<winsock2.h>
#include<WS2tcpip.h>
using namespace std;


class ServerClass {
private:
	SocketInit socketinit;//确认网络协议

	SOCKET ServSock;//服务器自身的socket

public:
	ServerClass();//构造函数

	~ServerClass();//析构函数

	void Bind(const char* ip, unsigned short port);//创建协议地址簇和绑定套接字

	void Listen();//监听套接字

	void Communication();//连接客户端，为客户端创建线程，接收来自客户端的消息并进行处理

	SOCKET GetSocket();//获取socket的接口
};
