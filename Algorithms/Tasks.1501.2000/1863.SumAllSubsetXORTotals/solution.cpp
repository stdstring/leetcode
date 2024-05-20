#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int subsetXORSum(std::vector<int> const &nums) const
    {
        const int subsetMaskMax = 1 << nums.size();
        int result = 0;
        for (int subsetMask = 1; subsetMask < subsetMaskMax; ++subsetMask)
            result += subsetXORSum(nums, subsetMask);
        return result;
    }

private:
    [[nodiscard]] int subsetXORSum(std::vector<int> const &nums, int subsetMask) const
    {
        int result = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            const int mask = 1 << index;
            if ((subsetMask & mask) != 0)
                result ^= nums[index];
        }
        return result;
    }
};

}

namespace SumAllSubsetXORTotalsTask
{

TEST(SumAllSubsetXORTotalsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.subsetXORSum({1, 3}));
    ASSERT_EQ(28, solution.subsetXORSum({5, 1, 6}));
    ASSERT_EQ(480, solution.subsetXORSum({3, 4, 5, 6, 7, 8}));
}

}