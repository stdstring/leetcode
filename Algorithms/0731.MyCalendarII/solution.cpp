#include <set>

#include "gtest/gtest.h"

namespace
{

class MyCalendarTwo
{
public:
    MyCalendarTwo() = default;

    bool book(int start, int end)
    {
        constexpr size_t maxAllowedBooking = 2;
        size_t currentBooking = 0;
        for (auto startIterator = _starts.cbegin(), endIterator = _ends.cbegin(); (startIterator != _starts.cend()) && (*startIterator < end);)
        {
            if (*startIterator < *endIterator)
            {
                ++currentBooking;
                if (isIntersected(start, end, *startIterator, *endIterator) && (currentBooking == maxAllowedBooking))
                    return false;
                ++startIterator;
            }
            else
            {
                --currentBooking;
                ++endIterator;
            }
        }
        _starts.insert(start);
        _ends.insert(end);
        return true;
    }

private:
    std::multiset<int> _starts;
    std::multiset<int> _ends;

    [[nodiscard]] bool isIntersected(int start1, int end1, int start2, int end2) const
    {
        return !((end1 <= start2) || (end2 <= start1));
    }
};

}

namespace MyCalendarIITask
{

TEST(MyCalendarIITaskTests, Examples)
{
    MyCalendarTwo calendar;
    ASSERT_EQ(true, calendar.book(10, 20));
    ASSERT_EQ(true, calendar.book(50, 60));
    ASSERT_EQ(true, calendar.book(10, 40));
    ASSERT_EQ(false, calendar.book(5, 15));
    ASSERT_EQ(true, calendar.book(5, 10));
    ASSERT_EQ(true, calendar.book(25, 55));
}

}