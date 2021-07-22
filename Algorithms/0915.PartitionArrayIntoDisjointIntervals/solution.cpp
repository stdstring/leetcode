#include <algorithm>
#include <stack>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int partitionDisjoint(std::vector<int> const &nums) const
    {
        std::stack<int> minValueRL;
        for (auto it = nums.crbegin(); it != nums.crend(); ++it)
            minValueRL.push(minValueRL.empty() ? *it : std::min(*it, minValueRL.top()));
        minValueRL.pop();
        int maxValue = nums[0];
        size_t index = 0;
        while (maxValue > minValueRL.top())
        {
            maxValue = std::max(maxValue, nums[index++]);
            minValueRL.pop();
        }
        return static_cast<int>(index + 1);
    }
};

}

namespace PartitionArrayIntoDisjointIntervalsTask
{

TEST(PartitionArrayIntoDisjointIntervalsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.partitionDisjoint({5, 0, 3, 8, 6}));
    ASSERT_EQ(4, solution.partitionDisjoint({1, 1, 1, 0, 6, 12}));
}

}