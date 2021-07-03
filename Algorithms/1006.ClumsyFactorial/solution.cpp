#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int clumsy(int n) const
    {
        if (n == 1)
            return 1;
        if (n == 2)
            return 2 * 1;
        if (n == 3)
            return 3 * 2 / 1;
        int result = n * (n - 1) / (n - 2) + (n - 3);
        n -= 4;
        while (n > 0)
        {
            int term = n--;
            if (n > 0)
                term *= n--;
            if (n > 0)
                term /= n--;
            result -= term;
            if (n > 0)
                result += n--;
        }
        return result;
    }
};

}

namespace ClumsyFactorialTask
{

TEST(ClumsyFactorialTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(7, solution.clumsy(4));
    ASSERT_EQ(12, solution.clumsy(10));
}

}