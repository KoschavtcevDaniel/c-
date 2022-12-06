#include <iostream> 
#include <winsock2.h>
#include <windows.h>
#include <string>
#pragma comment (lib, "Ws2_32.lib") 
using namespace std;
#define SRV_PORT 1234 

struct Person
{
	string name; 
	int a[4];
}B;

int answer;

int main() {
	char buff[1024];
	if (WSAStartup(0x0202, (WSADATA*)&buff[0]))
	{
		cout << "Error WSAStartup \n" << WSAGetLastError();   // Ошибка!
		return 1;
	}

	SOCKET s, s_new;
	int from_len;
	//int* IMBData = new int[2];
	sockaddr_in sin, from_sin;
	s = socket(AF_INET, SOCK_STREAM, 0);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = 0;
	sin.sin_port = htons(SRV_PORT);
	bind(s, (sockaddr*)&sin, sizeof(sin));
	listen(s, 3);
	while (1) {
		from_len = sizeof(from_sin);
		s_new = accept(s, (sockaddr*)&from_sin, &from_len);

		if (s_new == 0) cout << "Client connection error!\n";
		else {
			cout << "New Client was connected!" << endl;
			from_len = recv(s_new, (char*)&B, sizeof(B), 0);
			int f = 0;
			for (int i = 0; i < 4; i++) {
				if (B.a[i] == 3 && f == 0)
					answer = 0;
				if (B.a[i] == 2)
				{
					f -= 1;
					answer = f;
				}
			}

			cout << "Received Data" << endl;
			cout << "Name:" << B.name << "Physics:" << B.a[0] << "Math:" << B.a[1] << "Russian:" << B.a[2] << "Programming:" << B.a[3] << endl;
			cout << answer << endl;
			send(s_new, (char*)&answer, sizeof(answer), 0);
			cout << "Client was disconnected" << endl;
			closesocket(s_new);
		}
	}
	return 0;
}
