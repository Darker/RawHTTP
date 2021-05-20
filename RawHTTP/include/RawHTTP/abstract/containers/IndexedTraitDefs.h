#pragma once
#include "IndexedCollection.h"

#include <vector>

namespace RawHttp
{
//! Template specialization for std::vector
template <typename TValue>
struct IndexedTraits<TValue, std::vector<TValue>>
{
  static const TValue& GetValueConst(const std::vector<TValue>& collection, size_t index) { return collection[index]; }
  static TValue& GetValue(std::vector<TValue>& collection, size_t index) { return collection[index]; }
  static size_t GetLength(const std::vector<TValue>& collection) { return collection.size(); }
};
}