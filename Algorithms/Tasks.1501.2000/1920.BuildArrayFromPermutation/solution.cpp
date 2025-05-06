#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> buildArray(std::vector<int> const &nums) const
    {
        std::vector<int> result(nums.size());
        for (size_t index = 0; index < nums.size(); ++index)
            result[index] = nums[nums[index]];
        return result;
    }
};

}

namespace BuildArrayFromPermutationTask
{

TEST(BuildArrayFromPermutationTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 1, 2, 4, 5, 3}), solution.buildArray({0, 2, 1, 5, 3, 4}));
    ASSERT_EQ(std::vector<int>({4, 5, 0, 1, 2, 3}), solution.buildArray({5, 0, 1, 2, 3, 4}));
}

}