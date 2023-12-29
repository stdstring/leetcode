#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minDifficulty(std::vector<int> const &jobDifficulty, int d) const
    {
        const size_t daysCount = d;
        if (jobDifficulty.size() < daysCount)
            return -1;
        if (jobDifficulty.size() == daysCount)
            return std::accumulate(jobDifficulty.cbegin(), jobDifficulty.cend(), 0);
        if (daysCount == 1)
            return *std::ranges::max_element(jobDifficulty);
        std::vector<int> currentDpRow(jobDifficulty.size(), INT_MAX);
        // first day
        int firstMaxDifficulty = INT_MIN;
        for (size_t finish = 0; finish < jobDifficulty.size(); ++finish)
            currentDpRow[finish] = firstMaxDifficulty = std::max(firstMaxDifficulty, jobDifficulty[finish]);
        // inner days
        for (size_t day = 1; day < daysCount - 1; ++day)
        {
            std::vector<int> nextDpRow(jobDifficulty.size(), INT_MAX);
            for (size_t start = day; start < jobDifficulty.size(); ++start)
            {
                const int prevValue = currentDpRow[start - 1];
                int maxDifficulty = INT_MIN;
                for (size_t finish = start; finish < jobDifficulty.size(); ++finish)
                {
                    maxDifficulty = std::max(maxDifficulty, jobDifficulty[finish]);
                    nextDpRow[finish] = std::min(nextDpRow[finish], prevValue + maxDifficulty);
                }
            }
            std::swap(currentDpRow, nextDpRow);
        }
        // last day
        int result = INT_MAX;
        int lastMaxDifficulty = INT_MIN;
        for (size_t index = jobDifficulty.size() - 1; index >= daysCount - 1; --index)
        {
            lastMaxDifficulty = std::max(lastMaxDifficulty, jobDifficulty[index]);
            result = std::min(result, currentDpRow[index - 1] + lastMaxDifficulty);
        }
        return result;
    }
};

}

namespace MinDifficultyOfJobScheduleTask
{

TEST(MinDifficultyOfJobScheduleTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.minDifficulty({6, 5, 4, 3, 2, 1}, 2));
    ASSERT_EQ(-1, solution.minDifficulty({9, 9, 9}, 4));
    ASSERT_EQ(3, solution.minDifficulty({1, 1, 1}, 3));
}

TEST(MinDifficultyOfJobScheduleTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(843, solution.minDifficulty({11, 111, 22, 222, 33, 333, 44, 444}, 6));
}

}