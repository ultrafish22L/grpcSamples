// Copyright (C) 2025 OTOY NZ Ltd.

#ifndef _API_TIME_SAMPLING_H_
#define _API_TIME_SAMPLING_H_   1

#include "octaneenums.h"
#include "octanetypes.h"
#include "octanetime.h"


namespace Octane
{

//--------------------------------------------------------------------------------------------------
/// ApiTimeSampling defines a time sampling pattern. The pattern is a series of time stamps for 
/// which times are given, and the period indicates after how much time the pattern will repeat.
/// 
/// - If the period is set to 0, then the time sampling is considered aperiodic and the pattern size
/// must be at least the amount of values given in the setAnim() calls.
/// 
/// - To denote sampling at a regular interval, use a pattern of size 1 containing the start time of
/// the sampling.
///
/// - If the pattern is empty (size 0) then the sampling is regular with starting time 0.
///
/// The animation will end when t = endTime. The end time includes the length of the last frame. If 
/// endTime = END_TIME_AUTO, any animators set up with this time sampling will repeat their values 
/// exactly once (or once back-and-forth for ping-pong animators).
/// 
/// Example:
///     Assume in the diagram below, that a dash is one second, and the following:
///     pattern (time values) = { 4, 7, 12, 14 }
///     data values           = { A B C D E }
///     animation type        = ANIMATION_LOOP
///     period                = 20 seconds (repeat after 20 seconds)
///
///                period            period             period
///         |----------------->|----------------->|----------------->|
///         4  7   12 14      24 27   32 34      44                 64       |
///     |   |--|----|-|--------|--|----|-|--------|--|----|-|--------|--|----|
///     |   A  B    C D        E  A    B C        D  E    A B        C  D    |
///     |                                                                    |
///     |   ^                  ^                                             | 
///     ^   t = pattern[0]     t = pattern[0]+periodIndex*mPeriod            ^
///     t = 0                                                                t = mEndTime
///
/// Data members:
///     mPattern:       Time stamp pattern for our key frames. If empty, it will implicitly be {0}.
///     mPatternSize:   The number of entries of the time stamp pattern. If 0, the pattern will
///                     implicitly be {0}.
///     mPeriod:        The period of the time pattern
///     mAnimationType: Determines whether the data is looped (as above), or ping-pong, or once.
///                     The data array is repeated until the time reaches mEndTime
///     mEndTime:       The end time of the whole animation. If set to endTimeAuto(), it will
///                     mPatter[0] + mPeriod.
///     
///  The time stamp pattern and the data value pattern are independent of each other, i.e. their
///  periods and patterns are independent.
///
/// Conditions that must be true:
///     - mPeriod must be larger than the difference of the first and last time values.
///     - the start of the animation is always mPeriod[0], and mEndTime is always larger than
///       mPeriod[0].
///     - There must be at least one data value.
/// Special cases:
///     - if mPattern provided is empty, one will be created with a single zero in it.
///       This means that there will be one time sample every mPeriod. This also means that 
///       the endTime of the animation depends on the number of data values there are. 
struct OCTANEAPI_DECL ApiTimeSampling
{
    const TimeT   *mPattern;
    size_t         mPatternSize;
    TimeT          mPeriod;
    AnimationType  mAnimationType;
    TimeT          mEndTime;

    /// Creates a regular time sampling starting at 0.
    ApiTimeSampling(
        TimeT         period   = 0,
        TimeT         endTime  = endTimeAuto(),
        AnimationType animType = ANIMATION_ONCE);

    /// Creates a time sampling referring the given data. This does not take ownership of the
    /// pattern array.
    ApiTimeSampling(
        const TimeT  *pattern,
        size_t        patternSize,
        TimeT         period,
        TimeT         endTime  = endTimeAuto(),
        AnimationType animType = ANIMATION_ONCE);

    static float endTimeAuto();
};



} // namespace Octane

#endif // #ifndef _API_TIME_SAMPLING_H_
