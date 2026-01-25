#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumDifference(std::vector<int> const &nums, int k) const
    {
        std::vector<int> sortedNums(nums);
        std::ranges::sort(sortedNums);
        int minDiff = INT_MAX;
        for (size_t start = 0; start <= nums.size() - k; ++start)
            minDiff = std::min(sortedNums[start + k - 1] - sortedNums[start], minDiff);
        return minDiff;
    }
};

}

namespace MinDiffBetweenHighestLowestKScoresTask
{

TEST(MinDiffBetweenHighestLowestKScoresTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.minimumDifference({90}, 1));
    ASSERT_EQ(2, solution.minimumDifference({9, 4, 1, 7}, 2));
}

}