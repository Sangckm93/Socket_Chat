#include "Socket.h"
#include "stdio.h"
void main()
{
	// Creat socket to receive data from client
	Socket chat(1234);
	while (1)
	{
		chat.Server_action();
	}
	//getchar();
}