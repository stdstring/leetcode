#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumPossibleSum(int n, int target) const
    {
        constexpr long long modValue = 1000000007;
        const long long targetValue = target;
        const long long size = n;
        if (targetValue == 1)
            return static_cast<int>(calcArithProgressionSum(1, size, size) % modValue);
        const long long leftPartBorder = targetValue / 2;
        const long long leftPartSum = size <= leftPartBorder ?
                                      calcArithProgressionSum(1, size, size) :
                                      calcArithProgressionSum(1, leftPartBorder, leftPartBorder);
        const long long rightPartSum = size <= leftPartBorder ?
                                       0 :
                                       calcArithProgressionSum(targetValue, targetValue + size - leftPartBorder - 1, size - leftPartBorder);
        return static_cast<int>((leftPartSum + rightPartSum) % modValue);
    }

private:
    [[nodiscard]] long long calcArithProgressionSum(long long a1, long long an, long long n) const
    {
        return (a1 + an) * n / 2;
    }
};

}

namespace FindMinPossibleSumOfBeautifulArrayTask
{

TEST(FindMinPossibleSumOfBeautifulArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minimumPossibleSum(2, 3));
    ASSERT_EQ(8, solution.minimumPossibleSum(3, 3));
    ASSERT_EQ(1, solution.minimumPossibleSum(1, 1));
}

TEST(FindMinPossibleSumOfBeautifulArrayTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(69, solution.minimumPossibleSum(10, 6));
    ASSERT_EQ(160, solution.minimumPossibleSum(15, 10));
}

TEST(FindMinPossibleSumOfBeautifulArrayTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(91, solution.minimumPossibleSum(13, 50));
    ASSERT_EQ(750000042, solution.minimumPossibleSum(1000000000, 1000000000));
}

}