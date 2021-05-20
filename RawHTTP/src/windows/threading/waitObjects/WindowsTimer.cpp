#include "windows/threading/waitObjects/WindowsTimer.h"

void RawHttp::WindowsTimer::Start()
{
  _handle = CreateWaitableTimerW(NULL, true, NULL);
  LARGE_INTEGER dueTime;
  dueTime.QuadPart = _delay.To100sOfNanoSeconds() * -1LL;
  BOOL result = ::SetWaitableTimer(_handle, &dueTime, 0, NULL, NULL, FALSE);
  //::SetWaitableTimer(_handle, )
  //BOOL SetWaitableTimer(
  //  HANDLE              hTimer,
  //  const LARGE_INTEGER *lpDueTime,
  //  LONG                lPeriod,
  //  PTIMERAPCROUTINE    pfnCompletionRoutine,
  //  LPVOID              lpArgToCompletionRoutine,
  //  BOOL                fResume
  //);
}
