#include "windows/threading/WindowsEventLoop.h"
#include "windows/threading/WinEventWaitObject.h"

#include <vector>

namespace RawHttp
{
class WindowsEventLoop::PrivateData
{
public:
  std::vector<WinEventWaitObject> _tasks;
};


WindowsEventLoop::WindowsEventLoop() : _private(new PrivateData)
{

}

void WindowsEventLoop::Run()
{

}

WindowsEventLoop::TerminationMode WindowsEventLoop::Terminate(TerminationMode mode)
{
  return TerminationMode();
}

}
