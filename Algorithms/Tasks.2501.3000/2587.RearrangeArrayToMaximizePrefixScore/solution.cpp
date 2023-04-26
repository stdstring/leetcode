#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxScore(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end(), std::greater<int>());
        long long prefixSum = 0;
        for (size_t index = 0; index < numbers.size(); ++index)
        {
            prefixSum += numbers[index];
            if (prefixSum <= 0)
                return static_cast<int>(index);
        }
        return static_cast<int>(nums.size());
    }
};

}

namespace RearrangeArrayToMaximizePrefixScoreTask
{

TEST(RearrangeArrayToMaximizePrefixScoreTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.maxScore({2, -1, 0, 1, -3, 3, -3}));
    ASSERT_EQ(0, solution.maxScore({-2, -3, 0}));
}

}