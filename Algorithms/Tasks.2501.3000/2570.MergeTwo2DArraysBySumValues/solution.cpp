#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> mergeArrays(std::vector<std::vector<int>> const &nums1,
                                                            std::vector<std::vector<int>> const &nums2) const
    {
        std::vector<std::vector<int>> result;
        size_t index1 = 0;
        size_t index2 = 0;
        while ((index1 < nums1.size()) && (index2 < nums2.size()))
        {
            if (nums1[index1][0] < nums2[index2][0])
                result.push_back(nums1[index1++]);
            else if (nums2[index2][0] < nums1[index1][0])
                result.push_back(nums2[index2++]);
            else
            {
                result.push_back({nums1[index1][0], nums1[index1][1] + nums2[index2][1]});
                ++index1;
                ++index2;
            }
        }
        for (;(index1 < nums1.size()); ++index1)
            result.push_back(nums1[index1]);
        for (;(index2 < nums2.size()); ++index2)
            result.push_back(nums2[index2]);
        return result;
    }
};

}

namespace MergeTwo2DArraysBySumValuesTask
{

TEST(MergeTwo2DArraysBySumValuesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 6}, {2, 3}, {3, 2}, {4, 6}}),
              solution.mergeArrays({{1, 2}, {2, 3}, {4, 5}}, {{1, 4}, {3, 2}, {4, 1}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 3}, {2, 4}, {3, 6}, {4, 3}, {5, 5}}),
              solution.mergeArrays({{2, 4}, {3, 6}, {5, 5}}, {{1, 3}, {4, 3}}));
}

}