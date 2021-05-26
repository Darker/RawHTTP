#pragma once
#include "../../threading/IWaitObject.h"
#include "../../datatypes/typedefs.h"
#include "../WindowsTypes.h"

#include "windows.h"

#include <vector>
#include <limits>

namespace RawHttp
{

class WinEventWaitObject : public IWaitObject
{
public:
  //! Virtual destructor to allow destruction via IWaitObject*
  virtual ~WinEventWaitObject();

  //! Wait for this and all given objects. These objects MUST be of the same type
  virtual WaitResult WaitFor(const ArrayView<IWaitObject*, false>& objects, bool all, TimeInterval timeout, bool noExceptions = false);
  //! Provides string object type. Object types with the same type are compatible and can wait within the same thread
  virtual const char* GetType() const override { return "windows-event"; }
  virtual Win::Handle GetEventHandle() const = 0;

};

}