#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int rob(std::vector<int> const &nums) const
    {
        if (nums.size() == 1)
            return nums[0];
        return std::max(rob(nums, 0, nums.size() - 2), rob(nums, 1, nums.size() - 1));
    }

private:
    int rob(std::vector<int> const &nums, size_t fromIndex, size_t toIndex) const
    {
        std::vector<int> result;
        result.push_back(nums[fromIndex]);
        for (size_t index = fromIndex + 1; index <= toIndex; ++index)
            result.push_back(std::max(result.back(), (result.size() > 1 ? result[result.size() - 2] : 0) + nums[index]));
        return result.back();
    }
};

}

namespace HouseRobberIITask
{

TEST(HouseRobberIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.rob({2, 3, 2}));
    ASSERT_EQ(4, solution.rob({1, 2, 3, 1}));
    ASSERT_EQ(0, solution.rob({0}));
}

TEST(HouseRobberIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(1, solution.rob({1}));
    ASSERT_EQ(3, solution.rob({1, 2, 1, 1}));
    ASSERT_EQ(16, solution.rob({1, 2, 3, 4, 5, 1, 2, 3, 4, 5}));
}

}