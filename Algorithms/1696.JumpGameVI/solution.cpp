#include <queue>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxResult(std::vector<int> const &nums, int k) const
    {
        const size_t maxShift = k;
        std::priority_queue<std::pair<int, size_t>> queue;
        int currentScore = nums[0];
        queue.emplace(currentScore, 0);
        for (size_t index = 1; index < nums.size(); ++index)
        {
            while ((queue.top().second + maxShift) < index)
                queue.pop();
            currentScore = queue.top().first + nums[index];
            queue.emplace(currentScore, index);
        }
        return currentScore;
    }
};

}

namespace JumpGameVITask
{

TEST(JumpGameVITaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(7, solution.maxResult({1, -1, -2, 4, -7, 3}, 2));
    ASSERT_EQ(17, solution.maxResult({10, -5, -2, 4, 0, 3}, 3));
    ASSERT_EQ(0, solution.maxResult({1, -5, -20, 4, -1, 3, -6, -3}, 2));
}

}