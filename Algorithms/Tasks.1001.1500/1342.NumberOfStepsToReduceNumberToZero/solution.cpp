#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfSteps(int num) const
    {
        size_t steps = 0;
        while (num > 0)
        {
            if ((num & 1) == 1)
                --num;
            else
                num >>= 1;
            ++steps;
        }
        return static_cast<int>(steps);
    }
};

}

namespace NumberOfStepsToReduceNumberToZeroTask
{

TEST(NumberOfStepsToReduceNumberToZeroTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.numberOfSteps(14));
    ASSERT_EQ(4, solution.numberOfSteps(8));
    ASSERT_EQ(12, solution.numberOfSteps(123));
}

}
