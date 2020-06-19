#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int thirdMax(std::vector<int> const &nums) const
    {
        std::vector<int> maxData;
        maxData.emplace_back(nums[0]);
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if (maxData.size() == 3 && nums[index] <= maxData.back())
                continue;
            if (maxData[0] == nums[index] || (maxData.size() > 1 && maxData[1] == nums[index])  || (maxData.size() > 2 && maxData[2] == nums[index]))
                continue;
            if (maxData.size() < 3)
                maxData.emplace_back(nums[index]);
            else
                maxData[2] = nums[index];
            if (maxData.size() == 3 && maxData[2] > maxData[1])
                std::swap(maxData[2], maxData[1]);
            if (maxData[1] > maxData[0])
                std::swap(maxData[1], maxData[0]);
        }
        return maxData.size() == 3 ? maxData.back() : maxData.front();
    }
};

}

namespace ThirdMaximumNumberTask
{

TEST(ThirdMaximumNumberTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.thirdMax({3, 2, 1}));
    ASSERT_EQ(2, solution.thirdMax({1, 2}));
    ASSERT_EQ(1, solution.thirdMax({2, 2, 3, 1}));
}

}