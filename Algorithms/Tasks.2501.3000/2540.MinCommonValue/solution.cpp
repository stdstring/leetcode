#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int getCommon(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        for (size_t index1 = 0, index2 = 0; (index1 < nums1.size()) && (index2 < nums2.size());)
        {
            if (nums1[index1] == nums2[index2])
                return nums1[index1];
            ++(nums1[index1] < nums2[index2] ? index1 : index2);
        }
        return -1;
    }
};

}

namespace MinCommonValueTask
{

TEST(MinCommonValueTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.getCommon({1, 2, 3}, {2, 4}));
    ASSERT_EQ(2, solution.getCommon({1, 2, 3, 6}, {2, 3, 4, 5}));
}

}