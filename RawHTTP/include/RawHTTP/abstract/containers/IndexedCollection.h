#pragma once
#include "BasicIterator.h"
#include <cstddef>

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

  using IteratorBaseClass = BasicIterator<TValue, size_t, is_const>;
  class Iterator : public IteratorBaseClass
  {
    using ViewType = typename std::conditional<is_const, const ArrayView, ArrayView>::type;
    using ValueType = typename IteratorBaseClass::ValueType;
  public:
    //! Initializes the view and the index.The view must remain in existence while this object is used
    Iterator(ViewType& view, size_t index = 0) : IteratorBaseClass(index), _view(view) {}

    //! Provides refference to the current value
    virtual ValueType& operator*() const override { return _view[IteratorBaseClass::GetIndex()]; }
    //! Post increment operator
    Iterator operator++() { const Iterator old = *this; IteratorBaseClass::operator++(); return old; }
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

  /* for( : ) methods */
  Iterator begin() const { return Iterator(*this, 0); }
  Iterator end() const { return Iterator(*this, GetLength() - 1); }
  //! Only enabled if this is not a const view
  template <bool is_non_const = !is_const>
  Iterator begin(typename std::enable_if <(is_non_const), int>::type*v=nullptr) { return Iterator(*this, 0); }
  template <bool is_non_const = !is_const>
  Iterator end(typename std::enable_if <(is_non_const), int>::type*v = nullptr) { return Iterator(*this, GetLength() - 1); }
protected:
  //! Called from the non-virtual operator, which is only available when the template is set to non const mode
  virtual TValue& GetNonConst(size_t index) = 0;
};

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

