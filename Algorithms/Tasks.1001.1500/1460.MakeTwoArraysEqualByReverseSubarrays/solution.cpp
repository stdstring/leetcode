#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canBeEqual(std::vector<int> const &target, std::vector<int> const &arr) const
    {
        std::vector<int> arr1(target);
        std::ranges::sort(arr1);
        std::vector<int> arr2(arr);
        std::ranges::sort(arr2);
        for (size_t index = 0; index < arr1.size(); ++index)
        {
            if (arr1[index] != arr2[index])
                return false;
        }
        return true;
    }
};

}

namespace MakeTwoArraysEqualByReverseSubarraysTask
{

TEST(MakeTwoArraysEqualByReverseSubarraysTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canBeEqual({1, 2, 3, 4}, {2, 4, 1, 3}));
    ASSERT_EQ(true, solution.canBeEqual({7}, {7}));
    ASSERT_EQ(false, solution.canBeEqual({3, 7, 9}, {3, 7, 11}));
}

}