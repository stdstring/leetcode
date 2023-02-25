#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countEven(int num) const
    {
        size_t count = 0;
        for (int current = 1; current <= num; ++current)
        {
            if (calcDigitSum(current) % 2 == 0)
                ++count;
        }
        return static_cast<int>(count);
    }

private:
    [[nodiscard]] int calcDigitSum(int num) const
    {
        int digitSum = 0;
        while (num > 0)
        {
            digitSum += (num % 10);
            num /= 10;
        }
        return digitSum;
    }
};

}

namespace CountIntegersWithEvenDigitSumTask
{

TEST(CountIntegersWithEvenDigitSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.countEven(4));
    ASSERT_EQ(14, solution.countEven(30));
}

}
