#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minStoneSum(std::vector<int> const &piles, int k) const
    {
        int totalPiles = 0;
        std::priority_queue<int> queue;
        for (int pile : piles)
        {
            queue.push(pile);
            totalPiles += pile;
        }
        for (int operation = 1; operation <= k; ++operation)
        {
            const int pile = queue.top();
            queue.pop();
            totalPiles -= (pile / 2);
            queue.push(pile - pile / 2);
        }
        return totalPiles;
    }
};

}

namespace RemoveStonesToMinimizeTotalTask
{

TEST(RemoveStonesToMinimizeTotalTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(12, solution.minStoneSum({5, 4, 9}, 2));
    ASSERT_EQ(12, solution.minStoneSum({4, 3, 6, 7}, 3));
}

}