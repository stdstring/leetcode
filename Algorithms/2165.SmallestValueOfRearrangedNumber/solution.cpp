#include <array>
#include <cstdlib>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long smallestNumber(long long num) const
    {
        if (num == 0)
            return 0;
        constexpr int digitsCount = 10;
        std::array<size_t, digitsCount> digits{};
        digits.fill(0);
        const bool isNegative = num < 0;
        num = std::abs(num);
        while (num > 0)
        {
            ++digits[num % 10];
            num /= 10;
        }
        long long result = 0;
        if (isNegative)
        {
            for (int rDigit = 0; rDigit < digitsCount; ++rDigit)
                result = appendDigit(result, digitsCount - rDigit - 1, digits[0LL + digitsCount - rDigit - 1]);
            result *= -1;
        }
        else
        {
            for (int digit = 1; digit < digitsCount; ++digit)
            {
                if (digits[digit] > 0)
                {
                    result = digit;
                    --digits[digit];
                    break;
                }
            }
            for (int digit = 0; digit < digitsCount; ++digit)
                result = appendDigit(result, digit, digits[digit]);
        }
        return result;
    }

private:
    [[nodiscard]] long long appendDigit(long long number, int digit, size_t count) const
    {
        for (size_t index = 0; index < count; ++index)
            number = 10 * number + digit;
        return number;
    }
};

}

namespace SmallestValueOfRearrangedNumberTask
{

TEST(SmallestValueOfRearrangedNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(103, solution.smallestNumber(310));
    ASSERT_EQ(-7650, solution.smallestNumber(-7605));
}

}