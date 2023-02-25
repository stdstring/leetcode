#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int integerReplacement(int n) const
    {
        long long number = n;
        int count = 0;
        while (number > 1)
        {
            if (number % 2 == 0)
            {
                number /= 2;
                ++count;
            }
            else if ((number - 1) == 2)
            {
                number = 1;
                count += 2;
            }
            else
            {
                number = ((number + 1) % 4 == 0 ? (number + 1) : (number - 1)) / 4;
                count += 3;
            }
        }
        return count;
    }
};

}

namespace IntegerReplacementTask
{

TEST(IntegerReplacementTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.integerReplacement(8));
    ASSERT_EQ(4, solution.integerReplacement(7));
}

TEST(IntegerReplacementTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.integerReplacement(3));
    ASSERT_EQ(32, solution.integerReplacement(2147483647));
}


}