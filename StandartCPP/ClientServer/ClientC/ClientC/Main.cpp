#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>

#pragma warning(disable:4996)

SOCKET Connection;

void ClientHandler()
{
  char msg[256];
  while (true)
  {
    recv(Connection, msg, sizeof(msg), NULL);
    std::cout << msg << std::endl;
  }
}

int main(int argc, char* argv[])
{
  WSAData wsaData;
  WORD DllVersion = MAKEWORD(2, 1);
  if (WSAStartup(DllVersion, &wsaData) != 0)
  {
    std::cout << "Somthing wrong by connection";
    exit(1);
  }

  SOCKADDR_IN addr_in;
  int sizeofaddrin = sizeof(addr_in);
  addr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr_in.sin_port = htons(1234);
  addr_in.sin_family = AF_INET;

  Connection = socket(AF_INET, SOCK_STREAM, NULL);
  if (connect(Connection, (SOCKADDR*)&addr_in, sizeof(addr_in)) != 0)
  {
    std::cout << "Error connecting!!\n";
    return 1;
  }

  std::cout << "Sucsess boy\n";

  CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler, NULL, NULL, NULL);
  char msgl[256];
  while (true)
  {
    std::cin.getline(msgl, sizeof(msgl));
    send(Connection, msgl, sizeof(msgl), NULL);
    Sleep(10);
  }

  system("pause");
  return 0;
}