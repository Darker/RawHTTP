#pragma once
#include "util/NoCopy.h"

namespace RawHttp
{

class EventData : public NoCopy
{
public:
  EventData() = delete;
  EventData(EventData&& other) { _data = other._data; other._data = nullptr; }
  size_t Size() const {}
  void* Data() { return _data; }
  const void* Data() const { return _data; }

  EventData& operator=(EventData&& other) { _data = other._data; other._data = nullptr; }
protected:
  EventData(void* data, bool owner = false) : _data(data), _ownedPointer(owner) {}
  void* _data = nullptr;
  //! If true, this class owns the data and may delete or move them
  bool _ownedPointer;
};

template <typename TData>
class EventDataTyped : public EventData
{
public:
  EventDataTyped(const TData& data) : EventData(&_dataTyped), _dataTyped(_dataTyped) {}
  EventDataTyped(TData&& data) : EventData(&_dataTyped), _dataTyped(_dataTyped) {}

  const TData& DataTyped() const { return *((TData*)_data); }
  TData& DataTyped() { return *((TData*)_data); }
protected:
  TData _dataTyped;
};

}
