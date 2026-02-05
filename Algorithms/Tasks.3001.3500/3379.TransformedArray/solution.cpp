#include <cstdlib>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> constructTransformedArray(std::vector<int> const &nums) const
    {
        std::vector<int> result(nums.size(), 0);
        for (size_t index = 0; index < nums.size(); ++index)
        {
            int current = nums[index];
            if (current > 0)
                result[index] = nums[(index + current) % nums.size()];
            if (current < 0)
            {
                size_t rest = std::abs(current) % nums.size();
                result[index] = nums[(nums.size() + index - rest) % nums.size()];
            }
            if (current == 0)
                result[index] = nums[index];
        }
        return result;
    }
};

}

namespace TransformedArrayTask
{

TEST(TransformedArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({1, 1, 1, 3}), solution.constructTransformedArray({3, -2, 1, 1}));
    ASSERT_EQ(std::vector<int>({-1, -1, 4}), solution.constructTransformedArray({-1, 4, -1}));
}

}