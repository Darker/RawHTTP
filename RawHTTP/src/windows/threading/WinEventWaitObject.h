#pragma once
#include "threading/IWaitObject.h"
#include "datatypes/typedefs.h"

#include "windows.h"

#include <vector>
#include <limits>

namespace RawHttp
{

class WinEventWaitObject : public IWaitObject
{
public:
  enum class WinWaitStatus : size_t
  {
    Timeout = WAIT_TIMEOUT,
    Failed = WAIT_FAILED,
    Success = WAIT_OBJECT_0,
    Abandoned = WAIT_ABANDONED_0,
  };

  //! Wait for this and all given objects. These objects MUST be of the same type
  virtual WaitResult WaitFor(const ArrayView<IWaitObject*, false>& objects, bool all, TimeInterval timeout, bool noExceptions = false);
  //! Provides string object type. Object types with the same type are compatible and can wait within the same thread
  virtual const char* GetType() const { return "windows-event"; }
  virtual HANDLE GetEventHandle() const = 0;

};

}