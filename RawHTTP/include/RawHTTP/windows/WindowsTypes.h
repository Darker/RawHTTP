#pragma once
#ifdef _WIN32
#include "windows.h"

namespace RawHttp
{
namespace Win
{

using Bool = BOOL;
using Handle = HANDLE;
using Dword = DWORD;
constexpr const Handle Null = NULL;
constexpr const Handle InvalidHandle = static_cast<Handle>(INVALID_HANDLE_VALUE);
}
}
#else
namespace RawHttp
{
namespace Win
{

using Bool = bool;
using Handle = void *;
using Dword = unsigned long;
constexpr const Handle Null = nullptr;
constexpr const Handle InvalidHandle = (Handle)(long long)-1;
}
}
#endif //_WIN32