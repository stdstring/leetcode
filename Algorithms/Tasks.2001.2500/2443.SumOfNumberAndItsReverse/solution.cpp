#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool sumOfNumberAndReverse(int num) const
    {
        for (int current = num; current >= 0; --current)
        {
            const int reversedCurrent = reverseNumber(current);
            if ((current + reversedCurrent) == num)
                return true;
        }
        return false;
    }

private:
    [[nodiscard]] int reverseNumber(int number) const
    {
        int result = 0;
        while (number > 0)
        {
            result = 10 * result + (number % 10);
            number /= 10;
        }
        return result;
    }
};

}

namespace SumOfNumberAndItsReverseTask
{

TEST(SumOfNumberAndItsReverseTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.sumOfNumberAndReverse(443));
    ASSERT_EQ(false, solution.sumOfNumberAndReverse(63));
    ASSERT_EQ(true, solution.sumOfNumberAndReverse(181));
}

}