#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int consecutiveNumbersSum(int N) const
    {
        // Description:
        // Let N can be write as a sum of termCount consecutive positive integers,
        // then N = a + (a + 1) + ... + (a + termCount - 1) = termCount * a + (termCount) * (termCount - 1) / 2
        size_t caseCount = 1;
        int termCount = 2;
        while (true)
        {
            const int tail = termCount * (termCount - 1) / 2;
            if (tail >= N)
                break;
            const int body = N - tail;
            const int quotient = body / termCount;
            const int rest = body % termCount;
            if (rest == 0)
                ++caseCount;
            if (quotient == 1)
                break;
            ++termCount;
        }
        return caseCount;
    }
};

}

namespace
{

TEST(TwoSumTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.consecutiveNumbersSum(5));
    ASSERT_EQ(3, solution.consecutiveNumbersSum(9));
    ASSERT_EQ(4, solution.consecutiveNumbersSum(15));
}

}