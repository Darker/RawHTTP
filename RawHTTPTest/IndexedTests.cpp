#include <RawHttp/abstract/containers/IndexedCollection.h>

#include <vector>
#include <iostream>

using namespace RawHttp;

//! Template specialization for std::vector
template <typename TValue>
struct RawHttp::IndexedTraits<TValue, std::vector<TValue>>
{
  static const TValue& GetValueConst(const std::vector<TValue>& collection, size_t index) { return collection[index]; }
  static TValue& GetValue(std::vector<TValue>& collection, size_t index) { return collection[index]; }
  static size_t GetLength(const std::vector<TValue>& collection) { return collection.size(); }
};

/*!
 *  Prints each item in given abstract iterable container.
 *
 *      @tparam TValue
 *
 *      @param [in,out] iterable
 */
template <typename TValue>
void PrintAnyArrayAbstract(ArrayView<TValue, true>& iterable)
{
  int index = 0;
  for (const TValue& v : iterable)
  {
    std::cout << "iterable[" << index++ << "] = " << v << "\r\n";
  }

  //for (auto it = iterable.begin(); it != iterable.end(); ++it)
  //{
  //  const TValue& v = *it;
  //  std::cout << "iterable[" << index++ << "] = " << v << "\r\n";
  //}

  //for (size_t index = 0; index < iterable.GetLength(); ++index)
  //{
  //  const TValue& v = iterable[index];
  //  std::cout << "iterable[" << index << "] = " << v << "\r\n";
  //}
}
/*!
 *  Converts given collection to iterable construct and iterates over it.
 *
 *      @tparam TIterable
 *      @tparam TValue
 *
 *      @param [in] iterable IterableImpl has implicit ctor from the given Iterable type, so collections may be passed directly
 */
template <class TIterable, typename TValue>
void PrintAnyArray(ArrayViewImpl<TIterable, TValue, true> iterable)
{
  PrintAnyArrayAbstract(iterable);
}

template <class TIterable, typename TValue>
void SetAnyArray(ArrayViewImpl<TIterable, TValue, false> iterable, const TValue& desiredValue)
{
  for (TValue& val : iterable)
  {
    val = desiredValue;
  }
}

int main()
{
  std::vector<int> test1{ 3,4,6,323,54,43,76 };
  PrintAnyArray<std::vector<int>, int>(test1);
  SetAnyArray<std::vector<int>, int>(test1, 15);
  PrintAnyArray<std::vector<int>, int>(test1);
}