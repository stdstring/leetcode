#include <algorithm>
#include <cstdint>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int arrayNesting(std::vector<int> const &nums) const
    {
        int maxSize = 0;
        std::vector<uint8_t> visited(nums.size(), 0);
        for (int number = 0; number < static_cast<int>(nums.size()); ++number)
        {
            int current = number;
            int size = 0;
            while (visited[current] == 0)
            {
                ++size;
                visited[current] = 1;
                current = nums[current];
            }
            maxSize = std::max(maxSize, size);
        }
        return maxSize;
    }
};

}

namespace ArrayNestingTask
{

TEST(ArrayNestingTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.arrayNesting({5, 4, 0, 3, 1, 6, 2}));
}

TEST(ArrayNestingTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.arrayNesting({0, 1, 2, 4, 3}));
}

}