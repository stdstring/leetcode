#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findLength(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        size_t bestLength = 0;
        std::vector<size_t> prevDPRow(nums2.size(), 0);
        std::vector<size_t> currentDPRow(nums2.size(), 0);
        for (const int number1 : nums1)
        {
            for (size_t index2 = 0; index2 < nums2.size(); ++index2)
            {
                if (number1 != nums2[index2])
                    currentDPRow[index2] = 0;
                else
                {
                    currentDPRow[index2] = 1 + (index2 == 0 ? 0 : prevDPRow[index2 - 1]);
                    bestLength = std::max(bestLength, currentDPRow[index2]);
                }
            }
            std::swap(prevDPRow, currentDPRow);
        }
        return static_cast<int>(bestLength);
    }
};

}

namespace MaxLengthOfRepeatedSubarrayTask
{

TEST(MaxLengthOfRepeatedSubarrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.findLength({1, 2, 3, 2, 1}, {3, 2, 1, 4, 7}));
    ASSERT_EQ(5, solution.findLength({0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}));
}

}