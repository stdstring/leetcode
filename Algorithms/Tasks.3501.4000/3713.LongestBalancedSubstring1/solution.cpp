#include <algorithm>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestBalanced(std::string const &s) const
    {
        std::vector<std::vector<size_t>> dp(s.size() + 1);
        dp[0] = std::vector<size_t>(alphabetSize, 0);
        for (size_t index = 0; index < s.size(); ++index)
        {
            const char current = s[index];
            dp[index + 1] = dp[index];
            ++dp[index + 1][current - alphabetStart];
        }
        size_t longestSize = 0;
        for (size_t from = 0; from < s.size(); ++from)
        {
            for (size_t to = from + 1; to < s.size() + 1; ++to)
            {
                if (isBalanced(dp, from, to))
                    longestSize = std::max(longestSize, to - from);
            }
        }
        return static_cast<int>(longestSize);
    }

private:
    static constexpr size_t alphabetStart = 'a';
    static constexpr size_t alphabetSize = 26;

    [[nodiscard]] bool isBalanced(std::vector<std::vector<size_t>> const &dp, size_t from, size_t to) const
    {
        size_t expectedDelta = 0;
        for (size_t index = 0; index < alphabetSize; ++index)
        {
            size_t currentDelta = dp[to][index] - dp[from][index];
            if (currentDelta == 0)
                continue;
            if ((expectedDelta == 0) || (expectedDelta == currentDelta))
                expectedDelta = currentDelta;
            else
                return false;
        }
        return true;
    }
};

}

namespace LongestBalancedSubstring1Task
{

TEST(LongestBalancedSubstring1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.longestBalanced("abbac"));
    ASSERT_EQ(4, solution.longestBalanced("zzabccy"));
    ASSERT_EQ(2, solution.longestBalanced("aba"));
}

}