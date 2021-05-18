#include <RawHTTP/abstract/containers/Iterable.h>
using namespace RawHttp;

#include <vector>
#include <iostream>

/*!
 *  Template specialization for std::vector
 *
 *      @tparam TValue Value of the vector
 *      @tparam std::vector<TValue> 
 */
template <typename TValue>
struct RawHttp::IterableTraits<TValue, std::vector<TValue>>
{
  using Iterator = size_t;

  static Iterator CreateIterator(const std::vector<TValue>& collection) { return 0; }
  static const TValue& GetCurrentConst(const std::vector<TValue>& collection, const Iterator& iterator) { return collection[iterator]; }
  static TValue& GetCurrent(std::vector<TValue>& collection, const Iterator& iterator) { return collection[iterator]; }
  static bool IsEnd(const std::vector<TValue>& collection, const Iterator& iterator) { return iterator >= collection.size(); }
  static void AdvanceIterator(const std::vector<TValue>& collection, Iterator& iterator) { ++iterator; }
};

/*!
 *  Template specialization that allows iterating over const char*
 *
 *      @tparam char  Value type of char* collection is char
 *      @tparam char* 
 */
template <>
struct RawHttp::IterableTraits<char, char*>
{
  using Iterator = size_t;

  static Iterator CreateIterator(const char* collection) { return 0; }
  static const char& GetCurrentConst(const char* collection, const Iterator& iterator) { return collection[iterator]; }
  static bool IsEnd(const char* collection, const Iterator& iterator) { return *(collection + iterator) == 0; }
  static void AdvanceIterator(const char* collection, Iterator& iterator) { ++iterator; }
};

/*!
 *  Prints each item in given abstract iterable container.
 *
 *      @tparam TValue 
 *
 *      @param [in,out] iterable 
 */
template <typename TValue>
void PrintAnyArrayAbstract(Iterable<TValue>& iterable)
{
  while (!iterable.End())
  {
    std::cout << "  " << iterable.GetValue() << "\r\n";
    iterable.Next();
  }
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
void PrintAnyArray(IterableImpl<TIterable, TValue> iterable)
{
  PrintAnyArrayAbstract(iterable);
}

int main()
{
  const char* testStr = "StackOverflow";
  std::cout << "Chars of string:\r\n";
  PrintAnyArray<char*, char>(const_cast<char*>(testStr));
  std::cout << "  " << "\r\n";
  std::vector<int> numbers = { 1,2,3,4,5 };
  std::cout << "Numbers: \r\n";
  PrintAnyArray<std::vector<int>, int>(numbers);
}


