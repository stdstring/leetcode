#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int canCompleteCircuit(std::vector<int> const &gas, std::vector<int> const &cost) const
    {
        if (gas.size() == 1)
            return gas[0] >= cost[0] ? 0 : -1;
        int volume = gas[0] - cost[0];
        size_t start = 0;
        size_t finish = 1;
        while (start != finish)
        {
            if (volume < 0)
            {
                start = start == 0 ? gas.size() - 1 : start - 1;
                volume += (gas[start] - cost[start]);
            }
            else
            {
                volume += (gas[finish] - cost[finish]);
                finish = finish == (gas.size() - 1) ? 0 : finish + 1;
            }
        }
        return volume >= 0 ? static_cast<int>(start) : -1;
    }
};

}

namespace GasStationTask
{

TEST(GasStationTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.canCompleteCircuit({1, 2, 3, 4, 5}, {3, 4, 5, 1, 2}));
    ASSERT_EQ(-1, solution.canCompleteCircuit({2, 3, 4}, {3, 4, 3}));
}

TEST(GasStationTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(-1, solution.canCompleteCircuit({4}, {5}));
}

}