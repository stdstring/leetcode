#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int earliestFinishTime(std::vector<int> const &landStartTime,
                                         std::vector<int> const &landDuration,
                                         std::vector<int> const &waterStartTime,
                                         std::vector<int> const &waterDuration) const
    {
        return std::min(calcEarliestFinishTime(landStartTime, landDuration, waterStartTime, waterDuration),
                        calcEarliestFinishTime(waterStartTime, waterDuration, landStartTime, landDuration));
    }

private:
    [[nodiscard]] int calcEarliestFinishTime(std::vector<int> const &firstStartTime,
                                             std::vector<int> const &firstDuration,
                                             std::vector<int> const &secondStartTime,
                                             std::vector<int> const &secondDuration) const
    {
        int minFirstTime = INT_MAX;
        for (size_t index = 0; index < firstStartTime.size(); ++index)
        {
            minFirstTime = std::min(minFirstTime, firstStartTime[index] + firstDuration[index]);
        }
        int minSecondTime = INT_MAX;
        for (size_t index = 0; index < secondStartTime.size(); ++index)
        {
            minSecondTime = std::min(minSecondTime, std::max(minFirstTime, secondStartTime[index]) + secondDuration[index]);
        }
        return minSecondTime;
    }
};

}

namespace TwoSumTask
{

TEST(TwoSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.earliestFinishTime({2, 8}, {4, 1}, {6}, {3}));
    ASSERT_EQ(14, solution.earliestFinishTime({5}, {3}, {1}, {10}));
}

}