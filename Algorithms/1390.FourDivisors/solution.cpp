#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int sumFourDivisors(std::vector<int> const &nums) const
    {
        int sumValue = 0;
        for (int number : nums)
        {
            int divisorSum = 1 + number;
            size_t divisorCount = 2;
            int divisor = 2;
            while (divisor * divisor < number)
            {
                if (number % divisor == 0)
                {
                    divisorSum += (divisor + number / divisor);
                    divisorCount += 2;
                }
                if (divisorCount > 4)
                    break;
                ++divisor;
            }
            if (divisor * divisor == number)
                ++divisorCount;
            if (divisorCount == 4)
                sumValue += divisorSum;
        }
        return sumValue;
    }
};

}

namespace FourDivisorsTask
{

TEST(FourDivisorsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(32, solution.sumFourDivisors({21, 4, 7}));
    ASSERT_EQ(64, solution.sumFourDivisors({21, 21}));
    ASSERT_EQ(0, solution.sumFourDivisors({1, 2, 3, 4, 5}));
}

TEST(FourDivisorsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.sumFourDivisors({83521}));
}

}