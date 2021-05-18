#pragma once
#include "threading/IEventLoop.h"
#include <memory>

namespace RawHttp
{

class WindowsEventLoop : public IEventLoop
{
public:
  WindowsEventLoop();

  // Inherited via IEventLoop
  virtual void Run() override;
  virtual TerminationMode Terminate(TerminationMode mode) override;
private:
  class PrivateData;
  std::unique_ptr<PrivateData> _private;
};


}
