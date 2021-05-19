#pragma once
namespace RawHttp
{
class IEventLoop;

class IEventSource
{
public:
  virtual void StartProducingEvents(IEventLoop* targetLoop) = 0;
  virtual void Stop() = 0;
};

}
