#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int uniqueXorTriplets(std::vector<int> const &nums) const
    {
        const int count = static_cast<int>(nums.size());
        if (count < 3)
            return count;
        int result = 1;
        while (result <= count)
            result <<= 1;
        return result;
    }
};

}

namespace NumberUniqueXORTriplets1Task
{

TEST(NumberUniqueXORTriplets1TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.uniqueXorTriplets({1, 2}));
    ASSERT_EQ(4, solution.uniqueXorTriplets({3, 1, 2}));
}

TEST(NumberUniqueXORTriplets1TaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(8, solution.uniqueXorTriplets({1, 2, 3, 4, 5}));
    ASSERT_EQ(8, solution.uniqueXorTriplets({1, 2, 3, 4}));
    ASSERT_EQ(1, solution.uniqueXorTriplets({1}));
}

}