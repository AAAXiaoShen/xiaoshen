#include<iostream>
#include "ServerClass.h"
#pragma warning(disable:4996)
using namespace std;


int main() {
	ServerClass Server;
	Server.Bind("192.168.181.1", 12306);
	Server.Listen();


	Server.Communication();
	
	while (true);

	return 0;

}