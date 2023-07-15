#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxValue(std::vector<std::vector<int>> const &events, int k) const
    {
        std::vector<std::vector<int>> sortedEvents(events);
        auto comparer = [](std::vector<int> const &l, std::vector<int> const &r) { return (l[0] < r[0]) || ((l[0] == r[0]) && (l[1] < r[1])); };
        std::ranges::sort(sortedEvents, comparer);
        std::vector<std::vector<int>> dp(sortedEvents.size(), std::vector<int>(k + 1, 0));
        return solveImpl(sortedEvents, dp, 0, k, 0);
    }

private:
    [[nodiscard]] int solveImpl(std::vector<std::vector<int>> const &sortedEvents, std::vector<std::vector<int>> &dp, size_t index, int k, int endTime) const
    {
        if (index == sortedEvents.size())
            return 0;
        if (k == 0)
            return 0;
        if (sortedEvents[index][0] <= endTime)
            return solveImpl(sortedEvents, dp, index + 1, k, endTime);
        if (dp[index][k] > 0)
            return dp[index][k];
        const int value = std::max(sortedEvents[index][2] + solveImpl(sortedEvents, dp, index + 1, k - 1, sortedEvents[index][1]),
                                   solveImpl(sortedEvents, dp, index + 1, k, endTime));
        dp[index][k] = value;
        return value;
    }
};

}

namespace MaxNumberEventsThatCanBeAttended2Task
{

TEST(MaxNumberEventsThatCanBeAttended2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.maxValue({{1, 2, 4}, {3, 4, 3}, {2, 3, 1}}, 2));
    ASSERT_EQ(10, solution.maxValue({{1, 2, 4}, {3, 4, 3}, {2, 3, 10}}, 2));
    ASSERT_EQ(9, solution.maxValue({{1, 1, 1}, {2, 2, 2}, {3, 3, 3}, {4, 4, 4}}, 3));
}

TEST(MaxNumberEventsThatCanBeAttended2TaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(291, solution.maxValue({{3, 68, 97},
                                      {12, 46, 13},
                                      {21, 24, 75},
                                      {64, 85, 74},
                                      {10, 98, 15},
                                      {23, 84, 62},
                                      {87, 96, 29},
                                      {80, 85, 39},
                                      {52, 89, 77},
                                      {31, 63, 91},
                                      {29, 40, 48},
                                      {30, 96, 42},
                                      {69, 81, 68},
                                      {52, 58, 65},
                                      {41, 52, 37}}, 10));
}

}