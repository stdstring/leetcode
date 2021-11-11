#include <cstdlib>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minStartValue(std::vector<int> const &nums) const
    {
        int startValue = 1;
        int currentSum = startValue;
        for (const int number : nums)
        {
            currentSum += number;
            if (currentSum < 1)
            {
                startValue += (std::abs(currentSum) + 1);
                currentSum = 1;
            }
        }
        return startValue;
    }
};

}

namespace MinValueToGetPositiveStepByStepSumTask
{

TEST(MinValueToGetPositiveStepByStepSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.minStartValue({-3, 2, -3, 4, 2}));
    ASSERT_EQ(1, solution.minStartValue({1, 2}));
    ASSERT_EQ(5, solution.minStartValue({1, -2, -3}));
}

}