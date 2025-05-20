#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isZeroArray(std::vector<int> const &nums, std::vector<std::vector<int>> const &queries) const
    {
        std::vector<int> decrements(nums.size() + 1, 0);
        for (std::vector<int> const &query : queries)
        {
            ++decrements[query[0]];
            --decrements[query[1] + 1];
        }
        int currentDecrement = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            currentDecrement += decrements[index];
            if (nums[index] > currentDecrement)
                return false;
        }
        return true;
    }
};

}

namespace ZeroArrayTransformation1Task
{

TEST(ZeroArrayTransformation1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.isZeroArray({1, 0, 1}, {{0, 2}}));
    ASSERT_EQ(false, solution.isZeroArray({4, 3, 2, 1}, {{1, 3}, {0, 2}}));
}

}