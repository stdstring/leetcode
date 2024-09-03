#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int getLucky(std::string const &s, int k) const
    {
        int digitSum = 0;
        for (const char ch : s)
        {
            int letter = ch - 'a' + 1;
            digitSum += (letter / 10) + (letter % 10);
        }
        for (int transform = 2; (transform <= k) && (digitSum > 9); ++transform)
        {
            // s.length <= 100, max(letter digit sum) = 1 + 9 = 10, 10 * 100 = 1000 => digits sum <= 1000
            digitSum = (digitSum / 1000) + ((digitSum / 100) % 10) + ((digitSum / 10) % 10) + (digitSum % 10);
        }
        return digitSum;
    }
};

}

namespace SumDigitsOfStringAfterConvertTask
{

TEST(SumDigitsOfStringAfterConvertTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(36, solution.getLucky("iiii", 1));
    ASSERT_EQ(6, solution.getLucky("leetcode", 2));
    ASSERT_EQ(8, solution.getLucky("zbax", 2));
}

TEST(SumDigitsOfStringAfterConvertTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.getLucky("ssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssss", 2));
}

}