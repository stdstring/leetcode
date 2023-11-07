#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int eliminateMaximum(std::vector<int> const &dist, std::vector<int> const &speed) const
    {
        std::vector<int> times(dist.size(), 0);
        for (size_t index = 0; index < dist.size(); ++index)
            times[index] = (dist[index] / speed[index]) + ((dist[index] % speed[index]) > 0 ? 1 : 0);
        std::ranges::sort(times);
        int currentTime = 0;
        for (size_t index = 0; index < times.size(); ++index)
        {
            if (times[index] <= currentTime)
                return static_cast<int>(index);
            ++currentTime;
        }
        return static_cast<int>(dist.size());
    }
};

}

namespace EliminateMaxNumberMonstersTask
{

TEST(EliminateMaxNumberMonstersTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.eliminateMaximum({1, 3, 4}, {1, 1, 1}));
    ASSERT_EQ(1, solution.eliminateMaximum({1, 1, 2, 3}, {1, 1, 1, 1}));
    ASSERT_EQ(1, solution.eliminateMaximum({3, 2, 4}, {5, 3, 2}));
}

TEST(EliminateMaxNumberMonstersTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.eliminateMaximum({4, 2, 3}, {2, 1, 1}));
}

}