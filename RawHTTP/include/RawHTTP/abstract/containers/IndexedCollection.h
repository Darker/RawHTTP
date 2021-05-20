#pragma once
#include "BasicIterator.h"
#include "../callbacks/ItemCallbacks.h"

#include <cstddef>
#include <vector>

namespace RawHttp
{

/*!
*  These are template traits for collections 
*  
*  @tparam TValue Type of values that are in the collection that is described by these traits
*  @tparam TCollection The collection described by the traits
*  
*  
*  */
template <typename TValue, class TCollection>
struct IndexedTraits
{
  static const TValue& GetValueConst(const TCollection& collection, size_t index) {}// { static_assert(false, "Implementation is missing for this type"); }
  static TValue& GetValue(TCollection& collection, size_t index) {}// { static_assert(false, "Implementation is missing for this type"); }
  static size_t GetLength(const TCollection& collection) { return 0; }//{ static_assert(false, "Implementation is missing for this type"); }
};


template <typename TValue, bool is_const = true>
class ArrayView
{
public:

  template <bool is_const_iterator = true>
  class Iterator : public BasicIterator<TValue, size_t, is_const_iterator || is_const>
  {
    static constexpr const bool is_const_i = (is_const || is_const_iterator);
    using BaseClass = BasicIterator<TValue, size_t, is_const_i>;
    using ViewType = typename std::conditional<is_const_i, const ArrayView, ArrayView>::type;
    using ValueType = typename BaseClass::ValueType;
  public:
    //! Initializes the view and the index.The view must remain in existence while this object is used
    Iterator(ViewType& view, size_t index = 0) : BaseClass(index), _view(view) {}

    //! Provides refference to the current value
    virtual ValueType& operator*() const override { return _view[BaseClass::GetIndex()]; }
    //! Post increment operator
    Iterator operator++() { const Iterator old = *this; BaseClass::operator++(); return old; }
  private:
    ViewType& _view;
  };


  //! Allows access to const value refs
  virtual const TValue& operator[](size_t index) const = 0;
  //! Conditionally allowed non const operator in case the value is not const
  template <bool is_non_const = !is_const>
  TValue& operator[](typename std::enable_if <(is_non_const), size_t>::type index) { return GetNonConst(index); }
  //! Returns length of the collection
  virtual size_t GetLength() const = 0;
  //! Fills the std vector with items of this view mapped by given callback. The vector will not be cleared before use.
  template<typename TNewType>
  void Map(std::vector<TNewType>& itemsTarget, const cb::Mapper<TValue, TNewType>& mapper) const;

  /* for( : ) methods */
  Iterator<true> begin() const { return Iterator<true>(*this, 0); }
  Iterator<true> end() const { return Iterator<true>(*this, GetLength()); }
  //! Only enabled if this is not a const view
  template <bool is_non_const = !is_const>
  Iterator<false> begin(typename std::enable_if <(is_non_const), int>::type*v=nullptr) { return Iterator<false>(*this, 0); }
  template <bool is_non_const = !is_const>
  Iterator<false> end(typename std::enable_if <(is_non_const), int>::type*v = nullptr) { return Iterator<false>(*this, GetLength()); }
protected:
  //! Called from the non-virtual operator, which is only available when the template is set to non const mode
  virtual TValue& GetNonConst(size_t index) = 0;
};

template<typename TValue, bool is_const> template <typename TNewType>
void ArrayView<TValue, is_const>::Map(std::vector<TNewType>& itemsTarget, const cb::Mapper<TValue, TNewType>& mapper) const
{
  for (const TValue& value : *this)
  {
    itemsTarget.push_back(mapper(value));
  }
}


template <class TCollection, typename TValue, bool is_const = true>
class ArrayViewImpl : public ArrayView<TValue, is_const>
{
  using IndexTraits = IndexedTraits<TValue, TCollection>;
  using CollectionType = typename std::conditional<is_const, const TCollection, TCollection>::type;
public:

  ArrayViewImpl(CollectionType& collection) : _collection(collection) {}
  //template <typename = typename std::enable_if <is_const>::type>
  //ArrayViewImpl(TCollection& collection) : _collection(collection) {}

  virtual const TValue& operator[](size_t index) const override { return IndexTraits::GetValueConst(_collection, index); }
  virtual size_t GetLength() const override { return IndexTraits::GetLength(_collection); }

protected:
  //! The nasty const cast here assumes that this will not be called from const template implementation as it has no non const operator[]
  virtual TValue& GetNonConst(size_t index) override { return IndexTraits::GetValue(const_cast<TCollection&>(_collection), index); }
private:
  CollectionType& _collection;
};

}

