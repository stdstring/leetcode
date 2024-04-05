#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::string> getWordsInLongestSubsequence(std::vector<std::string> const &words, std::vector<int> const &groups) const
    {
        // size, prev index
        std::vector<std::pair<size_t, size_t>> dp;
        dp.reserve(words.size());
        size_t maxSize = 0;
        size_t maxSizeIndex = std::string::npos;
        for (size_t index = 0; index < words.size(); ++index)
        {
            dp.emplace_back(1, std::string::npos);
            for (size_t prev = 0; prev < index; ++prev)
            {
                if (words[index].size() != words[prev].size())
                    continue;
                if (groups[index] == groups[prev])
                    continue;
                if (calcHammingDistance(words[index], words[prev]) != 1)
                    continue;
                if (dp[index].first < (dp[prev].first + 1))
                    dp[index] = std::pair<int, int>(dp[prev].first + 1, prev);
            }
            if (dp[index].first > maxSize)
            {
                maxSize = dp[index].first;
                maxSizeIndex = index;
            }
        }
        std::vector<std::string> result;
        result.reserve(dp.back().first);
        for (size_t current = maxSizeIndex; current != std::string::npos; current = dp[current].second)
            result.emplace_back(words[current]);
        std::ranges::reverse(result);
        return result;
    }

private:
    [[nodiscard]] int calcHammingDistance(std::string const &s1, std::string const &s2) const
    {
        int hammingDistance = 0;
        for (size_t index = 0; index < s1.size(); ++index)
            hammingDistance += (s1[index] == s2[index] ? 0 : 1);
        return hammingDistance;
    }
};

}

namespace LongestUnequalAdjacentGroupsSubseq2Task
{

TEST(LongestUnequalAdjacentGroupsSubseq2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"bab", "dab"}), solution.getWordsInLongestSubsequence({"bab", "dab", "cab"}, {1, 2, 2}));
    ASSERT_EQ(std::vector<std::string>({"a", "b", "c", "d"}), solution.getWordsInLongestSubsequence({"a", "b", "c", "d"}, {1, 2, 3, 4}));
}

TEST(LongestUnequalAdjacentGroupsSubseq2TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::string>({"caa", "cda"}), solution.getWordsInLongestSubsequence({"ac", "caa", "cda", "ba"}, {3, 1, 2, 3}));
}

}