#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool uniformArray(std::vector<int> const &nums1) const
    {
        // when all numbers in nums1 is even, then all is trivial
        // when all numbers in nums1 is odd, then all is trivial
        // when nums1 contains odd and even, then we can easily transform all even numbers into odd ones
        return true;
    }
};

}

namespace ConstructUniformParityArray1Task
{

TEST(ConstructUniformParityArray1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.uniformArray({2, 3}));
    ASSERT_EQ(true, solution.uniformArray({4, 6}));
}

}