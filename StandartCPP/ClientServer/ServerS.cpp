#pragma comment(lib,"ws2_32.lib")
#include <WinSock2.h>
#include <iostream>

#pragma warning(disable: 4996)

int main(int argc, char* argv[])
{
  WSAData wsaData;
  WORD DLLVersion = MAKEWORD(2, 1);
  if (WSAStartup(DLLVersion, &wsaData) != 0)
  {
    std::cout << "Error WSA startup is faild" << std::endl;
    return 1;  
  }
  
  SOCKADDR_IN addr_in;
  int sizeofaddr = sizeof(addr_in); 
  addr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
  addr_in.sin_port = htons(1111);
  addr_in.sin_family = AF_INET;

  SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
  bind(sListen, (SOCKADDR*)&addr_in, sizeof(addr_in));
  listen(sListen, SOMAXCONN);


  SOCKET newConnection;
  newConnection = accept(sListen, (SOCKADDR*)&addr_in, &sizeofaddr);

  if(newConnection == 0)
  {
    std::cout << "Faild connection!\n";
  }
  else
  {
    std::cout << "Client connected!\n";
  }

  system("pause");
  return 0;
}