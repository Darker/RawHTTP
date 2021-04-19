#include "windows/WindowsTCPListener.h"
#include "windows/WindowsTCPSocket.h"
#include "./WinSockManager.h"

#include <winsock2.h>
#include <ws2tcpip.h>

#include <stdio.h>

#include <string>

namespace RawHttp
{

struct WindowsTCPListener::Private
{
  SOCKET ListenSocket = INVALID_SOCKET;
  WSADATA wsaData;
};

WindowsTCPListener::WindowsTCPListener(IPAddress listenAddr) : _addr(listenAddr), _private(new Private)
{

}

WindowsTCPListener::~WindowsTCPListener()
{
}

void WindowsTCPListener::Start()
{
  WinSockManager& man = WinSockManager::GetInstance();

  // Initialize Winsock
  int iResult = WSAStartup(MAKEWORD(2, 2), &_private->wsaData);
  if (iResult != 0)
  {
    printf("WSAStartup failed with error: %d\n", iResult);
  }

  struct addrinfo *result = NULL;
  struct addrinfo hints;

  ZeroMemory(&hints, sizeof(hints));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;
  hints.ai_flags = AI_PASSIVE;

  std::string portStr = std::to_string(_addr.port);

  // Resolve the server address and port
  iResult = getaddrinfo(NULL, portStr.c_str(), &hints, &result);
  if (iResult != 0)
  {
    printf("getaddrinfo failed with error: %d\n", iResult);
  }

  // Create a SOCKET for connecting to server
  _private->ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
  if (_private->ListenSocket == INVALID_SOCKET)
  {
    printf("socket failed with error: %ld\n", WSAGetLastError());
    freeaddrinfo(result);
  }

  iResult = bind(_private->ListenSocket, result->ai_addr, (int)result->ai_addrlen);
  if (iResult == SOCKET_ERROR)
  {
    printf("bind failed with error: %d\n", WSAGetLastError());
    
    closesocket(_private->ListenSocket);
  }
  freeaddrinfo(result);

  iResult = listen(_private->ListenSocket, SOMAXCONN);
  if (iResult == SOCKET_ERROR)
  {
    printf("listen failed with error: %d\n", WSAGetLastError());
    closesocket(_private->ListenSocket);
  }

  while (true)
  {
    // Accept a client socket
    SOCKET ClientSocket = accept(_private->ListenSocket, NULL, NULL);
    if (ClientSocket == INVALID_SOCKET)
    {
      printf("accept failed with error: %d\n", WSAGetLastError());
      closesocket(_private->ListenSocket);
      break;
    }
    WindowsTCPSocket sock = WindowsTCPSocket(ClientSocket);
    _clientCb(&sock);
  }
}
void WindowsTCPListener::Close()
{
  closesocket(_private->ListenSocket);
}
void WindowsTCPListener::OnClient(const ClientCallback& cb)
{
  _clientCb = cb;
}

}
