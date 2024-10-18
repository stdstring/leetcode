#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countMaxOrSubsets(std::vector<int> const &nums) const
    {
        const int totalOr = std::accumulate(nums.cbegin(), nums.cend(), 0, [](int acc, int value){ return acc | value; });
        const int maxMask = (1 << nums.size()) - 1;
        size_t totalOrCount = 0;
        for (int mask = 1; mask <= maxMask; ++mask)
        {
            if (calcSubsetOr(nums, mask) == totalOr)
                ++totalOrCount;
        }
        return static_cast<int>(totalOrCount);
    }

private:
    [[nodiscard]] int calcSubsetOr(std::vector<int> const &nums, int subsetMask) const
    {
        int result = 0;
        size_t index = 0;
        for (; subsetMask != 0; subsetMask >>= 1)
        {
            if ((subsetMask & 1) == 1)
                result |= nums[index];
            ++index;
        }
        return result;
    }
};

}

namespace CountNumberMaxBitwiseOrSubsetsTask
{

TEST(CountNumberMaxBitwiseOrSubsetsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.countMaxOrSubsets({3, 1}));
    ASSERT_EQ(7, solution.countMaxOrSubsets({2, 2, 2}));
    ASSERT_EQ(6, solution.countMaxOrSubsets({3, 2, 1, 5}));
}

}