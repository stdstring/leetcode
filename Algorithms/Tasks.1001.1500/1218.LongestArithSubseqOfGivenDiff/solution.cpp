#include <algorithm>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int longestSubsequence(std::vector<int> const &arr, int difference) const
    {
        size_t bestSize = 0;
        std::unordered_map<int, size_t> sequenceMap;
        for (const int number : arr)
        {
            auto iterator = sequenceMap.find(number - difference);
            const size_t prevSize = iterator == sequenceMap.cend() ? 0 : iterator->second;
            sequenceMap[number] = std::max(sequenceMap[number], prevSize + 1);
            bestSize = std::max(bestSize, sequenceMap[number]);
        }
        return static_cast<int>(bestSize);
    }
};

}

namespace LongestArithSubseqOfGivenDiffTask
{

TEST(LongestArithSubseqOfGivenDiffTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.longestSubsequence({1, 2, 3, 4}, 1));
    ASSERT_EQ(1, solution.longestSubsequence({1, 3, 5, 7}, 1));
    ASSERT_EQ(4, solution.longestSubsequence({1, 5, 7, 8, 5, 3, 4, 2, 1}, -2));
}

}