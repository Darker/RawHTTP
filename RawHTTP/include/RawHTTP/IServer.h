#pragma once

namespace RawHttp 
{

class IServer
{
public:
  //! Starts listening on set address and port, must not block during this operation
  virtual void Start() = 0;
};

}
