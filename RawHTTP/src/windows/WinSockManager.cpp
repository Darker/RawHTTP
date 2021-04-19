#include "WinSockManager.h"

#include <winsock2.h>
#include <ws2tcpip.h>

namespace RawHttp
{

struct WinSockManager::Private
{
  WSADATA wsaData;
};

WinSockManager::~WinSockManager()
{
  WSACleanup();
}

WinSockManager::WinSockManager() : _private(new Private)
{
  int iResult = WSAStartup(MAKEWORD(2, 2), &_private->wsaData);
  if (iResult != 0)
  {
    printf("WSAStartup failed with error: %d\n", iResult);
  }
}

}