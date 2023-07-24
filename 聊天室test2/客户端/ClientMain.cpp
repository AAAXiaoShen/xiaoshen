#include<iostream>
#include"ClientClass.h"
#pragma warning(disable:4996)
using namespace std;


int main() {
	ClientClass Client;

	SOCKET ClntSock = Client.GetSocket();

	Client.ConnectServer("192.168.181.1", 12306);

	Client.SendData();

	Client.RecvData();

	while (true);//อฃถู

	return 0;
}