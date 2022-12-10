#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> missingRolls(std::vector<int> const &rolls, int mean, int n) const
    {
        const int totalSum = mean * static_cast<int>(n + rolls.size());
        const int rollsSum = std::accumulate(rolls.cbegin(), rolls.cend(), 0);
        const int missingSum = totalSum - rollsSum;
        if ((missingSum < 1 * n) || (6 * n < missingSum))
            return {};
        if (missingSum % n == 0)
            return std::vector<int>(n, missingSum / n);
        const int lessValue = missingSum / n;
        int greaterValue = lessValue + 1;
        const int lessValueCount = n * greaterValue - missingSum;
        const size_t greaterValueCount = n - lessValueCount;
        std::vector<int> result(lessValueCount, lessValue);
        for (size_t index = 0; index < greaterValueCount; ++index)
            result.emplace_back(greaterValue);
        return result;
    }
};

}

namespace FindMissingObservationsTask
{

TEST(FindMissingObservationsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({6, 6}), solution.missingRolls({3, 2, 4, 3}, 4, 2));
    ASSERT_EQ(std::vector<int>({2, 2, 2, 3}), solution.missingRolls({1, 5, 6}, 3, 4));
    ASSERT_EQ(std::vector<int>(), solution.missingRolls({1, 2, 3, 4}, 6, 4));
}

}