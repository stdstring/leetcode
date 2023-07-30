#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int strangePrinter(std::string const &s) const
    {
        std::vector<std::vector<int>> dp(s.size(), std::vector<int>(s.size(), -1));
        return calcMinTurnsImpl(s, 0, s.size() - 1, dp);
    }

private:
    [[nodiscard]] int calcMinTurnsImpl(std::string const &s, size_t i, size_t j, std::vector<std::vector<int>> &dp) const
    {
        if (dp[i][j] != -1)
            return dp[i][j];
        // initial case: when i=j, it only takes 1 operation to print it.
        if (i == j)
            dp[i][j] = 1;
        // if s[i]==s[j] or s[j]==s[j-1], then it's equivalent to printing substring s[i...j-1].
        else if ((s[i] == s[j]) || (s[j - 1] == s[j]))
            dp[i][j] = calcMinTurnsImpl(s, i, j - 1, dp);
        // if s[i]==s[i+1], it's equivalent to printing substring s[i+1...j].
        else if (s[i] == s[i + 1])
            dp[i][j] = calcMinTurnsImpl(s, i + 1, j, dp);
        // If the above two conditions are not met, it means that s[i] and s[j] are different,
        // and s[j] is also different from the character before it.
        // In this case, we have multiple options:
        else
        {
            // print s[i...j-1] and then the character at position j, so the number of operations is f(i,j-1,s) + 1.
            int turnsCount = calcMinTurnsImpl(s, i, j - 1, dp) + 1;
            // we can try to find a character k between i and j (exclusive) such that s[k] is the same as s[j].
            // if we find such a character, it means we can print s[i...k-1] and s[k...j-1] together as one operation,
            // since both sequences will end with the same character s[j].
            // the number of operations would be f(i,k-1,s) + f(k,j-1,s).
            // we try all possible k values and choose the minimum among them.
            for (size_t k = i + 1; k < j; ++k)
            {
                if (s[k] == s[j])
                    turnsCount = std::min(turnsCount, calcMinTurnsImpl(s, i, k - 1, dp) + calcMinTurnsImpl(s, k, j - 1, dp));
            }
            dp[i][j] = turnsCount;
        }
        return dp[i][j];
    }
};

}

namespace StrangePrinterTask
{

TEST(StrangePrinterTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.strangePrinter("aaabbb"));
    ASSERT_EQ(2, solution.strangePrinter("aba"));
}

TEST(StrangePrinterTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.strangePrinter("tbgtgb"));
}

}