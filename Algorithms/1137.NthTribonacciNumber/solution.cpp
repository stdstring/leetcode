#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int tribonacci(int n) const
    {
        if (n == 0)
            return 0;
        if (n == 1 || n == 2)
            return 1;
        int first = 0;
        int second = 1;
        int third = 1;
        n -= 2;
        while (n > 0)
        {
            const int current = first + second + third;
            first = second;
            second = third;
            third = current;
            --n;
        }
        return third;
    }
};

}

namespace NthTribonacciNumberTask
{

TEST(NthTribonacciNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.tribonacci(4));
    ASSERT_EQ(1389537, solution.tribonacci(25));
}


}