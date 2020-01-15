#include "Socket.h"
#include "stdio.h"

Socket::Socket(char* ip_server, int port)
{
	printf(" \nInitialising Winsock... ");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf(" Failed.Error Code : % d ", WSAGetLastError());
	}
	printf(" Initialised.\n ");
	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : % d", WSAGetLastError());
	}
	printf(" Socket created.\n ");

	server.sin_addr.s_addr = inet_addr(ip_server);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);

	//Connect to remote server
	if (connect(s, (struct sockaddr*) & server, sizeof(server)), 0)
	{
		puts("connect error");
	}
	puts("Connected");
}
Socket::Socket(int port)
{
	printf(" \nInitialising Winsock... ");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf(" Failed.Error Code : % d ", WSAGetLastError());
		//return 1;
	}

	printf(" Initialised.\n ");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : % d", WSAGetLastError());
	}

	printf(" Socket created.\n ");

	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	bind(s, (struct sockaddr*) & server, sizeof(struct sockaddr));

	listen(s, 2);
	
}
void Socket::Server_action()
{
	SOCKET cli_Socket = INVALID_SOCKET;
	struct sockaddr_in client;
	int socksize = sizeof(struct sockaddr_in);
	cli_Socket = accept(s, (struct sockaddr*) & client, &socksize);
	printf("Client: \r\n");
	printf("\tAddr: %s\r\n", inet_ntoa(client.sin_addr));
	printf("\tPort: %d\r\n", client.sin_port);
	Socket_info client_goal;
	//int timeout = 0;
	int src_socket_cli = 0;
	char buffer[1024];
	memset(buffer, 0, sizeof(buffer));
	//struct timeval timeout;
	//timeout.tv_sec = 10; // Server sẽ lắng nghe trong 10s, nếu tham số timeout = NULL thì select sẽ chạy mãi.
	//timeout.tv_usec = 0;
	//int n_select;

	while (src_socket_cli == 0)
	{
		//select();
		//thread:
			/*timeout++;
			if (timeout > 50)
			{
				break;
			}
			Sleep(100);*/
			src_socket_cli = recv(cli_Socket,buffer,sizeof(buffer), 0);
		printf("Message: %s\r\n", buffer);
	}
	closesocket(cli_Socket);
	printf("Close connection from %s\r\n", inet_ntoa(client.sin_addr));
	client_goal.ip_server = Get_ip(buffer);
	client_goal.Message2Goal = Get_Data(buffer);

	printf("ip: %s\r\n", client_goal.ip_server);
	printf("Message: %s\r\n", client_goal.Message2Goal);
	//printf("data len: %d\r\n", strlen(client_goal.Message2Goal));
	
	// Creat new Socket to send data to client
	SOCKET cli_Socket_goal = INVALID_SOCKET;
	//Socket_Init(cli_Socket_goal, client_goal.ip_server, 3333);	// init socket by function
	WSADATA wsa_send;
	struct sockaddr_in server_send;
	WSAStartup(MAKEWORD(2, 2), &wsa_send);
	cli_Socket_goal = socket(AF_INET, SOCK_STREAM, 0);
	server_send.sin_addr.s_addr = inet_addr(client_goal.ip_server);
	server_send.sin_family = AF_INET;
	server_send.sin_port = htons(3333);	// 3333 is port of client
	if (connect(cli_Socket_goal, (struct sockaddr*) & server_send, sizeof(server_send)), 0)
	{
		puts("connect error");
	}
	puts("Connected");
	if (send(cli_Socket_goal, client_goal.Message2Goal, strlen(client_goal.Message2Goal), 0) <=0)
	{
		printf("Send failed");
	}
	else
	{
		memset(client_goal.Message2Goal, 0, strlen(client_goal.Message2Goal));	// Clear old data
		closesocket(cli_Socket_goal);
		printf("Sent message");
	}
	memset(buffer, 0, sizeof(buffer));
}
void Socket::Socket_Init(SOCKET name_socket, char* ip_server, int port)
{
	WSADATA wsa_temp;
	struct sockaddr_in server_temp;
	//printf(" \nInitialising Winsock... ");
	if (WSAStartup(MAKEWORD(2, 2), &wsa_temp) != 0)
	{
		printf(" Failed.Error Code : % d ", WSAGetLastError());
	}

	printf(" Initialised.\n ");

	//Create a socket
	if ((name_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : % d", WSAGetLastError());
	}

	printf(" Socket created.\n ");

	server_temp.sin_addr.s_addr = inet_addr(ip_server);
	server_temp.sin_family = AF_INET;
	server_temp.sin_port = htons(port);

	//Connect to remote server
	if (connect(name_socket, (struct sockaddr*) & server_temp, sizeof(server_temp)), 0)
	{
		puts("connect error");
	}
	puts("Connected");
}
int Socket::Socket_Send(char* data, int size)
{
	return send(s, data, size, 0);
}
int Socket::Socket_Recv(char* src, uint16_t size)
{
	return recv(s, src, size, 0);
}
