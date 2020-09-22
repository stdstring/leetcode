#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int singleNumber(std::vector<int> const &nums) const
    {
        int result = nums[0];
        for (size_t index = 1; index < nums.size(); ++index)
            result ^= nums[index];
        return result;
    }
};

}

namespace SingleNumberTask
{

TEST(SingleNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.singleNumber({2, 2, 1}));
    ASSERT_EQ(4, solution.singleNumber({4, 1, 2, 1, 2}));
}

}