#pragma once
#include "../ITcpListener.h"
#include "../Types.h"

#include <memory>

namespace RawHttp
{

class WindowsTCPListener : public ITCPListener
{
public:
  WindowsTCPListener(IPAddress listenAddr);

  virtual ~WindowsTCPListener();

  // Inherited via ITCPListener
  virtual void Start() override;
  virtual void Close() override;
  virtual void OnClient(const ClientCallback& cb) override;
protected:
  //! Private internal data
  struct Private;
  //! Private internal data memory
  std::unique_ptr<Private> _private;
  //! address to listen on
  IPAddress _addr;
  //! Callback to call if client connects
  ClientCallback _clientCb;
};

}
