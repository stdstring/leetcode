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
        int result = INT_MAX;
        for (size_t landIndex = 0; landIndex < landStartTime.size(); ++landIndex)
        {
            const int lStart = landStartTime[landIndex];
            const int lDuration = landDuration[landIndex];
            const int lEnd = lStart + lDuration;
            for (size_t waterIndex = 0; waterIndex < waterStartTime.size(); ++waterIndex)
            {
                const int wStart = waterStartTime[waterIndex];
                const int wDuration = waterDuration[waterIndex];
                const int wEnd = wStart + wDuration;
                result = std::min(result, lEnd < wStart ? wEnd : lEnd + wDuration);
                result = std::min(result, wEnd < lStart ? lEnd : wEnd + lDuration);
            }
        }
        return result;
    }
};

}

namespace EarliestFinishTime4LandWaterRides1Task
{

TEST(EarliestFinishTime4LandWaterRides1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.earliestFinishTime({2, 8}, {4, 1}, {6}, {3}));
    ASSERT_EQ(14, solution.earliestFinishTime({5}, {3}, {1}, {10}));
}

}