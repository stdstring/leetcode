#include <cstdlib>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countPartitions(std::vector<int> const &nums) const
    {
        int leftSum = 0;
        int rightSum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        size_t result  = 0;
        for (const int number : nums)
        {
            leftSum += number;
            rightSum -= number;
            if ((rightSum > 0) && ((std::abs(leftSum - rightSum) % 2) == 0))
                ++result;
        }
        return static_cast<int>(result);
    }
};

}

namespace CountPartitionsWithEvenSumDiffTask
{

TEST(CountPartitionsWithEvenSumDiffTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.countPartitions({10, 10, 3, 7, 6}));
    ASSERT_EQ(0, solution.countPartitions({1, 2, 2}));
    ASSERT_EQ(3, solution.countPartitions({2, 4, 6, 8}));
}

}