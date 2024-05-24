#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string dayOfTheWeek(int day, int month, int year) const
    {
        // January 1, 1971 (Friday)
        const std::vector<std::string> dayOfWeekNames({"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"});
        const std::vector<int> daysMonth({31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31});
        int totalDays = 0;
        for (int currentYear = 1971; currentYear < year; ++currentYear)
            totalDays += (isLeapYear(currentYear) ? 366 : 365);
        for (int currentMonth = 1; currentMonth < month; ++currentMonth)
            totalDays += daysMonth[currentMonth - 1] + (((currentMonth == 2) && isLeapYear(year)) ? 1 : 0);
        totalDays += (day - 1);
        const int dayOfWeek = (5 + (totalDays % 7)) % 7;
        return dayOfWeekNames[dayOfWeek];
    }

private:
    [[nodiscard]] bool isLeapYear(int year) const
    {
        if ((year % 400) == 0)
            return true;
        if ((year % 100) == 0)
            return false;
        return (year % 4) == 0;
    }
};

}

namespace DayOfWeekTask
{

TEST(DayOfWeekTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("Saturday", solution.dayOfTheWeek(31, 8, 2019));
    ASSERT_EQ("Sunday", solution.dayOfTheWeek(18, 7, 1999));
    ASSERT_EQ("Sunday", solution.dayOfTheWeek(15, 8, 1993));
}

}