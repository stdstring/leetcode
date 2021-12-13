#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxPower(std::string const &s) const
    {
        size_t maxPowerValue = 0;
        size_t groupStart = 0;
        for (size_t index =0; index < s.size(); ++index)
        {
            if (s[index] != s[groupStart])
            {
                maxPowerValue = std::max(maxPowerValue, index - groupStart);
                groupStart = index;
            }
        }
        maxPowerValue = std::max(maxPowerValue, s.size() - groupStart);
        return static_cast<int>(maxPowerValue);
    }
};

}

namespace ConsecutiveCharactersTask
{

TEST(ConsecutiveCharactersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.maxPower("leetcode"));
    ASSERT_EQ(5, solution.maxPower("abbcccddddeeeeedcba"));
    ASSERT_EQ(5, solution.maxPower("triplepillooooow"));
    ASSERT_EQ(11, solution.maxPower("hooraaaaaaaaaaay"));
    ASSERT_EQ(1, solution.maxPower("tourist"));
}

}