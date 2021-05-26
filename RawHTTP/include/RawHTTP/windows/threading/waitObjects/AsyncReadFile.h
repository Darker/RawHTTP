#pragma once
#include "../WinEventWaitObject.h"
#include "../../WindowsTypes.h"

#include <string>
#include <memory>

namespace RawHttp
{

class AsyncReadFile : public WinEventWaitObject
{
public:
  AsyncReadFile(const std::wstring& name, size_t start, size_t length);
  bool Start();
  virtual Win::Handle GetEventHandle() const;
private:
  struct Private;
  std::unique_ptr<Private> _private;
  size_t _start = 0;
  size_t _length = 0;
  std::wstring _name;
};

}