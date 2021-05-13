#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool checkPowersOfThree(int n) const
    {
        while (n > 0)
        {
            if (n % 3 == 2)
                return false;
            n /= 3;
        }
        return true;
    }
};

}

namespace CheckIfNumberSumOfPowersOfThreeTask
{

TEST(CheckIfNumberSumOfPowersOfThreeTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.checkPowersOfThree(12));
    ASSERT_EQ(true, solution.checkPowersOfThree(91));
    ASSERT_EQ(false, solution.checkPowersOfThree(21));
}

}