#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long makeIntegerBeautiful(long long n, int target) const
    {
        long long term = 0;
        while (calcDigitsSum(n) > target)
        {
            long long factor = 1;
            long long current = n;
            while ((current % 10) == 0)
            {
                current /= 10;
                factor *= 10;
            }
            const long long digit = current % 10;
            term += (10 - digit) * factor;
            n += (10 - digit) * factor;
        }
        return term;
    }

private:
    [[nodiscard]] int calcDigitsSum(long long n) const
    {
        int digitsSum = 0;
        while (n > 0)
        {
            digitsSum += static_cast<int>(n % 10);
            n /= 10;
        }
        return digitsSum;
    }
};

}

namespace MinAdditionToMakeIntBeautifulTask
{

TEST(MinAdditionToMakeIntBeautifulTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.makeIntegerBeautiful(16, 6));
    ASSERT_EQ(33, solution.makeIntegerBeautiful(467, 6));
    ASSERT_EQ(0, solution.makeIntegerBeautiful(1, 1));
}

}