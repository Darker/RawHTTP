#include "AsyncReadFile.h"
namespace RawHttp
{

struct AsyncReadFile::Private
{
  OVERLAPPED ovlData = { 0 };
  HANDLE openFile = Win::Null;
};
AsyncReadFile::AsyncReadFile(const std::wstring& name, size_t start, size_t length) 
  : _private(new Private)
  , _start(start)
  , _length(length)
  , _name(name)
{
  //BOOL ReadFile(
  //  HANDLE       hFile,
  //  LPVOID       lpBuffer,
  //  DWORD        nNumberOfBytesToRead,
  //  LPDWORD      lpNumberOfBytesRead,
  //  LPOVERLAPPED lpOverlapped
  //);
  _private->openFile = CreateFileW(_name.data(), GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
    FILE_FLAG_OVERLAPPED, NULL);
  _private->ovlData.hEvent = CreateEventA(NULL, TRUE, FALSE, NULL);
}

bool AsyncReadFile::Start()
{
  return false;
}

}


