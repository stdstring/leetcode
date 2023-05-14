#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxScore(std::vector<int> const &nums) const
    {
        const size_t maskCount = 1ULL << nums.size();
        const size_t operationCount = nums.size() / 2;
        std::vector<int> dp(operationCount * maskCount, 0);
        int bestScore = 0;
        // init
        for (size_t index1 = 0; index1 < nums.size(); ++index1)
        {
            for (size_t index2 = index1 + 1; index2 < nums.size(); ++index2)
            {
                const size_t index = (1 << index1) | (1 << index2);
                dp[index] = std::gcd(nums[index1], nums[index2]);
                bestScore = std::max(bestScore, dp[index]);
            }
        }
        // calc
        for (int operation = 2; operation <= static_cast<int>(operationCount); ++operation)
        {
            const size_t currentShift = (operation - 1) * maskCount;
            const size_t prevShift = (operation - 2) * maskCount;
            for (size_t mask = 1; mask < maskCount; ++mask)
            {
                for (size_t index1 = 0; index1 < nums.size(); ++index1)
                {
                    for (size_t index2 = index1 + 1; index2 < nums.size(); ++index2)
                    {
                        const int currentMusk = (1 << index1) | (1 << index2);
                        if ((mask & currentMusk) == 0)
                        {
                            const size_t index = currentShift + mask | currentMusk;
                            dp[index] = std::max(dp[index], dp[prevShift + mask] + operation * std::gcd(nums[index1], nums[index2]));
                            bestScore = std::max(bestScore, dp[index]);
                        }
                    }
                }
            }
        }
        return bestScore;
    }
};

}

namespace MaxScoreAfterNOperationsTask
{

TEST(MaxScoreAfterNOperationsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.maxScore({1, 2}));
    ASSERT_EQ(11, solution.maxScore({3, 4, 6, 8}));
    ASSERT_EQ(14, solution.maxScore({1, 2, 3, 4, 5, 6}));
}

TEST(MaxScoreAfterNOperationsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(257, solution.maxScore({984916, 312350, 779975, 165893, 436389, 592384, 264617, 136726, 8893, 587955, 921403, 891842}));
}

}