#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minExtraChar(std::string const &s, std::vector<std::string> const &dictionary) const
    {
        std::vector<int> dp(s.size() + 1, INT_MAX);
        dp[0] = 0;
        for (size_t index = 0; index < s.size(); ++index)
        {
            for (std::string const &word : dictionary)
            {
                if (word.size() > (s.size() - index))
                    continue;
                if (s.compare(index, word.size(), word) == 0)
                    dp[index + word.size()] = std::min(dp[index + word.size()], dp[index]);
            }
            dp[index + 1] = std::min(dp[index + 1], dp[index] + 1);
        }
        return dp.back();
    }
};

}

namespace ExtraCharactersInStringTask
{

TEST(ExtraCharactersInStringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minExtraChar("leetscode", {"leet", "code", "leetcode"}));
    ASSERT_EQ(3, solution.minExtraChar("sayhelloworld", {"hello", "world"}));
}

TEST(ExtraCharactersInStringTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.minExtraChar("leetleet", {"leet", "code", "leetcode"}));
}

}