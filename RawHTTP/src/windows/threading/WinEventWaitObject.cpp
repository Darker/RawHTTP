#include "WinEventWaitObject.h"
#include "../util/ErrorHelpers.h"

namespace RawHttp
{
/**
 * @param objects
 * @param all
 * @param timeout
 */
IWaitObject::WaitResult WinEventWaitObject::WaitFor(const ArrayView<IWaitObject*, false>& objects, bool all, TimeInterval timeout, bool noExceptions)
{
  constexpr auto MaxWaitObjs = MAXIMUM_WAIT_OBJECTS;
  constexpr auto MinSuccessIndex = WAIT_OBJECT_0;
  constexpr auto MaxSuccessIndex = MinSuccessIndex + MaxWaitObjs;

  std::vector<HANDLE> handles;
  objects.Map<HANDLE>(handles, [](IWaitObject* obj) { return static_cast<WinEventWaitObject*>(obj)->GetEventHandle(); });
  const DWORD result = WaitForMultipleObjects(handles.size(), handles.data(), all, timeout.ToMilliSeconds());
  if (result >= MinSuccessIndex && result <= MaxSuccessIndex)
  {
    const size_t index = result - MinSuccessIndex;
    return { WaitResultStatus::Success, objects[index], index };
  }
  else if (result == WAIT_TIMEOUT)
  {
    return { WaitResultStatus::Timeout };
  }
  else if (result == WAIT_FAILED)
  {
    if (noExceptions)
    {
      return { WaitResultStatus::Error };
    }
    else
    {
      throw WaitException(std::string("Failed to wait on Windows object(s): ") + GetLastErrorAsString());
    }
  }
  else if (result == WAIT_ABANDONED_0)
  {
    if (noExceptions)
    {
      return { WaitResultStatus::Error };
    }
    else
    {
      throw WaitException("WinEventWaitObject cannot handle abandoned objects yet!");
    }
  }
  else
  {
    if (noExceptions)
    {
      return { WaitResultStatus::Error };
    }
    else
    {
      throw WaitException("Unknown result from WaitForMultipleObjects!");
    }
  }
}

HANDLE WinEventWaitObject::GetEventHandle() const
{
  return HANDLE();
}
}
