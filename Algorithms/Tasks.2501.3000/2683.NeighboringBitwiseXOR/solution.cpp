#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool doesValidArrayExist(std::vector<int> const &derived) const
    {
        constexpr int firstValue = 1;
        int currentValue = 1;
        for (const int derivedValue : derived)
            currentValue = currentValue ^ derivedValue;
        return currentValue == firstValue;
    }
};

}

namespace NeighboringBitwiseXORTask
{

TEST(NeighboringBitwiseXORTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.doesValidArrayExist({1, 1, 0}));
    ASSERT_EQ(true, solution.doesValidArrayExist({1, 1}));
    ASSERT_EQ(false, solution.doesValidArrayExist({1, 0}));
}

TEST(NeighboringBitwiseXORTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.doesValidArrayExist({ 1 }));
    ASSERT_EQ(true, solution.doesValidArrayExist({ 0 }));
}

}