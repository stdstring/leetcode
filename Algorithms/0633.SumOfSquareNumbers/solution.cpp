#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool judgeSquareSum(int c) const
    {
        // from https://en.wikipedia.org/wiki/Sum_of_two_squares_theorem
        if (c == 0)
            return true;
        int factor = 3;
        eraseFactor(c, 2);
        while ((c > 1) && (factor * factor <= c))
        {
            if (c % factor == 0)
            {
                const int power = eraseFactor(c, factor);
                if ((factor % 4 == 3) && (power % 2 == 1))
                    return false;
            }
            factor += 2;
        }
        return c % 4 != 3;
    }

private:
    int eraseFactor(int &number, int factor) const
    {
        int power = 0;
        while (number % factor == 0)
        {
            ++power;
            number /= factor;
        }
        return power;
    }
};

}

namespace SumOfSquareNumbersTask
{

TEST(SumOfSquareNumbersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.judgeSquareSum(5));
    ASSERT_EQ(false, solution.judgeSquareSum(3));
    ASSERT_EQ(true, solution.judgeSquareSum(4));
    ASSERT_EQ(true, solution.judgeSquareSum(2));
    ASSERT_EQ(true, solution.judgeSquareSum(1));
}

TEST(SumOfSquareNumbersTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.judgeSquareSum(0));
}

}