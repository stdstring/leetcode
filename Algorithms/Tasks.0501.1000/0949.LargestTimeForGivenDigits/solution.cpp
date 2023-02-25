#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string largestTimeFromDigits(std::vector<int> const &arr) const
    {
        std::string bestTime;
        bestTime = std::max(bestTime, getBestTime(arr[0], arr[1], arr[2], arr[3]));
        bestTime = std::max(bestTime, getBestTime(arr[0], arr[2], arr[1], arr[3]));
        bestTime = std::max(bestTime, getBestTime(arr[0], arr[3], arr[1], arr[2]));
        bestTime = std::max(bestTime, getBestTime(arr[1], arr[2], arr[0], arr[3]));
        bestTime = std::max(bestTime, getBestTime(arr[1], arr[3], arr[0], arr[2]));
        bestTime = std::max(bestTime, getBestTime(arr[2], arr[3], arr[0], arr[1]));
        return bestTime;
    }

private:
    std::string getBestTime(int hourDigit1, int hourDigit2, int minuteDigit1, int minuteDigit2) const
    {
        const int hour1 = 10 * hourDigit1 + hourDigit2;
        const int hour2 = 10 * hourDigit2 + hourDigit1;
        const int minute1 = 10 * minuteDigit1 + minuteDigit2;
        const int minute2 = 10 * minuteDigit2 + minuteDigit1;
        std::string bestTime;
        if (hour1 < 24 && minute1 < 60)
            bestTime = std::max(bestTime, std::to_string(hourDigit1) + std::to_string(hourDigit2) + ":" + std::to_string(minuteDigit1) + std::to_string(minuteDigit2));
        if (hour1 < 24 && minute2 < 60)
            bestTime = std::max(bestTime, std::to_string(hourDigit1) + std::to_string(hourDigit2) + ":" + std::to_string(minuteDigit2) + std::to_string(minuteDigit1));
        if (hour2 < 24 && minute1 < 60)
            bestTime = std::max(bestTime, std::to_string(hourDigit2) + std::to_string(hourDigit1) + ":" + std::to_string(minuteDigit1) + std::to_string(minuteDigit2));
        if (hour2 < 24 && minute2 < 60)
            bestTime = std::max(bestTime, std::to_string(hourDigit2) + std::to_string(hourDigit1) + ":" + std::to_string(minuteDigit2) + std::to_string(minuteDigit1));
        return bestTime;
    }
};

}

namespace LargestTimeForGivenDigitsTask
{

TEST(LargestTimeForGivenDigitsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("23:41", solution.largestTimeFromDigits({1, 2, 3, 4}));
    ASSERT_EQ("", solution.largestTimeFromDigits({5, 5, 5, 5}));
    ASSERT_EQ("00:00", solution.largestTimeFromDigits({0, 0, 0, 0}));
    ASSERT_EQ("10:00", solution.largestTimeFromDigits({0, 0, 1, 0}));
}

}