#pragma once
#include "Types.h"

#include <streambuf>
#include <array>

namespace RawHttp 
{

class ITCPSocket : public std::streambuf
{
public:

  virtual ~ITCPSocket() = default;

  //! Reads at most N bytes from socket, reads only available data and does not block.
  template<size_t N>
  size_t Read(std::array<byte, N>& buffer) { return Read(buffer.data(), N); }
  //! Reads at most bufferLength bytes from socket, reads only available data and does not block.
  virtual size_t Read(byte* buffer, size_t bufferLength) = 0;
  //! Writes the buffer into the socket, blocks until done, throws on failure
  virtual void Write(const byte* buffer, size_t bufferLength) = 0;
  //! Returns true if any data is available to be read
  virtual bool HasData() const = 0;
  //! Returns true if connection is OK
  virtual bool ConnectionOk() const = 0;
  //! Closes the socket, ConnectionOk must return false immediatelly after this call
  virtual void Close() = 0;
};

}
