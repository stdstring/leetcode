#include <algorithm>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minSum(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        auto [zeroCount1, sum1] = calcNumbersData(nums1);
        auto [zeroCount2, sum2] = calcNumbersData(nums2);
        if ((zeroCount1 == 0) && (zeroCount2 == 0))
            return sum1 != sum2 ? -1 : sum1;
        if (zeroCount1 == 0)
            return (sum2 + zeroCount2) > sum1 ? -1 : sum1;
        if (zeroCount2 == 0)
            return (sum1 + zeroCount1) > sum2 ? -1 : sum2;
        return std::max(sum1 + zeroCount1, sum2 + zeroCount2);
    }

private:
    [[nodiscard]] std::pair<int, long long> calcNumbersData(std::vector<int> const &numbers) const
    {
        int zeroCount = 0;
        long long sum = 0;
        for (const int number : numbers)
        {
            sum += number;
            if (number == 0)
                ++zeroCount;
        }
        return std::pair<int, long long>(zeroCount, sum);
    }
};

}

namespace MinEqualSumTwoArraysAfterReplacingZerosTask
{

TEST(MinEqualSumTwoArraysAfterReplacingZerosTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(12, solution.minSum({3, 2, 0, 1, 0}, {6, 5, 0}));
    ASSERT_EQ(-1, solution.minSum({2, 0, 2, 0}, {1, 4}));
}

}