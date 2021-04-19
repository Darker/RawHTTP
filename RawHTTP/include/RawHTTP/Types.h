#pragma once
#include <array>

namespace RawHttp
{

using byte = unsigned char;

using PortNumber = int;

struct IPAddress
{
  enum class Type
  {
    IPV4,
    IPV6
  };

  Type type;
  std::array<byte, 16> octets;
  PortNumber port;
};

}
