#pragma once
#include "../ITCPSocket.h"

#include <array>

namespace RawHttp
{

class WindowsTCPSocket : public ITCPSocket
{
  friend class WindowsTCPListener;
public:

  virtual ~WindowsTCPSocket();

  // Inherited via ITCPSocket
  virtual size_t Read(byte* buffer, size_t bufferLength) override;
  virtual void Write(const byte* buffer, size_t bufferLength) override;
  virtual bool HasData() const override;
  virtual bool ConnectionOk() const override;
  virtual void Close() override;
protected:
  using WindowsSocketPtr = unsigned __int64;

  //! Create socket from windows handle
  WindowsTCPSocket(WindowsSocketPtr handle);

  //! Private internal data
  struct Private;
  //! Private internal data memory
  std::unique_ptr<Private> _private;
  //! Data buffer for reading
  std::array<byte, 512> _buffer;
};

}