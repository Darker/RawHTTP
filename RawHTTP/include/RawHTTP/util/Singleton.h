#pragma once
#include "NoCopy.h"

namespace RawHttp
{

template <class TSingleton>
class Singleton : public NoCopy
{
  friend TSingleton;
public:
  static TSingleton& GetInstance() { static TSingleton inst; return inst; }
protected:
  Singleton() = default;
};

}
