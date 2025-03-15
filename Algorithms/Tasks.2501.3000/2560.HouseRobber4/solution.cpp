#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minCapability(std::vector<int> const &nums, int k) const
    {
        auto [min, max] = std::ranges::minmax(nums);
        int left = min;
        int right = max;
        while (left < right)
        {
            const int middle = (left + right) / 2;
            int robCount = 0;
            for (size_t index = 0; index < nums.size();)
            {
                if (nums[index] <= middle)
                {
                    ++robCount;
                    index += 2;
                }
                else
                    ++index;
            }
            if (robCount >= k)
                right = middle;
            else
                left = middle + 1;
        }
        return left;
    }

};

}

namespace HouseRobber4Task
{

TEST(HouseRobber4TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.minCapability({2, 3, 5, 9}, 2));
    ASSERT_EQ(2, solution.minCapability({2, 7, 9, 3, 1}, 2));
}

}