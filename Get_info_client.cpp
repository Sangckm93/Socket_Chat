#include "Socket.h"
//standard of message
//{"Dst":"192.168.1.1";"Data":"hello"}
char client_ip[256];
//memset(client_ip, 0, sizeof(client_ip));
char client_Data[256];
//memset(client_Data, 0, sizeof(client_Data));
char* Get_ip(char* client_msg)
{
	int gAction_step = 0;
	char* temp = strstr(client_msg, "\"Dst\"");
	if (temp != NULL)
	{
		gAction_step = 1;
		int i = 0;
		while (gAction_step != 0)
		{
			switch (gAction_step)
			{
			case 1:
				if(*(temp+7+i) != (char)0x22)
				//if(client_ip[i] == (char)0x22)
				{
					memcpy(client_ip + i, temp + 7 + i, 1);
					//gAction_step = 2;
				}else gAction_step = 0;
				break;
			
			/*case 2:
				if(client_ip[i] != (char)0x22)
				{
					gAction_step = 3;
				}
				break;
			case 3:
				memcpy(client_ip + i, temp + 6 + i, 1);
				if(client_ip[i] == (char)0x22)
					gAction_step = 0;
				break;
			*/
			}
			i++;
		}
		//printf("ip: %s", client_ip);
	}
	return client_ip;
}
char* Get_Data(char* client_msg)
{
	char* temp = strstr(client_msg,"\"Data\"");
	if (temp != NULL)
	{
		int i = 0;
		while (1)
		{
			if (*(temp+8+i) != (char)0x22)
			{
				memcpy(client_Data + i,temp+8+i, 1);
			}else break;
			i++;
		}
		//printf("ip: %s", client_ip);
	}
	return client_Data;
}