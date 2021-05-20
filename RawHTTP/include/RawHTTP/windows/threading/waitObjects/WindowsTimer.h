#pragma once
#include "../WinEventWaitObject.h"
#include "../../WindowsTypes.h"

namespace RawHttp 
{

class WindowsTimer : public WinEventWaitObject
{
public:
  WindowsTimer(TimeInterval delay) : _delay(delay) {}
  virtual Win::Handle GetEventHandle() const override { return _handle; }
  void Start();
private:
  Win::Handle _handle = Win::Null;
  TimeInterval _delay;
};

}