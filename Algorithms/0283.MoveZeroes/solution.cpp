#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    void moveZeroes(std::vector<int> &nums)
    {
        size_t zeroCount = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (nums[index] == 0)
                ++zeroCount;
            else
                nums[index - zeroCount] = nums[index];
        }
        if (zeroCount == nums.size())
            return;
        for (size_t index = nums.size() - zeroCount; index < nums.size(); ++index)
            nums[index] = 0;
    }
};

}

namespace MoveZeroesTask
{

TEST(MoveZeroesTaskTests, Examples)
{
    Solution solution;
    std::vector<int> nums({0, 1, 0, 3, 12});
    solution.moveZeroes(nums);
    ASSERT_EQ(std::vector<int>({1, 3, 12, 0, 0}), nums);
}

}