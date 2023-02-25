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
        std::vector<int> result;
        if (!nums.empty())
            result.push_back(nums[0]);
        if (nums.size() > 1)
            result.push_back(std::max(nums[0], nums[1]));
        for (size_t index = 2; index < nums.size(); ++index)
            result.push_back(std::max(result[index - 1], result[index - 2] + nums[index]));
        return result.empty() ? 0 : result.back();
    }
};

}

namespace HouseRobberTask
{

TEST(HouseRobberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.rob({1, 2, 3, 1}));
    ASSERT_EQ(12, solution.rob({2, 7, 9, 3, 1}));
}

}