#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxDistance(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        size_t result = 0;
        for (size_t index1 = 0, index2 = 0; (index1 < nums1.size()) && (index2 < nums2.size());)
        {
            if ((index1 <= index2) && (nums1[index1] <= nums2[index2]))
                result = std::max(result, index2 - index1);
            if (nums1[index1] <= nums2[index2])
                ++index2;
            else
                ++index1;
        }
        return static_cast<int>(result);
    }
};

}

namespace MaxDistanceBetweenPairOfValuesTask
{

TEST(MaxDistanceBetweenPairOfValuesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxDistance({55, 30, 5, 4, 2}, {100, 20, 10, 10, 5}));
    ASSERT_EQ(1, solution.maxDistance({2, 2, 2}, {10, 10, 1}));
    ASSERT_EQ(2, solution.maxDistance({30, 29, 19, 5}, {25, 25, 25, 25, 25}));
}

}