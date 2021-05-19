#pragma once
#include <stdexcept>
namespace RawHttp
{

class GenericError : public std::runtime_error
{
  using std::runtime_error::runtime_error;
};

}
