#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int earliestFullBloom(std::vector<int> const &plantTime, std::vector<int> const &growTime) const
    {
        std::vector<size_t> indices(growTime.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&growTime](size_t left, size_t right){ return growTime[left] > growTime[right]; });
        int plantStart = 0;
        int totalBloomStart = 0;
        for (const size_t index : indices)
        {
            plantStart += plantTime[index];
            totalBloomStart = std::max(totalBloomStart, plantStart + growTime[index]);
        }
        return totalBloomStart;
    }
};

}

namespace EarliestPossibleDayOfFullBloomTask
{

TEST(EarliestPossibleDayOfFullBloomTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.earliestFullBloom({1, 4, 3}, {2, 3, 1}));
    ASSERT_EQ(9, solution.earliestFullBloom({1, 2, 3, 2}, {2, 1, 2, 1}));
    ASSERT_EQ(2, solution.earliestFullBloom({1}, {1}));
}

}