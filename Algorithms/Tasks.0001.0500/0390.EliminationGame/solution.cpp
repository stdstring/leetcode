#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int lastRemaining(int n) const
    {
        // description
        // 1) if array contains 1 element, then we have the answer
        // 2) on each step we remove n / 2 + n % 2 elements (n / 2 remains in array)
        // 3) after that, we reverse the array and move into the next step
        if (n == 1)
            return 1;
        // prev result
        const int prev = lastRemaining(n / 2);
        // prev is calculated for inverse array
        return n - 2 * (prev - 1) - n % 2;
    }
};

}

namespace EliminationGameTask
{

TEST(EliminationGameTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(6, solution.lastRemaining(9));
    ASSERT_EQ(1, solution.lastRemaining(1));
}

TEST(EliminationGameTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(22, solution.lastRemaining(48));
}

}