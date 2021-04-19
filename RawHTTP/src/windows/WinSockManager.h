#pragma once
#include "util/Singleton.h"

#include <memory>

namespace RawHttp
{

class WinSockManager : public Singleton<WinSockManager>
{
  friend class Singleton<WinSockManager>;
public:
  virtual ~WinSockManager();
protected:
  WinSockManager();

  //! Private internal data
  struct Private;
  //! Private internal data memory
  std::unique_ptr<Private> _private;
};

}
