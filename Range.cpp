#include "Range.h"

Range::Range()
    : mBegin(0), mEnd(0) {}

Range::Range(int begin, int end)
    : mBegin(begin), mEnd(end) {}

int Range::begin() const
{
    return mBegin;
}

int Range::end() const
{
    return mEnd;
}

int Range::length() const
{
    return mEnd - mBegin;
}

int Range::isValid() const
{
    return mEnd > mBegin;
}
