#pragma once
#pragma warning(disable:4996)
#include<vector>
#include <process.h>
#include<string>
#include<map>
#include"SocketInit.hpp"
#include<Windows.h>
#include<winsock2.h>
#include<WS2tcpip.h>
using namespace std;


class ServerClass {
private:
	SocketInit socketinit;//ȷ������Э��

	SOCKET ServSock;//�����������socket

public:
	ServerClass();//���캯��

	~ServerClass();//��������

	void Bind(const char* ip, unsigned short port);//����Э���ַ�غͰ��׽���

	void Listen();//�����׽���

	void Communication();//���ӿͻ��ˣ�Ϊ�ͻ��˴����̣߳��������Կͻ��˵���Ϣ�����д���

	SOCKET GetSocket();//��ȡsocket�Ľӿ�
};
