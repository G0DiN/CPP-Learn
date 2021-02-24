#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <string>
#include <iostream>

#pragma warning(disable:4996)

SOCKET Connection;

void ClientHandler()
{
  int msg_size;
  while (true)
  {
    recv(Connection, (char*)&msg_size, sizeof(int), NULL);
    char* msg = new char[msg_size + 1];
    msg[msg_size] = '\0';
    recv(Connection, msg, msg_size, NULL);
    std::cout << msg << std::endl;

    delete[] msg;
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

  std::string msgl;
  while (true)
  {
    std::getline(std::cin, msgl);
    int msgl_size = msgl.size();
    send(Connection, (char*)&msgl_size, sizeof(int), NULL);
    send(Connection, msgl.c_str(), msgl_size, NULL);
    Sleep(10);
  }

  system("pause");
  return 0;
}