#pragma once

namespace RawHttp
{
class IEventLoop;
class ITask
{
public:
  virtual void Execute(IEventLoop* currentLoop) = 0;
};

}
