#include <set>
#include <utility>

#include "gtest/gtest.h"

namespace
{

bool compare(std::pair<int, int> const &left, std::pair<int, int> const &right)
{
    return left.first < right.first;
}

class MyCalendar
{
public:
    MyCalendar() : _bookingSet(compare)
    {
    }

    bool book(int start, int end)
    {
        if (_bookingSet.empty())
        {
            _bookingSet.emplace(start, end);
            return true;
        }
        auto bound = _bookingSet.lower_bound(std::pair<int, int>(start, end));
        if (bound != _bookingSet.cend() && end > bound->first)
            return false;
        if (bound != _bookingSet.cbegin() && start < (--bound)->second)
            return false;
        _bookingSet.emplace(start, end);
        return true;
    }

private:
    std::set<std::pair<int, int>, decltype(compare)*> _bookingSet;
};

}

namespace MyCalendarITask
{

TEST(MyCalendarITaskTests, Examples)
{
    MyCalendar calendar;
    ASSERT_EQ(true, calendar.book(10, 20));
    ASSERT_EQ(false, calendar.book(15, 25));
    ASSERT_EQ(true, calendar.book(20, 30));
}

}