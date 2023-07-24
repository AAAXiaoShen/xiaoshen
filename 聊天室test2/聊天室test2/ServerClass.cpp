#include "ServerClass.h"



using namespace std;



const int MaxNum = 100;

SOCKET ClntSocks[MaxNum];//��ſͻ��˵�socket��externȫ�ֱ���

int CountNum = 0;//ͳ�Ƶ�ǰ�Ŀͻ�������


DWORD WINAPI HandleClnt(int i) {
	char buff[256] = { 0 };
	char temp[256] = { 0 };
	int Strlen;
	while (true) {
		Strlen = recv(ClntSocks[i], buff, 255, NULL);

		if (Strlen > 0) {
			cout << i << ":" << buff << endl;

			//�������пͻ���
			memset(temp, 0, 256);//���
			sprintf_s(temp, "%d:%s", i, buff);//temp�Ƿ��͸������ͻ��˵���Ϣ
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
	//���������׽���
	ServSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//����TCP�׽���
	if (ServSock == SOCKET_ERROR) {
		cout << "�����׽��ִ���ʧ��" << endl;
		return;
	}

}

ServerClass::~ServerClass() {
	closesocket(ServSock);
}

void ServerClass::Bind(const char* ip, unsigned short port) {

	sockaddr_in sock_in;// sockaddr_in�Ǳ���IPv4��ַ��Ϣ�Ľṹ��
	sock_in.sin_family = AF_INET;
	sock_in.sin_port = htons(port);//�˿�
	sock_in.sin_addr.S_un.S_addr = inet_addr(ip);//ip,ֵΪINADDR_ANYʱ���õ��Ƿ�������IP��ַ

	int ret = bind(ServSock, (const sockaddr*)&sock_in, sizeof(sock_in));//��(ip �� socket��)

	if (ret == SOCKET_ERROR) {
		cout << "���׽���ʧ��" << endl;
		return;
	}
	cout << "���׽��ֳɹ�" << endl;
}

void ServerClass::Listen() {

	if (listen(ServSock, 10) == SOCKET_ERROR) {//�������˴��ڶ���������˵ �ں�Ϊ ���׽���ά����������Ӹ���
		cout << "�����׽���ʧ��" << endl;
		return;
	}
	cout << "�����׽��ֳɹ�" << endl;
}

void ServerClass::Communication() {
	//ѭ�����Ӷ���ͻ���
	for (int i = 0; i < MaxNum; i++) {
		//���տͻ��˵�����
		sockaddr_in ClntAddr;
		int clen = sizeof(ClntAddr);

		//���ӿͻ���
		SOCKET ClntSock = accept(ServSock, (sockaddr*)&ClntAddr, &clen);

		if (ClntSock == SOCKET_ERROR) {
			cout << "���տͻ���ʧ��" << GetLastError() << endl;
			closesocket(ClntSock);
			return;
		}
		cout << "���ӿͻ��˳ɹ�" << endl;

		//���ͻ��˵�socket��������
		ClntSocks[i] = ClntSock;

		CountNum++;

		//Ϊ�ͻ��˷����̣߳����̸߳��������Ϣ
		HANDLE hTheard = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)HandleClnt, (LPVOID)i, 0, 0);
	}

}

SOCKET ServerClass::GetSocket() {
	return ServSock;
}