#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxUncrossedLines(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        // Longest common subsequence problem
        std::vector<int> dpRow(nums2.size(), 0);
        for (const int number1 : nums1)
        {
            std::vector<int> dpNextRow(nums2.size(), 0);
            for (size_t index2 = 0; index2 < nums2.size(); ++index2)
            {
                if (number1 == nums2[index2])
                    dpNextRow[index2] = (index2 > 0 ? dpRow[index2 - 1] : 0) + 1;
                else
                    dpNextRow[index2] = std::max(dpRow[index2], index2 > 0 ? dpNextRow[index2 - 1] : 0);
            }
            std::swap(dpRow, dpNextRow);
        }
        return dpRow.back();
    }
};

}

namespace UncrossedLinesTask
{

TEST(UncrossedLinesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxUncrossedLines({1, 4, 2}, {1, 2, 4}));
    ASSERT_EQ(3, solution.maxUncrossedLines({2, 5, 1, 2, 5}, {10, 5, 2, 1, 5, 2}));
    ASSERT_EQ(2, solution.maxUncrossedLines({1, 3, 7, 1, 7, 5}, {1, 9, 2, 5, 1}));
}

}