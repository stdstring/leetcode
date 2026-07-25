#include <algorithm>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxProduct(int n) const
    {
        int digit1 = 0;
        int digit2 = 0;
        for (; n > 0; n /= 10)
        {
            const int current = n % 10;
            if (current >= digit1)
            {
                std::swap(digit1, digit2);
                digit1 = current;
            }
            else if (current > digit2)
                digit2 = current;
        }
        return digit1 * digit2;
    }
};

}

namespace MaxProductTwoDigitsTask
{

TEST(MaxProductTwoDigitsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxProduct(31));
    ASSERT_EQ(4, solution.maxProduct(22));
    ASSERT_EQ(8, solution.maxProduct(124));
}

TEST(MaxProductTwoDigitsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.maxProduct(10));
}

}