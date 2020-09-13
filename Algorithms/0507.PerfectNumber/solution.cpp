#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool checkPerfectNumber(int num) const
    {
        if (num == 1)
            return false;
        int sum = 1;
        int divisor = 2;
        while (divisor * divisor <= num)
        {
            if (num % divisor == 0)
            {
                const int otherDivisor = num / divisor;
                sum += divisor;
                if (divisor != otherDivisor)
                    sum += otherDivisor;
            }
            ++divisor;
            if (sum > num)
                return false;
        }
        return sum == num;
    }
};

}

namespace PerfectNumberTask
{

TEST(PerfectNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.checkPerfectNumber(28));
}

TEST(PerfectNumberTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.checkPerfectNumber(1));
}

}