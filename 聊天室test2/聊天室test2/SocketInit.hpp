#pragma once
#ifndef _SOCKET_INIT_H_
#define _SOCKET_INIT_H_

#include<winsock2.h>
#include<iostream>
#pragma comment(lib,"ws2_32.lib")

//ȷ������Э��
class SocketInit {
public:
	SocketInit() {
		WORD sockVersion = MAKEWORD(2, 2);
		WSADATA wasData;
		if (WSAStartup(sockVersion, &wasData) != 0) {
			std::cout << "��̬�����Ӽ���ʧ�ܣ�" << std::endl;
		}
	}
	~SocketInit() {
		WSACleanup();
	}
};

#endif // _SOCKET_INIT_H_