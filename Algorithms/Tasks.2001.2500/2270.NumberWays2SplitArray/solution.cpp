#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int waysToSplitArray(std::vector<int> const &nums) const
    {
        long long rightSum = std::accumulate(nums.cbegin(), nums.cend(), 0LL);
        long long leftSum = 0;
        size_t waysCount = 0;
        for (size_t index = 0; index < nums.size() - 1; ++index)
        {
            leftSum += nums[index];
            rightSum -= nums[index];
            if (leftSum >= rightSum)
                ++waysCount;
        }
        return static_cast<int>(waysCount);
    }
};

}

namespace NumberWays2SplitArrayTask
{

TEST(NumberWays2SplitArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.waysToSplitArray({10, 4, -8, 7}));
    ASSERT_EQ(2, solution.waysToSplitArray({2, 3, 1, 0}));
}

}