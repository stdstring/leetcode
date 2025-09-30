#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minScoreTriangulation(std::vector<int> const &values) const
    {
        const size_t vertexCount = values.size();
        std::vector<std::vector<int>> dp(vertexCount, std::vector<int>(vertexCount, 0));
        return minScoreTriangulationImpl(values, dp, 0, vertexCount - 1);
    }

private:
    [[nodiscard]] int minScoreTriangulationImpl(std::vector<int> const &values, std::vector<std::vector<int>> &dp, size_t i, size_t j) const
    {
        if (dp[i][j] != 0)
            return dp[i][j];
        int result = 0;
        for (size_t k = i + 1; k < j; ++k)
        {
            int current = minScoreTriangulationImpl(values, dp, i, k) +
                          values[i] * values[j] * values[k] +
                          minScoreTriangulationImpl(values, dp, k, j);
            result = std::min(result == 0 ? INT_MAX : result, current);
        }
        dp[i][j] = result;
        return result;
    }
};

}

namespace MinScoreTriangulationPolygonTask
{

TEST(MinScoreTriangulationPolygonTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.minScoreTriangulation({1, 2, 3}));
    ASSERT_EQ(144, solution.minScoreTriangulation({3, 7, 4, 5}));
    ASSERT_EQ(13, solution.minScoreTriangulation({1, 3, 1, 4, 1, 5}));
}

}