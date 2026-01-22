// Copyright (C) 2026 OTOY NZ Ltd.

#ifndef _OCTANETIME_H_
#define _OCTANETIME_H_ 1

// system
#include <algorithm>
#include <limits>
#include "octanetypes.h"

// The time interval type:
namespace Octane
{


/// The type that is used to store a time.
typedef float TimeT;


/// Returns an invalid time stamp. This will compare FALSE to any other time stamp.
/// Use isInvalidTime() to check if a given time stamp is invalid.
inline const TimeT invalidTime()
{
    return std::numeric_limits<TimeT>::quiet_NaN();
}


inline bool isInvalidTime(
    Octane::TimeT time)
{
    return time != time;
}



/// The type that is used to store a time span.
struct TimeSpanT
{
    TimeT begin;
    TimeT end;

    inline static TimeSpanT make(
        TimeT begin,
        TimeT end);


    /// Returns TRUE if this time span is equal to the other time span.
    inline bool operator==(
        const TimeSpanT &other) const;

    /// Returns TRUE if this time span is not equal to the other time span.
    inline bool operator!=(
        const TimeSpanT &other) const;

    // properties

    /// Returns the length of this time interval.
    inline TimeT length() const;

    /// Returns TRUE if this interval has zero length.
    bool empty() const;

    /// Adds an offset to the start and end of the interval.
    inline void shift(
        Octane::TimeT offset);

    /// Returns TRUE if the passed time is inside the interval.
    /// @param[in] time
    ///     The time to test.
    inline bool contains(
        const TimeT time) const;
};



/// The type used to return a frame range
struct FrameRangeT
{
    int32_t first;
    int32_t last;

    inline static FrameRangeT make(
        const int32_t begin,
        const int32_t end);

    /// returns the amount of frames
    inline uint32_t count() const;
};



// composition

/// Returns the union of the two time span. Empty time spans are ignored.
inline TimeSpanT getUnion(
    const TimeSpanT &a,
    const TimeSpanT &b);

/// Returns TRUE if this time span ends before the other time span starts.
inline bool before(
    const TimeSpanT &a,
    const TimeSpanT &b);

/// Returns TRUE if there is overlap between the two time spans.
inline bool overlaps(
    const TimeSpanT &a,
    const TimeSpanT &b);


// other operations

/// Convert a time range to a frame range
/// @param[in] time
///     The time span which should be covered
/// @param[in] fps
///     The frame rate to be rendered. Frame 0 is always considered to be at time 0.
/// @return
///     The first and last frame to be rendered. Both bounds are inclusive, so the number
///     of frames is (range.y - range.x + 1).
inline FrameRangeT timeRangeToFrameRange(
    const TimeSpanT &time,
    const float     fps);

/// Clamp a time to an interval.
/// @param[in] time
///     The time to clamp.
/// @param[in] timeSpan
///     The time span the time will be clamped to.
inline TimeT clampTime(
    const TimeT       time,
    const TimeSpanT & timeSpan);


// == implementations ==

inline TimeSpanT TimeSpanT::make(
    TimeT begin,
    TimeT end)
{
    TimeSpanT ts = { begin, end };
    return ts;
}


inline bool TimeSpanT::operator==(
    const TimeSpanT &other) const
{
    return begin == other.begin && end == other.end;
}


inline bool TimeSpanT::operator!=(
    const TimeSpanT &other) const
{
    return begin != other.begin || end != other.end;
}


inline TimeT TimeSpanT::length() const
{
    return end - begin;
}


inline bool TimeSpanT::empty() const
{
    return end <= begin;
}


inline void TimeSpanT::shift(
    Octane::TimeT offset)
{
    begin += offset;
    end += offset;
}


inline bool TimeSpanT::contains(
    const TimeT time) const
{
    return time >= begin && time <= end;
}


inline TimeSpanT getUnion(
    const TimeSpanT &a,
    const TimeSpanT &b)
{
    if (a.empty()) { return b; }
    if (b.empty()) { return a; }

    TimeSpanT ts = {
        std::min(a.begin, b.begin),
        std::max(a.end, b.end)};
    return ts;
}


inline bool before(
    const TimeSpanT &a,
    const TimeSpanT &b)
{
    return a.end < b.begin;
}


inline bool overlaps(
    const TimeSpanT &a,
    const TimeSpanT &b)
{
    return !before(a, b) && !before(b, a);
}


inline FrameRangeT FrameRangeT::make(
    const int32_t first,
    const int32_t last)
{
    FrameRangeT r = { first, last };
    return r;
}

inline uint32_t FrameRangeT::count() const
{
    return last - first + 1;
}


inline FrameRangeT timeRangeToFrameRange(
    const TimeSpanT &time,
    const float     fps)
{
    // only single frame for an empty interval
    if (time.empty()) { return FrameRangeT::make(0, 0); }

    /// Use a margin to take rounding errors into account
    return FrameRangeT::make((int32_t)floor(time.begin * fps + .1f),
                             (int32_t)ceil (time.end   * fps - .1f) );
}


inline TimeT clampTime(
    const TimeT       time,
    const TimeSpanT & timeSpan)
{
    return std::min(std::max(time, timeSpan.begin), timeSpan.end);
}

} // namespace Octane


#endif  // #ifndef _OCTANETIME_H_
