#pragma once
#include <cmath>
#include <limits>

namespace RawHttp 
{
class TimeInterval
{
public:
  using TimeNumType = unsigned long long;

  explicit constexpr TimeInterval(TimeNumType us) : _microSeconds(us) {}

  

  static constexpr TimeInterval FromMicroSeconds(TimeNumType us) { return TimeInterval{ us }; }
  static constexpr TimeInterval FromMilliSeconds(TimeNumType ms) { return TimeInterval{ ms*DurationMilliSecond }; }
  static constexpr TimeInterval FromSeconds(TimeNumType s) { return TimeInterval{ s*DurationSecond }; }

  constexpr double ToMilliSeconds() const { return _microSeconds / 1000.0; }
  constexpr double ToSeconds() const { return _microSeconds / 1000000.0; }
private:
  TimeNumType _microSeconds;

  static constexpr TimeNumType DurationMilliSecond = 1000;
  static constexpr TimeNumType DurationSecond = DurationMilliSecond * 1000;
  static constexpr TimeNumType DurationMinute = DurationSecond * 60;
  static constexpr TimeNumType DurationHour = DurationMinute * 60;
  static constexpr TimeNumType DurationDay = DurationHour * 24;
  static constexpr TimeNumType DurationWeek = DurationDay * 7;

};

namespace TimeConstants
{
constexpr const TimeInterval Zero = TimeInterval{ 0 };
constexpr const TimeInterval Infinity = TimeInterval{ std::numeric_limits<TimeInterval::TimeNumType>::max() };
}


namespace Units
{

constexpr TimeInterval operator"" _us(TimeInterval::TimeNumType microSeconds) { return TimeInterval::FromMicroSeconds(microSeconds); }
constexpr TimeInterval operator"" _ms(TimeInterval::TimeNumType milliSeconds) { return TimeInterval::FromMilliSeconds(milliSeconds); }
constexpr TimeInterval operator"" _s(TimeInterval::TimeNumType seconds) { return TimeInterval::FromSeconds(seconds); }

}
}
