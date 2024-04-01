#include <algorithm>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestValidSubstring(std::string const &word, std::vector<std::string> const &forbidden) const
    {
        std::unordered_set<std::string> forbiddenSet;
        forbiddenSet.reserve(forbidden.size());
        size_t maxForbiddenSize = 0;
        for (std::string const &forbiddenPart : forbidden)
        {
            maxForbiddenSize = std::max(maxForbiddenSize, forbiddenPart.size());
            forbiddenSet.emplace(forbiddenPart);
        }
        size_t bestSize = 0;
        for (size_t start = 0, end = 1; end <= word.size(); ++end)
        {
            auto const &[hasForbiddenTail, size] = checkTailForbidden(word, start, end, forbiddenSet, maxForbiddenSize);
            if (hasForbiddenTail)
                start = end - size + 1;
            else
                bestSize = std::max(bestSize, end - start);
        }
        return static_cast<int>(bestSize);
    }

private:
    [[nodiscard]] std::pair<bool, size_t> checkTailForbidden(std::string const &word,
                                                             size_t start,
                                                             size_t end,
                                                             std::unordered_set<std::string> const &forbiddenSet,
                                                             size_t maxForbiddenSize) const
    {
        for (size_t size = 1; size <= std::min(end - start, maxForbiddenSize); ++size)
        {
            if (forbiddenSet.contains(word.substr(end - size, size)))
                return std::pair<bool, size_t>(true, size);
        }
        return std::pair<bool, size_t>(false, std::string::npos);
    }
};

}

namespace LengthOfLongestValidSubstringTask
{

TEST(LengthOfLongestValidSubstringTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.longestValidSubstring("cbaaaabc", {"aaa", "cb"}));
    ASSERT_EQ(4, solution.longestValidSubstring("leetcode", {"de", "le", "e"}));
}

TEST(LengthOfLongestValidSubstringTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.longestValidSubstring("bcac", {"bcac", "caca", "bcac", "bca"}));
}

}