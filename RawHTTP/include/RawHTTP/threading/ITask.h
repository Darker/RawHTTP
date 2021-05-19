#pragma once
#include "IEventLoop.h"
namespace RawHttp
{

class ITask
{
public:
  virtual void Execute(IEventLoop* currentLoop) = 0;
};

}
