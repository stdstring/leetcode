#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> closestDivisors(int num) const
    {
        std::vector<int> divisors1(calcClosestDivisors(num + 1));
        const int diff1 = divisors1[1] - divisors1[0];
        std::vector<int> divisors2(calcClosestDivisors(num + 2));
        const int diff2 = divisors2[1] - divisors2[0];
        return diff1 < diff2 ? divisors1 : divisors2;
    }

private:
    [[nodiscard]] std::vector<int> calcClosestDivisors(int num) const
    {
        std::vector<int> result({1, num});
        for (int divisor = 2; divisor * divisor <= num; ++divisor)
        {
            if ((num % divisor) == 0)
            {
                result[0] = divisor;
                result[1] = num / divisor;
            }
        }
        return result;
    }
};

}

namespace ClosestDivisorsTask
{

TEST(ClosestDivisorsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, 3}), solution.closestDivisors(8));
    ASSERT_EQ(std::vector<int>({5, 25}), solution.closestDivisors(123));
    ASSERT_EQ(std::vector<int>({25, 40}), solution.closestDivisors(999));
}

}