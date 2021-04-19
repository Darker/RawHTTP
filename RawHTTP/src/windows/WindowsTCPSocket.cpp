#include "windows/WindowsTCPSocket.h"

#include <winsock2.h>

namespace RawHttp
{

struct WindowsTCPSocket::Private
{
  SOCKET ClientSocket = INVALID_SOCKET;
};

WindowsTCPSocket::WindowsTCPSocket(WindowsSocketPtr handle) : _private(new Private{handle}) 
{
}


WindowsTCPSocket::~WindowsTCPSocket()
{
}

size_t WindowsTCPSocket::Read(byte* buffer, size_t bufferLength)
{
  return recv(_private->ClientSocket, (char*)buffer, (int)bufferLength, 0);
}

void WindowsTCPSocket::Write(const byte* buffer, size_t bufferLength)
{
  send(_private->ClientSocket, (char*)buffer, (int)bufferLength, 0);
}

bool RawHttp::WindowsTCPSocket::HasData() const
{
  return false;
}

bool RawHttp::WindowsTCPSocket::ConnectionOk() const
{
  return false;
}

void RawHttp::WindowsTCPSocket::Close()
{
  closesocket(_private->ClientSocket);
}



}
