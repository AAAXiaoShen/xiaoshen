#include "ServerClass.h"



using namespace std;



const int MaxNum = 100;

SOCKET ClntSocks[MaxNum];//存放客户端的socket，extern全局变量

int CountNum = 0;//统计当前的客户端数量


DWORD WINAPI HandleClnt(int i) {
	char buff[256] = { 0 };
	char temp[256] = { 0 };
	int Strlen;
	while (true) {
		Strlen = recv(ClntSocks[i], buff, 255, NULL);

		if (Strlen > 0) {
			cout << i << ":" << buff << endl;

			//发给所有客户端
			memset(temp, 0, 256);//清空
			sprintf_s(temp, "%d:%s", i, buff);//temp是发送给其他客户端的消息
			for (int j = 0; j < CountNum; j++) {
				send(ClntSocks[j], temp, strlen(temp), NULL);
			}
		}
		else {
			cout << Strlen << endl;
		}
	}
	return 0;
}

ServerClass::ServerClass() {
	//创建监听套接字
	ServSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//创建TCP套接字
	if (ServSock == SOCKET_ERROR) {
		cout << "监听套接字创建失败" << endl;
		return;
	}

}

ServerClass::~ServerClass() {
	closesocket(ServSock);
}

void ServerClass::Bind(const char* ip, unsigned short port) {

	sockaddr_in sock_in;// sockaddr_in是保存IPv4地址信息的结构体
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = htons(port);//端口
	sock_in.sin_addr.S_un.S_addr = inet_addr(ip);//ip,值为INADDR_ANY时设置的是服务器的IP地址

	int ret = bind(ServSock, (const sockaddr*)&sock_in, sizeof(sock_in));//绑定(ip 与 socket绑定)

	if (ret == SOCKET_ERROR) {
		cout << "绑定套接字失败" << endl;
		return;
	}
	cout << "绑定套接字成功" << endl;
}

void ServerClass::Listen() {

	if (listen(ServSock, 10) == SOCKET_ERROR) {//监听，此处第二个参数是说 内核为 此套接字维护的最大链接个数
		cout << "监听套接字失败" << endl;
		return;
	}
	cout << "监听套接字成功" << endl;
}

void ServerClass::Communication() {
	//循环连接多个客户端
	for (int i = 0; i < MaxNum; i++) {
		//接收客户端的连接
		sockaddr_in ClntAddr;
		int clen = sizeof(ClntAddr);

		//连接客户端
		SOCKET ClntSock = accept(ServSock, (sockaddr*)&ClntAddr, &clen);

		if (ClntSock == SOCKET_ERROR) {
			cout << "接收客户端失败" << GetLastError() << endl;
			closesocket(ClntSock);
			return;
		}
		cout << "连接客户端成功" << endl;

		//将客户端的socket放入服务端
		ClntSocks[i] = ClntSock;

		CountNum++;

		//为客户端分配线程，该线程负责接收消息
		HANDLE hTheard = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HandleClnt, (LPVOID)i, 0, 0);
	}

}

SOCKET ServerClass::GetSocket() {
	return ServSock;
}