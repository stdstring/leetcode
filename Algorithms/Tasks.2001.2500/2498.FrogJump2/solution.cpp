#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxJump(std::vector<int> const &stones) const
    {
        int cost = 0;
        // forward: 0 -> 2 -> 4 -> ...
        for (size_t index = 2; index < stones.size(); index += 2)
            cost = std::max(cost, stones[index] - stones[index - 2]);
        if ((stones.size() % 2) == 0)
            cost = std::max(cost, stones[stones.size() - 1] - stones[stones.size() - 2]);
        // backward n-1 -> n-3 -> ... (when n is even) || n-1 -> n-2 -> n-4 -> ... (when n is odd)
        for (size_t rIndex = (stones.size() % 2) == 0 ? 2 : 3; rIndex < stones.size(); rIndex += 2)
        {
            const size_t index = stones.size() - 1 - rIndex;
            cost = std::max(cost, stones[index + 2] - stones[index]);
        }
        if ((stones.size() % 2) != 0)
        {
            cost = std::max(cost, stones[stones.size() - 1] - stones[stones.size() - 2]);
            cost = std::max(cost, stones[1] - stones[0]);
        }
        return cost;
    }
};

}

namespace FrogJump2Task
{

TEST(FrogJump2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.maxJump({0, 2, 5, 6, 7}));
    ASSERT_EQ(9, solution.maxJump({0, 3, 9}));
}

}