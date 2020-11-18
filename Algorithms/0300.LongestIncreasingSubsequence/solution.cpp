#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int lengthOfLIS(std::vector<int> const &nums) const
    {
        std::vector<int> subsequencesLength(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
        {
            int currentLength = 1;
            for (size_t prevIndex = 0; prevIndex < index; ++prevIndex)
            {
                if (nums[prevIndex] < nums[index])
                    currentLength = std::max(currentLength, subsequencesLength[prevIndex] + 1);
            }
            subsequencesLength[index] = currentLength;
        }
        return *std::max_element(subsequencesLength.cbegin(), subsequencesLength.cend());
    }
};

}

namespace LongestIncreasingSubsequenceTask
{

TEST(LongestIncreasingSubsequenceTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.lengthOfLIS({10, 9, 2, 5, 3, 7, 101, 18}));
    ASSERT_EQ(4, solution.lengthOfLIS({0, 1, 0, 3, 2, 3}));
    ASSERT_EQ(1, solution.lengthOfLIS({7, 7, 7, 7, 7, 7, 7}));
}

}