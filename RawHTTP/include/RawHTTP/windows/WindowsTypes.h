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
constexpr Handle Null = NULL;
constexpr Handle InvalidHandle = INVALID_HANDLE_VALUE;
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
constexpr Handle Null = nullptr;
constexpr Handle InvalidHandle = (Handle)(long long)-1;
}
}
#endif //_WIN32