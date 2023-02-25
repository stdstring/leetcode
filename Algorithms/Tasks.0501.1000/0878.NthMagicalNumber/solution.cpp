#include <algorithm>
#include <numeric>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int nthMagicalNumber(int n, int a, int b) const
    {
        constexpr int64_t modValue = 1000000007;
        if (a > b)
            std::swap(a, b);
        if (n == 1)
            return a;
        if ((b % a) == 0)
            return static_cast<int>((1LL * a * n) % modValue);
        const int lcm = std::lcm(a, b);
        int64_t left = 1;
        int64_t right = 1LL * a * n;
        while (left < right)
        {
            int64_t middle = getLEMagicalNumber((left + right) / 2, a, b);
            if (middle == left)
                middle = getNextMagicalNumber(middle, a, b);
            const int magicalNumberPos = calcMagicalNumberPos(middle, a, b, lcm);
            if (magicalNumberPos == n)
                return static_cast<int>(middle % modValue);
            std::swap(magicalNumberPos < n ? left : right, middle);
        }
        return static_cast<int>(left % modValue);
    }

private:
    [[nodiscard]] int64_t getLEMagicalNumber(int64_t number, int64_t a, int64_t b) const
    {
        return std::max((number / a) * a, (number / b) * b);
    }

    [[nodiscard]] int64_t getNextMagicalNumber(int64_t magicalNumber, int64_t a, int64_t b) const
    {
        return std::min((1 + magicalNumber / a) * a, (1 + magicalNumber / b) * b);
    }

    [[nodiscard]] int calcMagicalNumberPos(int64_t magicalNumber, int a, int b, int lcm) const
    {
        return static_cast<int>(magicalNumber / a + magicalNumber / b - magicalNumber / lcm);
    }
};

}

namespace NthMagicalNumberTask
{

TEST(NthMagicalNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.nthMagicalNumber(1, 2, 3));
    ASSERT_EQ(6, solution.nthMagicalNumber(4, 2, 3));
    ASSERT_EQ(10, solution.nthMagicalNumber(5, 2, 4));
    ASSERT_EQ(8, solution.nthMagicalNumber(3, 6, 4));
}

}