#pragma once
#include "../abstract/containers/IndexedCollection.h"
#include "../abstract/units/Time.h"
#include "../datatypes/Exceptions.h"

namespace RawHttp 
{

class IWaitObject
{
public:
  /*!
   * Describes result status of a wait operation
   **/
  enum class WaitResultStatus
  {
    Success,
    Error,
    Timeout
  };
  /**
   * 
   */
  class WaitException : public GenericError
  {
    using GenericError::GenericError;
  };
 
  /*!
   * Describes result of a wait operation
   **/
  struct WaitResult
  {
    //! status of the request, following members are only valid if the status is success
    WaitResultStatus status;
    //! Pointer to the first completed event
    IWaitObject* completedEvent;
    //! index of the first completed event
    size_t completedIndex;
  };

  virtual ~IWaitObject() = 0;

  //! Wait for all given objects. These objects MUST be of the same type as this object. This object may or may not be in the wait list
  virtual WaitResult WaitFor(const ArrayView<IWaitObject*, false>& objects, bool all, TimeInterval timeout, bool noExceptions = false) = 0;
  //! Provides string object type. Object types with the same type are compatible and can wait within the same thread
  virtual const char* GetType() const = 0;

};

IWaitObject::~IWaitObject() { }

}
