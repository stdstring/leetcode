#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isGood(std::vector<int> const &nums) const
    {
        const int n = static_cast<int>(nums.size() - 1);
        const int maxValue = std::ranges::max(nums);
        if (n != maxValue)
            return false;
        std::vector<int> counter(n + 1, 0);
        for (const int number : nums)
        {
            const int maxCount = (number == n ? 2 : 1);
            if (counter[number] == maxCount)
                return false;
            ++counter[number];
        }
        return true;
    }
};

}

namespace CheckIfArrayGoodTask
{

TEST(CheckIfArrayGoodTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.isGood({2, 1, 3}));
    ASSERT_EQ(true, solution.isGood({1, 3, 3, 2}));
    ASSERT_EQ(true, solution.isGood({1, 1}));
    ASSERT_EQ(false, solution.isGood({3, 4, 4, 1, 2, 1}));
}

}