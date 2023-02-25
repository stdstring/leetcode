#include <limits>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int reverse(int x) const
    {
        if (x == 0)
            return 0;
        const bool sign = x < 0;
        std::vector<int> digits;
        long long sourceValue = x;
        if (sign)
            sourceValue = - sourceValue;
        // digits in reverse order
        while (sourceValue > 0)
        {
            digits.push_back(sourceValue % 10);
            sourceValue /= 10;
        }
        // reversed number
        long long destValue = 0;
        for (int digit : digits)
            destValue = 10 * destValue + digit;
        if (sign)
            destValue = - destValue;
        return destValue > std::numeric_limits<int>::max() || destValue < std::numeric_limits<int>::min() ? 0 : static_cast<int>(destValue);
    }
};

}

namespace ReverseIntegerTask
{

TEST(ReverseIntegerTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(321, solution.reverse(123));
    ASSERT_EQ(-321, solution.reverse(-123));
    ASSERT_EQ(21, solution.reverse(120));
}

TEST(ReverseIntegerTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.reverse(INT_MIN));
}

}