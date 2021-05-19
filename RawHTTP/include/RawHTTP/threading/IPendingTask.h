#pragma once
#include "ITask.h"
#include "IWaitObject.h"
namespace RawHttp 
{

class IPendingTask
{
public:
  virtual bool IsWaitingDone() const = 0;
  virtual ITask* GetTask() = 0;
  virtual const ITask* GetTask() const { return const_cast<IPendingTask*>(this)->GetTask(); }
  virtual IWaitObject* GetWaitObject() = 0;
  virtual const IWaitObject* GetWaitObject() const { return const_cast<IPendingTask*>(this)->GetWaitObject(); }
};

}
