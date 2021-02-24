#pragma comment(lib, "ws2_32.lib")
#include <WinSock2.h>
#include <iostream>

#pragma warning(disable:4996)

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

  SOCKET con = socket(AF_INET, SOCK_STREAM, NULL);
  if (connect(con, (SOCKADDR*)&addr_in, sizeof(addr_in)) != 0)
  {
    std::cout << "Error connecting!!\n";
    return 1;
  }

  std::cout << "Sucsess boy\n";
  char acceptMSG[256];
  recv(con, acceptMSG, sizeof(acceptMSG), NULL);
  std::cout << acceptMSG << std::endl;


  system("pause");
  return 0;
}