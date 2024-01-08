#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfArithmeticSlices(std::vector<int> const &nums) const
    {
        size_t result = 0;
        std::vector<std::unordered_map<long long, size_t>> dp(nums.size());
        for (size_t secondIndex = 1; secondIndex < nums.size(); ++secondIndex)
        {
            const long long second = nums[secondIndex];
            for (size_t firstIndex = 0; firstIndex < secondIndex; ++firstIndex)
            {
                const long long first = nums[firstIndex];
                const long long delta = second - first;
                if ((delta > INT_MAX) || (delta < INT_MIN))
                    continue;
                dp[secondIndex][delta] += 1;
                if (dp[firstIndex].contains(delta))
                {
                    dp[secondIndex][delta] += dp[firstIndex][delta];
                    result += dp[firstIndex][delta];
                }
            }
        }
        return static_cast<int>(result);
    }
};

}

namespace ArithmeticSlices2SubsequenceTask
{

TEST(ArithmeticSlices2SubsequenceTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.numberOfArithmeticSlices({2, 4, 6, 8, 10}));
    ASSERT_EQ(16, solution.numberOfArithmeticSlices({7, 7, 7, 7, 7}));
}

}