#include <set>

#include "gtest/gtest.h"

namespace
{

class MyCalendarThree
{
public:
    MyCalendarThree() = default;

    int book(int start, int end)
    {
        _starts.insert(start);
        _ends.insert(end);
        size_t bestBooking = 0;
        size_t currentBooking = 0;
        for (auto startIterator = _starts.cbegin(), endIterator = _ends.cbegin(); startIterator != _starts.cend();)
        {
            if (*startIterator < *endIterator)
            {
                ++currentBooking;
                bestBooking = std::max(bestBooking, currentBooking);
                ++startIterator;
            }
            else
            {
                --currentBooking;
                ++endIterator;
            }
        }
        return static_cast<int>(bestBooking);
    }

private:
    std::multiset<int> _starts;
    std::multiset<int> _ends;
};

}

namespace MyCalendarIIITask
{

TEST(MyCalendarIIITaskTests, Examples)
{
    MyCalendarThree calendar;
    ASSERT_EQ(1, calendar.book(10, 20));
    ASSERT_EQ(1, calendar.book(50, 60));
    ASSERT_EQ(2, calendar.book(10, 40));
    ASSERT_EQ(3, calendar.book(5, 15));
    ASSERT_EQ(3, calendar.book(5, 10));
    ASSERT_EQ(3, calendar.book(25, 55));
}

}