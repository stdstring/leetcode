#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumProduct(std::vector<int> const &nums, int k) const
    {
        constexpr long long modValue = 1000000007;
        if (nums.size() == 1)
            return static_cast<int>((nums[0] + k) % modValue);
        std::priority_queue<int, std::vector<int>, std::greater<int>> queue(nums.begin(), nums.end());
        while (k > 0)
        {
            const int minValue = queue.top();
            queue.pop();
            const int delta = std::min(k, queue.top() - minValue + 1);
            queue.emplace(minValue + delta);
            k -= delta;
        }
        if (queue.top() == 0)
            return 0;
        long long result = 1;
        while (!queue.empty())
        {
            result = (result * queue.top()) % modValue;
            queue.pop();
        }
        return static_cast<int>(result);
    }
};

}

namespace MaxProductAfterKIncrementsTask
{

TEST(MaxProductAfterKIncrementsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(20, solution.maximumProduct({0, 4}, 5));
    ASSERT_EQ(216, solution.maximumProduct({6, 3, 3, 2}, 2));
}

}