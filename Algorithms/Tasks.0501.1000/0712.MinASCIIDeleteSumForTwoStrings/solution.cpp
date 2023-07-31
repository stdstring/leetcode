#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumDeleteSum(std::string const &s1, std::string const &s2) const
    {
        // Longest Common Subsequence (LCS) problem
        const int s1Value = std::accumulate(s1.cbegin(), s1.cend(), 0);
        const int s2Value = std::accumulate(s2.cbegin(), s2.cend(), 0);
        std::vector<int> dpCurrent(s2.size() + 1, 0);
        std::vector<int> dpNext;
        dpNext.reserve(s2.size() + 1);
        for (const char ch1 : s1)
        {
            dpNext.clear();
            dpNext.emplace_back(0);
            for (size_t column = 0; column < s2.size(); ++column)
            {
                if (ch1 == s2[column])
                    dpNext.emplace_back(dpCurrent[column] + ch1);
                else
                    dpNext.emplace_back(std::max(dpNext.back(), dpCurrent[column + 1]));
            }
            std::swap(dpCurrent, dpNext);
        }
        return s1Value +s2Value - 2 * dpCurrent.back();
    }
};

}

namespace MinASCIIDeleteSumForTwoStringsTask
{

TEST(MinASCIIDeleteSumForTwoStringsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(231, solution.minimumDeleteSum("sea", "eat"));
    ASSERT_EQ(403, solution.minimumDeleteSum("delete", "leet"));
}

}