#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int lastStoneWeight(std::vector<int> const &stones) const
    {
        std::priority_queue<int> queue(stones.cbegin(), stones.cend());
        while (queue.size() > 1)
        {
            const int first = queue.top();
            queue.pop();
            const int second = queue.top();
            queue.pop();
            if (first > second)
                queue.push(first - second);
        }
        return queue.empty() ? 0 : queue.top();
    }
};

}

namespace LastStoneWeightTask
{

TEST(LastStoneWeightTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.lastStoneWeight({2, 7, 4, 1, 8, 1}));
    ASSERT_EQ(1, solution.lastStoneWeight({1}));
}

}