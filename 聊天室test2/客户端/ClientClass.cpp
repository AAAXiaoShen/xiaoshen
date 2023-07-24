#include "ClientClass.h"
#pragma warning(disable:4996)
#include<Windows.h>
using namespace std;


void Send(LPVOID lp) {

	SOCKET ClntSock = *(SOCKET*)lp;

	char buff[256];
	while (true) {
		memset(buff, 0, 256);//�������
		cout << "�����룺" << endl;
		cin >> buff;
		send(ClntSock, buff, strlen(buff), NULL);//����Ϣ��������
	}
}

ClientClass::ClientClass() {
	//���������׽���
	ClntSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//����TCP�׽���
	if (ClntSock == SOCKET_ERROR) {
		cout << "�����׽��ִ���ʧ��" << endl;
		return;
	}
	cout << "�����׽��ִ����ɹ�" << endl;

}

ClientClass::~ClientClass() {
	closesocket(ClntSock);
}

void ClientClass::ConnectServer(const char* ip, unsigned short port) {//���ӷ�����

	sockaddr_in sock_in;
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = htons(port);
	sock_in.sin_addr.S_un.S_addr = inet_addr(ip);

	if (connect(ClntSock, (const sockaddr*)&sock_in, sizeof(sockaddr_in)) == SOCKET_ERROR) {
		cout << "���ӷ�����ʧ��" << GetLastError() << endl;
		return;
	}

	cout << "�����˽�������" << endl;

}

void ClientClass::SendData() {

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Send, (LPVOID)&ClntSock, 0, 0);

}

void ClientClass::RecvData() {
	char buff[256];

	int n = 0;

	int Strlen;

	initgraph(300, 400, 1);//������Ϣ�Ĵ���

	while (true) {
		Strlen = recv(ClntSock, buff, 255, NULL);
		if (Strlen > 0) {
			//��ʾ��ͼ�ν��洰��
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