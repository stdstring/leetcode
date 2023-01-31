#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int bestTeamScore(std::vector<int> const &scores, std::vector<int> const &ages) const
    {
        std::vector<size_t> indices(scores.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&scores, &ages](size_t l, size_t r) { return (ages[l] < ages[r]) || ((ages[l] == ages[r]) && (scores[l] < scores[r])); });
        std::vector<int> dp(indices.size(), 0);
        int maxScores = 0;
        for (size_t current = 0; current < indices.size(); ++current)
        {
            dp[current] = scores[indices[current]];
            maxScores = std::max(maxScores, dp[current]);
            for (size_t index = 0; index < current; ++index)
            {
                if (scores[indices[index]] <= scores[indices[current]])
                {
                    dp[current] = std::max(dp[current], dp[index] + scores[indices[current]]);
                    maxScores = std::max(maxScores, dp[current]);
                }
            }
        }
        return maxScores;
    }
};

}

namespace BestTeamWithNoConflictsTask
{

TEST(BestTeamWithNoConflictsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(34, solution.bestTeamScore({1, 3, 5, 10, 15}, {1, 2, 3, 4, 5}));
    ASSERT_EQ(16, solution.bestTeamScore({4, 5, 6, 5}, {2, 1, 2, 1}));
    ASSERT_EQ(6, solution.bestTeamScore({1, 2, 3, 5}, {8, 9, 10, 1}));
}

}