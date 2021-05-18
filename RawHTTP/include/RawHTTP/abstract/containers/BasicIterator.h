#pragma once
#include <type_traits>

namespace RawHttp
{
//! Basic iterator template for making iterators for both const and modifiable cases
template<typename TValue, typename TIndex, bool is_const_iterator = true>
class BasicIterator
{
public:
  //! Decides between const or non const value
  using ValueType = typename std::conditional<is_const_iterator, const TValue, TValue>::type;

  //! Iterator starts at the beginning
  BasicIterator() : BasicIterator(0) {}
  //! Create iterator starting at index
  BasicIterator(TIndex index) :  _index(index) {}

  //! Move the iterator one step
  BasicIterator& operator++() { ++_index; return *this; }
  //! Returns true if the current iterator index is the same as the other one
  bool operator==(const BasicIterator& other) const { return _index == other._index; }
  //! Returns negative of operator==
  bool operator!=(const BasicIterator& other) const { return !(other == *this); }
  //! Provides refference to the current value
  virtual ValueType& operator*() const = 0;
protected:
  //! Cast to index type
  TIndex GetIndex() const { return _index; }
private:
  //! Current iterator index
  TIndex _index = 0;
};

}
