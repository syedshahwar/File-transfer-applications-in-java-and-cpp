#pragma warning(disable:4496)
#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;


#pragma comment(lib, "Ws2_32.lib")
#define Port 55556

SOCKET Socket, Sub;
WSADATA Winsock;
sockaddr_in Addr;
sockaddr_in IncomingAddress;
int AddressLen = sizeof(IncomingAddress);

int main()
{
	WSAStartup(MAKEWORD(2, 2), &Winsock);    // Start Winsock

	if (LOBYTE(Winsock.wVersion) != 2 || HIBYTE(Winsock.wVersion) != 2)    // Check version
	{
		WSACleanup();
		return 0;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	ZeroMemory(&Addr, sizeof(Addr));
	Addr.sin_family = AF_INET;
	Addr.sin_port = htons(Port);
	bind(Socket, (sockaddr*)&Addr, sizeof(Addr));

	if (listen(Socket, 1) == SOCKET_ERROR)
	{
		printf("listening error\n");
	}
	else
	{
		printf("Listening\n");
	}

	if (Sub = accept(Socket, (sockaddr*)&IncomingAddress, &AddressLen))
	{
		char *ClientIP = inet_ntoa(IncomingAddress.sin_addr);
		int ClientPort = ntohs(IncomingAddress.sin_port);
		printf("Client conncted!\n");
		printf("IP: %s:%d\n", ClientIP, ClientPort);

	}


		////////////////////////////////////////
	
		printf("Receiving file .. \n");
		int Size;
		char *Filesize = new char[1024];

		if (recv(Sub, Filesize, 1024, 0)) // File size
		{
			Size = atoi((const char*)Filesize);
			printf("File size: %d\n", Size);
		}

		char *Buffer = new char[Size];

		//int len = Size;
		//char *data = Buffer;

		int Offset = 0;
		while (Size > Offset)
		{
			int Amount = recv(Sub, Buffer + Offset, Size - Offset, 0);

			if (Amount <= 0)
			{
				cout << "Error: " << WSAGetLastError() << endl;
				break;
			}
			else
			{
				Offset += Amount;
			}
		}

		FILE *File;
		fopen_s(&File, "E:\\out-cpp.txt", "wb");
		fwrite(Buffer, 1, Size, File);
		fclose(File);

		free(Buffer);
		closesocket(Sub);
		closesocket(Socket);
		WSACleanup();
	

	getchar();
	return 0;
}
