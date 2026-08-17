#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int stoneGameV(std::vector<int> const &stoneValue) const
    {
        const size_t stoneCount = stoneValue.size();
        std::vector<int> prefixSum(stoneCount + 1, 0);
        for (size_t index = 0; index < stoneCount; ++index)
            prefixSum[index + 1] = prefixSum[index] + stoneValue[index];
        std::vector<std::vector<int>> dp(stoneCount, std::vector<int>(stoneCount, -1));
        return calcForRange(0, stoneCount - 1, prefixSum, dp);
    }

private:
    [[nodiscard]] int calcForRange(size_t left, size_t right, std::vector<int> const &prefixSum, std::vector<std::vector<int>> &dp) const
    {
        if (left == right)
            return 0;
        if (dp[left][right] != -1)
            return dp[left][right];
        int result = 0;
        for (size_t k = left; k < right; ++k)
        {
            const int leftSum = prefixSum[k + 1] - prefixSum[left];
            const int rightSum = prefixSum[right + 1] - prefixSum[k + 1];
            if (leftSum < rightSum)
            {
                if (result >= 2 * leftSum)
                    continue;
                result = std::max(result, leftSum + calcForRange(left, k, prefixSum, dp));
            }
            if (leftSum > rightSum)
            {
                if (result >= 2 * rightSum)
                    continue;
                result = std::max(result, rightSum + calcForRange(k + 1, right, prefixSum, dp));
            }
            if (leftSum == rightSum)
                result = std::max({result, leftSum + calcForRange(left, k, prefixSum, dp), rightSum + calcForRange(k + 1, right, prefixSum, dp)});
        }
        dp[left][right] = result;
        return result;
    }
};

}

namespace StoneGameVTask
{

TEST(StoneGameVTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(18, solution.stoneGameV({6, 2, 3, 4, 5, 5}));
    ASSERT_EQ(28, solution.stoneGameV({7, 7, 7, 7, 7, 7, 7}));
    ASSERT_EQ(0, solution.stoneGameV({4}));
}

}
