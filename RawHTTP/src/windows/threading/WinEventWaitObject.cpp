#include "WinEventWaitObject.h"

HANDLE RawHttp::WinEventWaitObject::GetEventHandle() const
{
  return HANDLE();
}

bool RawHttp::WinEventWaitObject::Wait(Iterable<WinEventWaitObject*>& objects, bool all, int waitMsMax)
{
  while (!objects.End())
  {
    const WinEventWaitObject* obj = objects.GetValue();

  }
  return false;
}
