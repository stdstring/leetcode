#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int missingNumber(std::vector<int> const &nums) const
    {
        const int maxN = static_cast<int>(nums.size() + 1);
        const int actualSum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        const int expectedSum = (0 + maxN - 1) * maxN / 2;
        return expectedSum - actualSum;
    }
};

}

namespace MissingNumberTask
{

TEST(MissingNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.missingNumber({3, 0, 1}));
    ASSERT_EQ(8, solution.missingNumber({9, 6, 4, 2, 3, 5, 7, 0, 1}));
}

}