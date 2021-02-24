#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>

#pragma warning(disable:4996)

int main()
{
  WSAData wsaData;
  WORD DLLVersion = MAKEWORD(2, 1);
  if (WSAStartup(DLLVersion, &wsaData) != 0)
  {
    std::cout << "Error" << std::endl;
    exit(1);
  }

  SOCKADDR_IN addr_in;
  int sizeofaddrin = sizeof(addr_in);
  addr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr_in.sin_port = htons(1234);
  addr_in.sin_family = AF_INET;

  SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
  bind(sListen, (SOCKADDR*)&addr_in, sizeof(addr_in));
  listen(sListen, SOMAXCONN);

  SOCKET newConnection;
  newConnection = accept(sListen, (SOCKADDR*)&addr_in, &sizeofaddrin);

  if (newConnection == 0)
    std::cout << "Error by listen to connect\n";
  else
  {
    std::cout << "Sucsess by listen! Congradulations\n";
    char msg[256] = "Hello you real good man, it's your second network programm!!!";
    send(newConnection, msg, sizeof(msg), NULL);
  }

  system("pause");
  return 0;
}