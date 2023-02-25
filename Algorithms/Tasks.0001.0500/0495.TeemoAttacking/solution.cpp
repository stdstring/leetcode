#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int findPoisonedDuration(std::vector<int> const &timeSeries, int duration) const
    {
        int totalSeconds = 0;
        for (size_t index = 0; index < timeSeries.size() - 1; ++index)
            totalSeconds += std::min(duration, timeSeries[index + 1] - timeSeries[index]);
        return totalSeconds + duration;
    }
};

}

namespace TeemoAttackingTask
{

TEST(TeemoAttackingTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.findPoisonedDuration({1, 4}, 2));
    ASSERT_EQ(3, solution.findPoisonedDuration({1, 2}, 2));
}

}