#pragma once
#include <abstract/containers/Iterable.h>
#include <abstract/units/Time.h>

namespace RawHttp 
{

class IWaitObject
{
public:
  //! Wait for this and all given objects. These objects MUST be of the same type
  virtual void WaitFor(Iterable<IWaitObject*> objects, bool all, TimeInterval timeout) = 0;
  //! Provides string object type. Object types with the same type are compatible and can wait within the same thread
  virtual const char* GetType() const = 0;

};


}
