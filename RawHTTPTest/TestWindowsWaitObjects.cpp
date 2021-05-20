#include <RawHTTP/windows/threading/waitObjects/WindowsTimer.h>
#include <RawHTTP/abstract/units/Time.h>
#include <RawHTTP/abstract/containers/IndexedCollection.h>
#include <RawHTTP/abstract/containers/IndexedTraitDefs.h>

#include <iostream>
#include <vector>
int main()
{
  using namespace RawHttp::Units;
  RawHttp::WindowsTimer timer(10_s);
  timer.Start();
  std::vector<RawHttp::IWaitObject*> timers{ &timer };
  
  std::cout << "Starting the wait.\r\n";
  timer.WaitFor(RawHttp::ArrayViewImpl<std::vector< RawHttp::IWaitObject*>, RawHttp::IWaitObject*, false>(timers), false, 100_s);
  std::cout << "Wait over.\r\n";
  return 0;
}