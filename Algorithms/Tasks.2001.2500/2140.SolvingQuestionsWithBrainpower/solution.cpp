#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long mostPoints(std::vector<std::vector<int>> const &questions) const
    {
        std::vector<long long> dp(questions.size() + 1, 0);
        const size_t dpMaxIndex = dp.size() - 1;
        for (size_t index = 0; index < questions.size(); ++index)
        {
            // skip
            dp[index + 1] = std::max(dp[index + 1], dp[index]);
            // answer
            size_t dest = index + questions[index][1] + 1;
            if (dest > dpMaxIndex)
                dest = dpMaxIndex;
            dp[dest] = std::max(dp[dest], dp[index] + questions[index][0]);
        }
        return dp.back();
    }
};

}

namespace SolvingQuestionsWithBrainpowerTask
{

TEST(SolvingQuestionsWithBrainpowerTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.mostPoints({{3, 2}, {4, 3}, {4, 4}, {2, 5}}));
    ASSERT_EQ(7, solution.mostPoints({{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}}));
}

TEST(SolvingQuestionsWithBrainpowerTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(157, solution.mostPoints({{21, 5}, {92, 3}, {74, 2}, {39, 4}, {58, 2}, {5, 5}, {49, 4}, {65, 3}}));
}

}