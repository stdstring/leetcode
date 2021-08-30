#include <array>
#include <cstdlib>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int daysBetweenDates(std::string const &date1, std::string const &date2) const
    {
        return std::abs(calcDaysFromStart(date1) - calcDaysFromStart(date2));
    }

private:
    bool isLeapYear(int year) const
    {
        return (year % 400 == 0) || (year % 100 != 0 && year % 4 == 0);
    }

    // start == 01.01.1900
    int calcDaysFromStart(std::string const &date) const
    {
        static const std::array<int, 12> daysToMonth({0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334});
        const int year = std::stoi(date);
        const int month = std::stoi(date.substr(5, 2));
        const int day = std::stoi(date.substr(8, 2));
        constexpr int startYear = 1900;
        int daysCount = (year - startYear) * 365;
        daysCount += ((startYear % 4 == 0 ? 4 : startYear % 4) + year - startYear) / 4;
        daysCount -= ((startYear % 100 == 0 ? 100 : startYear % 100) + year - startYear) / 100;
        daysCount += ((startYear % 400 == 0 ? 400 : startYear % 400) + year - startYear) / 400;
        if (isLeapYear(year))
            --daysCount;
        daysCount += daysToMonth[static_cast<size_t>(month) - 1];
        if ((month > 2) && isLeapYear(year))
            ++daysCount;
        daysCount += day;
        return daysCount;
    }
};

}

namespace NumberOfDaysBetweenTwoDatesTask
{

TEST(NumberOfDaysBetweenTwoDatesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.daysBetweenDates("2019-06-29", "2019-06-30"));
    ASSERT_EQ(15, solution.daysBetweenDates("2020-01-15", "2019-12-31"));
}

TEST(NumberOfDaysBetweenTwoDatesTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(14331, solution.daysBetweenDates("1971-06-29", "2010-09-23"));
}

}