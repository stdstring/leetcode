#include <set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxSum(std::vector<int> const &nums) const
    {
        std::set<int> numberSet(nums.cbegin(), nums.cend());
        if (*numberSet.rbegin() <= 0)
            return *numberSet.rbegin();
        int result = 0;
        for (auto iterator = numberSet.rbegin(); iterator != numberSet.rend(); ++iterator)
        {
            if (*iterator <= 0)
                break;
            result += *iterator;
        }
        return result;
    }
};

}

namespace MaxUniqueSubarraySumAfterDeletionTask
{

TEST(MaxUniqueSubarraySumAfterDeletionTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.maxSum({1, 2, 3, 4, 5}));
    ASSERT_EQ(1, solution.maxSum({1, 1, 0, 1, 1}));
    ASSERT_EQ(3, solution.maxSum({1, 2, -1, -2, 1, 0, -1}));
}

}