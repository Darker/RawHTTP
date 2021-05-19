#pragma once
#include <string>
namespace RawHttp 
{

//Returns the last Win32 error, in string format. Returns an empty string if there is no error.
std::string GetLastErrorAsString();

}
