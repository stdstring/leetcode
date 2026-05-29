#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minElement(std::vector<int> const &nums) const
    {
        int minSum = calcDigitSum(nums[0]);
        for (size_t index = 1; index < nums.size(); ++index)
            minSum = std::min(minSum, calcDigitSum(nums[index]));
        return minSum;
    }

private:
    [[nodiscard]] int calcDigitSum(int number) const
    {
        int result = 0;
        for (; number > 0; number /= 10)
            result += (number % 10);
        return result;
    }
};

}

namespace MinElementAfterReplaceWithDigitSumTask
{

TEST(MinElementAfterReplaceWithDigitSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minElement({10, 12, 13, 14}));
    ASSERT_EQ(1, solution.minElement({1, 2, 3, 4}));
    ASSERT_EQ(10, solution.minElement({999, 19, 199}));
}

}