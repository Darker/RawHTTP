#pragma once

namespace RawHttp
{

class Task
{
  friend class IEventLoop;
public:
  enum class Status
  {
    //! Task is initialized but not schleduled to be executed
    Initialized,
    //! Task has pending result
    Pending,
    //! Task finished with an error
    Error,
    //! Task finished with a result value
    Result
  };

  //! Get task status (thread safe)
  virtual Status GetStatus() = 0;
  //! 
};

}

