#pragma once
namespace RawHttp
{

class IEventLoop
{
public:
  //! Moide in which the loop should terminate
  enum class TerminationMode
  {
    //! Loop should stop ASAP, do not accept new tasks or dispatch notifications
    Kill,
    //! Finish tasks in the queue but do not accept new ones
    FinishTasks,
    //! Wait for the task queue to naturally become empty, accepting new tasks
    Wait,
    //! Does not terminate
    NoTermination
  };

  virtual ~IEventLoop() = default;

  //! Runs the loop and blocks until it's explicitly terminated
  virtual void Run() = 0;
  //! Terminates the loop. Stricter termination mode can override previous rest strict call, but not the other way around. Returns current termination mode
  virtual TerminationMode Terminate(TerminationMode mode) = 0;
  //! Adds a task to be executed to the event loop

protected:

};

}
