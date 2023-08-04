#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool wordBreak(std::string const &s, std::vector<std::string> const &wordDict) const
    {
        std::vector<bool> dp(s.size(), false);
        dp[0] = true;
        for (size_t index = 0; index < dp.size(); ++index)
        {
            if (!dp[index])
                continue;
            const size_t restSize = s.size() - index;
            for (std::string const &word : wordDict)
            {
                if (word.size() > restSize)
                    continue;
                if (s.compare(index, word.size(), word) != 0)
                    continue;
                if (word.size() == restSize)
                    return true;
                dp[index + word.size()] = true;
            }
        }
        return false;
    }
};

}

namespace WordBreakTask
{

TEST(WordBreakTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.wordBreak("leetcode", {"leet", "code"}));
    ASSERT_EQ(true, solution.wordBreak("applepenapple", {"apple", "pen"}));
    ASSERT_EQ(false, solution.wordBreak("catsandog", {"cats", "dog", "sand", "and", "cat"}));
}

}