#pragma once
#include "abstract/containers/Iterable.h"
#include "threading/IWaitObject.h"

#include "windows.h"

#include <vector>
#include <limits>

namespace RawHttp
{

class WinEventWaitObject : public IWaitObject
{
public:
  enum class WaitStatus
  {
    Timeout = WAIT_TIMEOUT,
    Failed = WAIT_FAILED,
    Success = WAIT_OBJECT_0,
    Abandoned = WAIT_ABANDONED_0,
  };
  struct WaitResult
  {
    WaitStatus status;
    HANDLE firstSignaledEvent = NULL;
    size_t firstSignaledEventIndex = std::numeric_limits<size_t>::max();
  };

  template <class TIterable>
  static bool Wait(IterableImpl<TIterable, WinEventWaitObject*> objects, bool all, int waitMsMax);
  
  virtual HANDLE GetEventHandle() const;

private:
  static bool Wait(Iterable<WinEventWaitObject*>& objects, bool all, int waitMsMax);
};

template<class TIterable>
bool WinEventWaitObject::Wait(IterableImpl<TIterable, WinEventWaitObject*> objects, bool all, int waitMsMax)
{
  //std::vector<HANDLE> handles;
  //while (objects.HasNext())
  //{
  //  const WinEventWaitObject& obj = objects.Next();
  //  handles.push_back(obj.GetEventHandle());
  //}
  return Wait(objects, all, waitMsMax);
}
}
