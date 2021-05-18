#pragma once

namespace RawHttp
{


/*!
 *  Template for generic traits of objects that can be iterated over.
 *  
 *
 *      @tparam TValue type of the value that is being iterated over
 *      @tparam TIterable type of the iterable collection/object
 */
template <typename TValue, class TIterable>
struct IterableTraits
{
  //! By default, iterator is size_t
  using Iterator = size_t;

  //! Creates iterator for given collection
  static Iterator CreateIterator(const TIterable& collection) { static_assert(false, "Implementation is missing for this type"); }
  //! Provides const ref to item described by current iterator within given collection
  static const TValue& GetCurrentConst(const TIterable& collection, const Iterator& iterator) { static_assert(false, "Implementation is missing for this type"); }
  //! Returns modifiable refference to item described by given iterator and collection
  static TValue& GetCurrent(TIterable& collection, const Iterator& iterator) { static_assert(false, "Implementation is missing for this type"); }
  //! Returns true if the iterator no longer points at valid data in collection
  static bool IsEnd(const TIterable& collection, const Iterator& iterator) { static_assert(false, "Implementation is missing for this type"); }
  //! Advances the iterator one step further
  static void AdvanceIterator(const TIterable& collection, Iterator& iterator) { static_assert(false, "Implementation is missing for this type"); }
};

/*!
 *  Abstract iterable construct that can be iterated over.
 * 
 * @tparam TValue Value type for iteration
 */
template <typename TValue>
class Iterable
{
public:
  virtual bool End() const = 0;
  virtual void Next() = 0;
  virtual const TValue& GetValue() const = 0;
};

/*!
 *  Implementation of iteration over various containers using iterable traits template specializations.
 *
 *      @tparam TIterable 
 *      @tparam TValue    
 */
template <class TIterable, typename TValue>
class IterableImpl : public Iterable<TValue>
{
public:
  //! Shortcut for referrint to specific traits related to the collection type
  using Traits = IterableTraits<TValue, TIterable>;

  //! Captures the REFFERENCE to given collection. The reffered objects therefore must not be deleted while this object is in use
  IterableImpl(const TIterable& src) : _iterable(src), _iterator(Traits::CreateIterator(src)) {}

  //! If returns true, call to GetValue and Next is undefined behavior
  bool End() const { return Traits::IsEnd(_iterable, _iterator); }
  //! Advances to the next item
  void Next() { Traits::AdvanceIterator(_iterable, _iterator); }
  //! Provides current item. UD if End() is true
  const TValue& GetValue() const { return Traits::GetCurrentConst(_iterable, _iterator); }

private:
  //! Container of the iterable data
  const TIterable& _iterable;
  //! Iterator over the container, defined for each supported collection type
  typename Traits::Iterator _iterator;
};

}

