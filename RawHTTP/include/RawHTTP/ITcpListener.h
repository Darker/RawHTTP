#pragma once
#include <functional>

namespace RawHttp
{

class ITCPSocket;

class ITCPListener
{
public:
  //! Callback for clients
  using ClientCallback = std::function<void(ITCPSocket* socket)>;

  //! virtual destructor for polymorphism
  virtual ~ITCPListener() = default;

  //! Start listening for connections, must not block
  virtual void Start() = 0;
  //! Stop listening and close any pending connections
  virtual void Close() = 0;
  //! Sets handler that will receive connected clients
  virtual void OnClient(const ClientCallback& cb) = 0;
};

}