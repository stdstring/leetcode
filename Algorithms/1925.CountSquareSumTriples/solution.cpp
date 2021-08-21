#include <unordered_set>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int countTriples(int n) const
    {
        std::unordered_set<int> squares;
        for (int number = 1; number <= n; ++number)
            squares.insert(number * number);
        const int maxSquare = n * n;
        size_t count = 0;
        for (int a = 1; a < n; ++a)
        {
            if (2 * a * a > maxSquare)
                break;
            for (int b = a; b < n; ++b)
            {
                const int value = a * a + b * b;
                if (value > maxSquare)
                    break;
                if (squares.count(value) == 1)
                    count += (a == b ? 1 : 2);
            }
        }
        return static_cast<int>(count);
    }
};

}


namespace CountSquareSumTriplesTask
{

TEST(CountSquareSumTriplesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.countTriples(5));
    ASSERT_EQ(4, solution.countTriples(10));
}

}