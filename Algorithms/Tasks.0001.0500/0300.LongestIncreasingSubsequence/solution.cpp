#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int lengthOfLIS(std::vector<int> const &nums) const
    {
        // from https://en.wikipedia.org/wiki/Longest_increasing_subsequence
        std::vector<size_t> m(nums.size() + 1, 0);
        size_t length = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            size_t left = 1;
            size_t right = length + 1;
            while (left < right)
            {
                const size_t middle = (left + right) / 2;
                if (nums[m[middle]] < nums[index])
                    left = middle + 1;
                else
                    right = middle;
            }
            m[left] = index;
            length = std::max(left, length);
        }
        return static_cast<int>(length);
    }
};

}

namespace LongestIncreasingSubsequenceTask
{

TEST(LongestIncreasingSubsequenceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.lengthOfLIS({10, 9, 2, 5, 3, 7, 101, 18}));
    ASSERT_EQ(4, solution.lengthOfLIS({0, 1, 0, 3, 2, 3}));
    ASSERT_EQ(1, solution.lengthOfLIS({7, 7, 7, 7, 7, 7, 7}));
}

}