#include <WinSock2.h>
#include <Windows.h>
#include <stdio.h>
#include <iostream>
using namespace std;

#pragma comment(lib, "Ws2_32.lib")

SOCKET Socket;
WSADATA Winsock;
sockaddr_in Addr;
int Addrlen = sizeof(Addr);

int main()
{
	WSAStartup(MAKEWORD(2, 2), &Winsock);    // Start Winsock

	if (LOBYTE(Winsock.wVersion) != 2 || HIBYTE(Winsock.wVersion) != 2)    // Check version
	{
		WSACleanup();
		return 0;
	}

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	ZeroMemory(&Addr, sizeof(Addr));    // clear the struct
	Addr.sin_family = AF_INET;    // set the address family
	Addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	Addr.sin_port = htons(55556);    // set the port

	if (connect(Socket, (sockaddr*)&Addr, sizeof(Addr)) < 0)
	{
		cout << "Connection failed !" << endl;
		getchar();
		return 0;
	}


	////////////////////////////////////////


	FILE *File, *fis;
	char *Buffer;
	long Size;

	fopen_s(&File, "E:\\sample.txt", "r");

	if (!File)
	{
		cout << "Error while readaing the file" << endl;
		getchar();
		return 0;
	}

	fseek(File, 0, SEEK_END);
	Size = ftell(File);
	fseek(File, 0, SEEK_SET);

	Buffer = new char[Size];

	fread(Buffer, Size, 1, File);
	char cSize[MAX_PATH];
	sprintf_s(cSize, "%i", Size);

	fclose(File);

	printf("Sending file .. \n");
	send(Socket, cSize, MAX_PATH, 0); // File size

	//int len = Size;
	//char *data = Buffer;

	int Offset = 0;
	while (Size > Offset)
	{
		int Amount = send(Socket, Buffer + Offset, Size - Offset, 0);

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


	getchar();
	closesocket(Socket);
	WSACleanup();
	return 0;
}