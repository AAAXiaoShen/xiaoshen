#include "ClientClass.h"
#pragma warning(disable:4996)
#include<Windows.h>
using namespace std;


void Send(LPVOID lp) {

	SOCKET ClntSock = *(SOCKET*)lp;

	char buff[256];
	while (true) {
		memset(buff, 0, 256);//清空数组
		cout << "请输入：" << endl;
		cin >> buff;
		send(ClntSock, buff, strlen(buff), NULL);//发信息给服务器
	}
}

ClientClass::ClientClass() {
	//创建监听套接字
	ClntSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//创建TCP套接字
	if (ClntSock == SOCKET_ERROR) {
		cout << "监听套接字创建失败" << endl;
		return;
	}
	cout << "监听套接字创建成功" << endl;

}

ClientClass::~ClientClass() {
	closesocket(ClntSock);
}

void ClientClass::ConnectServer(const char* ip, unsigned short port) {//连接服务器

	sockaddr_in sock_in;
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = htons(port);
	sock_in.sin_addr.S_un.S_addr = inet_addr(ip);

	if (connect(ClntSock, (const sockaddr*)&sock_in, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		cout << "连接服务器失败" << GetLastError() << endl;
		return;
	}

	cout << "与服务端建立连接" << endl;

}

void ClientClass::SendData() {

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Send, (LPVOID)&ClntSock, 0, 0);

}

void ClientClass::RecvData() {
	char buff[256];

	int n = 0;

	int Strlen;

	initgraph(300, 400, 1);//接收消息的窗口

	while (true) {
		Strlen = recv(ClntSock, buff, 255, NULL);
		if (Strlen > 0) {
			//显示到图形界面窗口
			buff[Strlen] = 0;
			outtextxy(1, n * 20, buff);
			n++;
			if (n > 18) {
				n = 0;
				cleardevice();
			}
		}
	}

}

SOCKET ClientClass::GetSocket() {
	return ClntSock;
}