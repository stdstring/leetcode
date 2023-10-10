#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int smallestDivisor(std::vector<int> const &nums, int threshold) const
    {
        const long long thresholdValue = threshold;
        if (calcDivisionResult(nums, 1) <= thresholdValue)
            return 1;
        const int maxValue = *std::ranges::max_element(nums);
        if (nums.size() == static_cast<size_t>(thresholdValue))
            return maxValue;
        int left = 1;
        int right = maxValue;
        while (left < right)
        {
            const int middle = (left + right) / 2;
            const long long middleResult = calcDivisionResult(nums, middle);
            if (middleResult > thresholdValue)
                left = middle + 1;
            else
                right = middle;
        }
        return left;
    }

private:
    [[nodiscard]] long long calcDivisionResult(std::vector<int> const &nums, int divisor) const
    {
        auto accFun = [divisor](long long acc, int number) { return acc + (number / divisor) + (number % divisor == 0 ? 0 : 1); };
        return std::accumulate(nums.cbegin(), nums.cend(), 0LL, accFun);
    }
};

}

namespace FindSmallestDivisorGivenThresholdTask
{

TEST(FindSmallestDivisorGivenThresholdTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.smallestDivisor({1, 2, 5, 9}, 6));
    ASSERT_EQ(44, solution.smallestDivisor({44, 22, 33, 11, 1}, 5));
}

TEST(FindSmallestDivisorGivenThresholdTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(34, solution.smallestDivisor({200, 100, 14}, 10));
}

}