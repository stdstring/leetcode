#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int equalSubstring(std::string const &s, std::string const &t, int maxCost) const
    {
        std::vector<int> prefixCost(s.size(), 0);
        for (size_t index = 0; index < s.size(); ++index)
            prefixCost[index] = std::abs(s[index] - t[index]) + (index > 0 ? prefixCost[index - 1] : 0);
        size_t currentLength = 0;
        // init
        while ((currentLength < prefixCost.size()) && (prefixCost[currentLength] <= maxCost))
            ++currentLength;
        size_t bestLength = currentLength;
        // move
        for (size_t index = 1; index < prefixCost.size(); ++index)
        {
            if (currentLength > 0)
                --currentLength;
            while ((index + currentLength) < prefixCost.size() && ((prefixCost[index + currentLength] - prefixCost[index - 1]) <= maxCost))
                ++currentLength;
            bestLength = std::max(bestLength, currentLength);
        }
        return static_cast<int>(bestLength);
    }
};

}

namespace GetEqualSubstringsWithinBudgetTask
{

TEST(GetEqualSubstringsWithinBudgetTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.equalSubstring("abcd", "bcdf", 3));
    ASSERT_EQ(1, solution.equalSubstring("abcd", "cdef", 3));
    ASSERT_EQ(1, solution.equalSubstring("abcd", "acde", 0));
}

}