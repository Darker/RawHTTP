#pragma once
#include <functional>
namespace RawHttp 
{

namespace cb
{
/**
 * @tparam TValue the value to be mapped from
 * @tparam TNewValue the value to be mapped to
 */
template <typename TValue, typename TNewValue>
using Mapper = std::function<TNewValue(const TValue&)>;
template <typename TValue>
using Predicate = std::function<bool(const TValue&)>;

//template <typename TValue>
//using Identity = [](const TValue& v) { return (TValue)v; };

}

}
