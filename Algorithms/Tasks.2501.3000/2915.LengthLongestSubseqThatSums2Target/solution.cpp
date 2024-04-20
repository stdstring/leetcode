#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int lengthOfLongestSubsequence(std::vector<int> const &nums, int target) const
    {
        std::vector<int> currentRow(target + 1, 0);
        std::vector<int> nextRow(target + 1, 0);
        for (const int number : nums)
        {
            if (number <= target)
                nextRow[number] = std::max(nextRow[number], 1);
            for (int sum = 1; sum <= target; ++sum)
            {
                if (currentRow[sum] == 0)
                    continue;
                nextRow[sum] = std::max(nextRow[sum], currentRow[sum]);
                if ((number + sum) <= target)
                    nextRow[number + sum] = std::max(nextRow[number + sum], currentRow[sum] + 1);
            }
            std::swap(currentRow, nextRow);
            std::ranges::fill(nextRow, 0);
        }
        return currentRow.back() == 0 ? -1 : currentRow.back();
    }
};

}

namespace LengthLongestSubseqThatSums2TargetTask
{

TEST(LengthLongestSubseqThatSums2TargetTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.lengthOfLongestSubsequence({1, 2, 3, 4, 5}, 9));
    ASSERT_EQ(4, solution.lengthOfLongestSubsequence({4, 1, 3, 2, 1, 5}, 7));
    ASSERT_EQ(-1, solution.lengthOfLongestSubsequence({1, 1, 5, 4, 5}, 3));
}

}