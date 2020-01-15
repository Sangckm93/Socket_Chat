#define _WINSOCK_DEPRECATED_NO_WARNINGS
#pragma once
#include"stdio.h";
#include "stdint.h"
#include <iostream>
#include <string.h>
#include "Winsock2.h";
#include "Ws2tcpip.h"

#pragma comment(lib,"ws2_32.lib") //Winsock Library
char* Get_ip(char* client_msg);
char* Get_Data(char* client_msg);
class Socket
{
	private:
		WSADATA wsa;
		SOCKET s;
		struct sockaddr_in server;
		char* message;
	public:
		Socket(char* ip_server, int port);
		Socket(int port);
		void Server_action();
		void Socket_Init(SOCKET name_socket,char* ip_server, int port);
		int Socket_Send(char* data,int size);
		int Socket_Recv(char* src, uint16_t size);
};

typedef struct
{
	char* ip_server;
	char* Message2Goal;
	int port;
}Socket_info;
