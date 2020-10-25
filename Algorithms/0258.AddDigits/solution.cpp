#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int addDigits(int num) const
    {
        if (num == 0)
            return 0;
        return num % 9 == 0 ? 9 : num % 9;
    }
};

}

namespace AddDigitsTask
{

TEST(AddDigitsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.addDigits(38));
}

TEST(AddDigitsTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.addDigits(0));
}

}