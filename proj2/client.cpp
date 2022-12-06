#include <iostream> 
#define _WINSOCK_DEPRECATED_NO_WARNINGS 
#include <winsock2.h>
#include <string>
#include <windows.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma warning(disable: 4996) 
using namespace std;
#define SRV_HOST "localhost" 
#define SRV_PORT 1234
#define CLNT_PORT 1235 
#define BUF_SIZE 64 

struct Person
{
    string name; 
    int a[4];
}A;

int answer;



int main() {
    setlocale(LC_ALL, "Russian");
    char buff[1024];
    if (WSAStartup(0x0202, (WSADATA*)&buff[0])) {
        cout << "Error WSAStartup \n" << WSAGetLastError();  // Ошибка!
        return 1;
    }
    SOCKET s;
    int from_len;   char buf[BUF_SIZE] = { 0 };    
    hostent* hp;
    sockaddr_in clnt_sin, srv_sin;
    s = socket(AF_INET, SOCK_STREAM, 0);
    clnt_sin.sin_family = AF_INET;
    clnt_sin.sin_addr.s_addr = 0;
    clnt_sin.sin_port = htons(CLNT_PORT);
    bind(s, (sockaddr*)&clnt_sin, sizeof(clnt_sin));
    hp = gethostbyname(SRV_HOST);
    srv_sin.sin_port = htons(SRV_PORT);
    srv_sin.sin_family = AF_INET;
    ((unsigned long*)&srv_sin.sin_addr)[0] =
        ((unsigned long**)hp->h_addr_list)[0][0];
    connect(s, (sockaddr*)&srv_sin, sizeof(srv_sin));
    int answer;
    
    cout << "Input Name and marks: ";
    cin >> A.name >> A.a[0] >> A.a[1] >> A.a[2] >> A.a[3];
    int* Data = new int[4] {A.a[0], A.a[1], A.a[2], A.a[3]};
    send(s, (char*)&A, sizeof(A), 0);

    from_len = recv(s, (char*)&answer, sizeof(answer), 0);
    
    if (from_len != sizeof(answer)) {
        cout << "Data recive error";
        return 1;
    }
    else {
        cout << A.name << " has ";
        int n;
        if (answer < 0) { n = answer * (-1); answer = -1; }
        switch (answer) {
        case -1: {cout << "Плохая учёба, стипендия отсутсвует, задолженностей " << n << endl; break; };
        case 0: {cout << "Нормальная учёба, стипендия отсутствует" << endl; break; };
        case 1: {cout << "Отличная учёба, стипендия 1800" << endl; break; };
        }

    }

    Sleep(5000);
    closesocket(s);
    return 0;
}
