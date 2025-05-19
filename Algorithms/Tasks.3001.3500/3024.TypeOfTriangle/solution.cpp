#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::string triangleType(std::vector<int> const &nums) const
    {
        const int a = nums[0];
        const int b = nums[1];
        const int c = nums[2];
        if (((a + b) <= c) || ((a + c) <= b) || ((b + c) <= a))
            return "none";
        if ((a == b) && (b == c))
            return "equilateral";
        if ((a == b) || (a == c) || (b == c))
            return "isosceles";
        return "scalene";
    }
};

}

namespace TypeOfTriangleTask
{

TEST(TypeOfTriangleTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ("equilateral", solution.triangleType({3, 3, 3}));
    ASSERT_EQ("scalene", solution.triangleType({3, 4, 5}));
}

}