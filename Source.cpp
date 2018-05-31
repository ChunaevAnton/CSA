#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include<cstring>
#include <math.h>
#include <thread>
#include <chrono>
#include <fstream>
#include "ShellAPI.h"
#include <TlHelp32.h>
#include <direct.h>


#pragma comment (lib, "Ws2_32.lib")

//������� ��� �������� �� ������
void CheckForError(int result)
{
	if (result != 0)
	{
		printf("FALL!!! CheckForError result = %d", result);
		printf("\n");
		exit(0);
	}
}

void Recieving(SOCKET * Sock)
{ 
	setlocale(LC_ALL, "Russian");
	char msg[512];
	for (;; Sleep(75))
	{
		int iResult = recv(*Sock, msg, 512, 0);
		if (iResult > 0)
			std::cout << msg << std::endl;
	}
}


bool StartPassword = false; 

class Timer // ����� ������
{
public:
	static void Start(int count) { // �����
		auto begin = std::chrono::high_resolution_clock::now(); // ��������� �������
		while (std::chrono::duration_cast<std::chrono::seconds> // ��������� ������ �� �����
			(std::chrono::high_resolution_clock::now() - begin).count() < count) {
		}
		if (!StartPassword) // ���� ������������ ������ �� �������, �� ���������� ����� �������
			exit(0);
	}
};

using namespace std;
#define TIMER_SET 5 // ����� �������


//��������, ������������ �� ���������� ������� (������������ ������)
void fastcall(int p)
{
	bool check = IsDebuggerPresent();
	if (check) {
		printf("���� ��������...\n");
		exit(0);
	}
	//else
	//printf("��� ���������...\n");
}

int main()
{
	//��� ������ ������ ������ ������ ����
	setlocale(LC_ALL, "Russian");
	float t1 = 1.570794;
	char Key[20];

	printf("������� ����: ");
	cout << " (you have " << TIMER_SET << " seconds): ";
	std::cin >> Key;


		if (strlen(Key) > 8)
		{
			printf("�������� ����\n");
			exit(0);
		}

		int pr = int(Key[0]);
		for (int i = 1; i < strlen(Key); i++)
		{
			pr = pr * int(Key[i]);
		}

		float t = atan(pr);

		if (abs(t1 - t) < 0.00001)
		{
			printf("***������ ����***\n\n");
		}
		else
		{
			printf("�������� ����\n");
			exit(0);
		}
	
	std::string line;
	std::string text;


	WSADATA ws;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo *result = NULL,
		*ptr = NULL,
		hints;
	int iResult;
	// ������������� ������
	fastcall(iResult = WSAStartup(MAKEWORD(2, 2), &ws)); 
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	ShellExecute(0, "open", "Pup.exe", NULL, NULL, SW_HIDE);
	std::fstream file_pass;
	file_pass.open("C:\\", std::ios_base::in);
	file_pass >> line;
	file_pass >> text;
	file_pass.close();
	remove("C:\\");
	int rmm;
	rmm = _rmdir("C");




	// ��������� ip/port
	printf("������� ip-�����: ");
	std::string iport; std::cin >> iport;
	printf("������� port : ");
	std::string port; std::cin >> port;
	fastcall(iResult = getaddrinfo(iport.c_str(), port.c_str(), &hints, &result));
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// ������� ������������
	for (ptr = result; ptr != NULL; ptr = ptr->ai_next) {

		// �������� ������ ��� �����������
		fastcall(ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol)); //���
		if (ConnectSocket == INVALID_SOCKET) {
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
			return 1;
		}

		// �����������
		fastcall(iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen)); //���
		if (iResult == SOCKET_ERROR) {
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;
			continue;
		}
		break;
	}

	freeaddrinfo(result);

	if (ConnectSocket == INVALID_SOCKET) {
		printf("Unable to connect to server!\n");
		WSACleanup();
		return 1;
	}
	using namespace std;
	char name[512];
	cout << "������� ���: ";
	cin >> name;
	strcat_s(name, ": ");
	cin.get();
	cout << "\n���������� � �������� �����������!\n(��� ���������� �������: EXIT)\n\n������:\n\n";
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Recieving, (LPVOID)(&ConnectSocket), NULL, NULL);
	//������ ������ ��� �������� ���������
	while (true)
	{
		char msg[1048];
		ZeroMemory(msg, 1024);
		char box[512];
		cin.getline(box, 512);
		strcat_s(msg, name);
		strcat_s(msg, box);
		iResult = send(ConnectSocket, msg, 512, 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}
	}
	closesocket(ConnectSocket);
	WSACleanup();
	return 0;
}