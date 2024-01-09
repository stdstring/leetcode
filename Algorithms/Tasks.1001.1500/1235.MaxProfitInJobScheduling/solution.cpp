#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int jobScheduling(std::vector<int> const &startTime, std::vector<int> const &endTime, std::vector<int> const &profit) const
    {
        const size_t jobCount = startTime.size();
        std::vector<size_t> indices(jobCount, 0);
        std::iota(indices.begin(), indices.end(), 0);
        auto comp = [&startTime, &endTime, &profit](size_t l, size_t r)
        {
            return (endTime[l] < endTime[r]) ||
                   ((endTime[l] == endTime[r]) && (startTime[l] < startTime[r])) ||
                   ((endTime[l] == endTime[r]) && (startTime[l] == startTime[r]) && (profit[l] < profit[r]));
        };
        std::ranges::sort(indices, comp);
        std::vector<int> dp(jobCount, 0);
        for (size_t index = 0; index < jobCount; ++index)
        {
            const int jobStartTime = startTime[indices[index]];
            const int jobProfit = profit[indices[index]];
            const int prevProfit = (index > 0 ? dp[index - 1] : 0);
            const auto closestFinishedJob = std::upper_bound(indices.cbegin(),
                                                             std::next(indices.cbegin(), static_cast<int>(index + 1)),
                                                             jobStartTime,
                                                             [&endTime](int time, size_t index) { return time < endTime[index]; });
            const size_t closestFinishedJobIndex = std::distance(indices.cbegin(), closestFinishedJob);
            const int currentProfit = jobProfit + (closestFinishedJobIndex == 0 ? 0 : dp[closestFinishedJobIndex - 1]);
            dp[index] = std::max(prevProfit, currentProfit);
        }
        return dp.back();
    }
};

}

namespace MaxProfitInJobSchedulingTask
{

TEST(MaxProfitInJobSchedulingTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(120, solution.jobScheduling({1, 2, 3, 3}, {3, 4, 5, 6}, {50, 10, 40, 70}));
    ASSERT_EQ(150, solution.jobScheduling({1, 2, 3, 4, 6}, {3, 5, 10, 6, 9}, {20, 20, 100, 70, 60}));
    ASSERT_EQ(6, solution.jobScheduling({1, 1, 1}, {2, 3, 4}, {5, 6, 4}));
}

TEST(MaxProfitInJobSchedulingTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(41, solution.jobScheduling({6, 15, 7, 11, 1, 3, 16, 2}, {19, 18, 19, 16, 10, 8, 19, 8}, {2, 9, 1, 19, 5, 7, 3, 19}));
    ASSERT_EQ(20, solution.jobScheduling({24, 24, 7, 2, 1, 13, 6, 14, 18, 24}, {27, 27, 20, 7, 14, 22, 20, 24, 19, 27}, {6, 1, 4, 2, 3, 6, 5, 6, 9, 8}));
}

}