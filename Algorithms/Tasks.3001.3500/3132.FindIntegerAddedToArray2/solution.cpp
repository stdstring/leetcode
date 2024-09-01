#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumAddedInteger(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        std::vector<int> sortedNums1(nums1);
        std::ranges::sort(sortedNums1);
        std::vector<int> sortedNums2(nums2);
        std::ranges::sort(sortedNums2);
        int minX = INT_MAX;
        for (size_t deleted1 = 0; deleted1 < sortedNums1.size(); ++deleted1)
        {
            for (size_t deleted2 = deleted1 + 1; deleted2 < sortedNums1.size(); ++deleted2)
                minX = calcMinXValue(sortedNums1, sortedNums2, deleted1, deleted2, minX);
        }
        return minX;
    }

private:
    [[nodiscard]] int calcMinXValue(std::vector<int> const &nums1, std::vector<int> const &nums2, size_t deleted1, size_t deleted2, int currentMinX) const
    {
        int min1Value = (deleted1 == 0 ? (deleted2 == 1 ? nums1[2] : nums1[1]) : nums1[0]);
        int minX = nums2[0] - min1Value;
        if (currentMinX <= minX)
            return currentMinX;
        for (size_t index1 = 0, index2 = 0; (index1 < nums1.size()) && (index2 < nums2.size());)
        {
            if ((index1 != deleted1) && (index1 != deleted2))
            {
                if ((nums1[index1] + minX) != nums2[index2])
                    return INT_MAX;
                ++index2;
            }
            ++index1;
        }
        return minX;
    }
};

}

namespace FindIntegerAddedToArray2Task
{

TEST(FindIntegerAddedToArray2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(-2, solution.minimumAddedInteger({4, 20, 16, 12, 8}, {14, 18, 10}));
    ASSERT_EQ(2, solution.minimumAddedInteger({3, 5, 5, 3}, {7, 7}));
}

}