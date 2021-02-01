#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int dayOfYear(std::string const &date) const
    {
        const int year = getNumber(date, 0, 4);
        const int month = getNumber(date, 5, 2);
        const int day = getNumber(date, 8, 2);
        return calcDayNumber(isLeapYear(year), month, day);
    }

private:
    static constexpr int MonthCount = 12;
    static constexpr int UsualYearDays[MonthCount] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    int getNumber(std::string const &date, size_t start, size_t size) const
    {
        int number = 0;
        for (size_t index = 0; index < size; ++index)
            number =  10 * number + (date[start + index] - '0');
        return number;
    }

    bool isLeapYear(int year) const
    {
        return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
    }

    int calcDayNumber(bool isLeapYear, int month, int day) const
    {
        int number = 0;
        for (size_t monthNumber = 1; monthNumber < static_cast<size_t>(month); ++monthNumber)
            number += UsualYearDays[monthNumber - 1] + (isLeapYear && monthNumber == 2 ? 1 : 0);
        return number + day;
    }
};

}

namespace DayOfYearTask
{

TEST(DayOfYearTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(9, solution.dayOfYear("2019-01-09"));
    ASSERT_EQ(41, solution.dayOfYear("2019-02-10"));
    ASSERT_EQ(60, solution.dayOfYear("2003-03-01"));
    ASSERT_EQ(61, solution.dayOfYear("2004-03-01"));
}

}