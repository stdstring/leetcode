#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int fib(int n) const
    {
        if (n == 0)
            return 0;
        int prev = 0;
        int current = 1;
        for (int number = 1; number < n; ++number)
        {
            const int next = current + prev;
            prev = current;
            current = next;
        }
        return current;
    }
};

}

namespace FibonacciNumberTask
{

TEST(FibonacciNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.fib(2));
    ASSERT_EQ(2, solution.fib(3));
    ASSERT_EQ(3, solution.fib(4));
}

}