#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int preimageSizeFZF(int k) const
    {
        const long long zeroCount = k;
        const long long maxNumber = 5LL * zeroCount;
        std::vector<long long> powers5;
        for (long long current = 5; current <= maxNumber; current *= 5)
            powers5.emplace_back(current);
        long long left = 0;
        long long right = maxNumber;
        while (right > left)
        {
            const long long middle = (left + right) / 2;
            const long long tailZeroCount = calcTailZeroCount(middle, powers5);
            if (tailZeroCount == zeroCount)
                return 5;
            if (tailZeroCount < zeroCount)
                left = middle + 1;
            else
                right = middle;
        }
        return calcTailZeroCount(left, powers5) == zeroCount ? 5 : 0;
    }

private:
    [[nodiscard]] long long calcTailZeroCount(long long n, std::vector<long long> const &powers5) const
    {
        long long tailZeroCount = 0;
        for (const long long power5 : powers5)
        {
            if (power5 > n)
                break;
            tailZeroCount += n / power5;
        }
        return tailZeroCount;
    }
};

}

namespace PreimageSizeFactorialZeroesFunTask
{

TEST(PreimageSizeFactorialZeroesFunTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.preimageSizeFZF(0));
    ASSERT_EQ(0, solution.preimageSizeFZF(5));
    ASSERT_EQ(5, solution.preimageSizeFZF(3));
}

TEST(PreimageSizeFactorialZeroesFunTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.preimageSizeFZF(121));
    ASSERT_EQ(0, solution.preimageSizeFZF(123453));
}

}