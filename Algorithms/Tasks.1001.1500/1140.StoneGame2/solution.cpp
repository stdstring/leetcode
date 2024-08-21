#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int stoneGameII(std::vector<int> const &piles) const
    {
        const size_t pilesCount = piles.size();
        std::vector<int> suffixSum(pilesCount, 0);
        for (size_t rIndex = 0; rIndex < pilesCount; ++rIndex)
        {
            const size_t index = pilesCount - 1 - rIndex;
            suffixSum[index] = (rIndex > 0 ? suffixSum[index + 1] : 0) + piles[index];
        }
        // 1 <= m <= pilesCount
        std::vector<std::vector<int>> dp(pilesCount, std::vector<int>(pilesCount + 1, 0));
        return calcMaxStonesCanGet(suffixSum, dp, 0, 1);
    }

private:
    [[nodiscard]] int calcMaxStonesCanGet(std::vector<int> const &suffixSum, std::vector<std::vector<int>> &dp, size_t currentPile, size_t m) const
    {
        if (currentPile >= suffixSum.size())
            return 0;
        if ((currentPile + 2 * m) >= suffixSum.size())
            return suffixSum[currentPile];
        if (dp[currentPile][m] != 0)
            return dp[currentPile][m];
        int maxStones = 0;
        for (size_t x = 1; x <= 2 * m; x++)
        {
            int currentStones = suffixSum[currentPile] - calcMaxStonesCanGet(suffixSum, dp, currentPile + x, std::max(m, x));
            maxStones = std::max(maxStones, currentStones);
        }
        dp[currentPile][m] = maxStones;
        return maxStones;
    }
};

}

namespace StoneGame2Task
{

TEST(StoneGame2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(10, solution.stoneGameII({2, 7, 9, 4, 4}));
    ASSERT_EQ(104, solution.stoneGameII({1, 2, 3, 4, 5, 100}));
}

}