#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] double findMedianSortedArrays(std::vector<int> const &nums1, std::vector<int> const &nums2) const
    {
        const size_t totalSize = nums1.size() + nums2.size();
        const size_t medianIndexLeft = totalSize / 2 - (totalSize % 2 == 0 ? 1 : 0);
        const size_t medianIndexRight = medianIndexLeft + (totalSize % 2 == 0 ? 1 : 0);
        if (nums1.empty())
            return findMedianArray(nums2, medianIndexLeft, medianIndexRight);
        if (nums2.empty())
            return findMedianArray(nums1, medianIndexLeft, medianIndexRight);
        if (nums1.back() <= nums2.front())
            return findMedianDisjointArrays(nums1, nums2, medianIndexLeft, medianIndexRight);
        if (nums2.back() <= nums1.front())
            return findMedianDisjointArrays(nums2, nums1, medianIndexLeft, medianIndexRight);
        size_t totalIndex = 0;
        size_t index1 = 0;
        size_t index2 = 0;
        for (;totalIndex < medianIndexLeft && index1 < nums1.size() && index2 < nums2.size(); ++totalIndex)
            ++(nums1[index1] < nums2[index2] ? index1 : index2);
        if (index1 == nums1.size())
            return findMedianArray(nums2, index2 + (medianIndexLeft - totalIndex), index2 + (medianIndexRight - totalIndex));
        if (index2 == nums2.size())
            return findMedianArray(nums1, index1 + (medianIndexLeft - totalIndex), index1 + (medianIndexRight - totalIndex));
        const double leftValue = nums1[index1] < nums2[index2] ? nums1[index1] : nums2[index2];
        if (medianIndexLeft < medianIndexRight)
            ++(nums1[index1] < nums2[index2] ? index1 : index2);
        const double rightValue = (index2 == nums2.size()) || (index1 < nums1.size() && index2 < nums2.size() && nums1[index1] < nums2[index2]) ? nums1[index1] : nums2[index2];
        return (leftValue + rightValue) / 2;
    }

private:
    [[nodiscard]] double findMedianDisjointArrays(std::vector<int> const &leftNumbers, std::vector<int> const &rightNumbers, size_t medianIndexLeft, size_t medianIndexRight) const
    {
        const double leftValue = medianIndexLeft < leftNumbers.size() ? leftNumbers[medianIndexLeft] : rightNumbers[medianIndexLeft - leftNumbers.size()];
        const double rightValue = medianIndexRight < leftNumbers.size() ? leftNumbers[medianIndexRight] : rightNumbers[medianIndexRight - leftNumbers.size()];
        return (leftValue + rightValue) / 2;
    }

    [[nodiscard]] double findMedianArray(std::vector<int> const &numbers, size_t medianIndexLeft, size_t medianIndexRight) const
    {
        const double leftValue = numbers[medianIndexLeft];
        const double rightValue = numbers[medianIndexRight];
        return (leftValue + rightValue) / 2;
    }
};

}

namespace MedianOfTwoSortedArraysTask
{

TEST(MedianOfTwoSortedArraysTaskTests, Examples)
{
    const Solution solution;
    ASSERT_DOUBLE_EQ(2.0, solution.findMedianSortedArrays({1, 3}, {2}));
    ASSERT_DOUBLE_EQ(2.5, solution.findMedianSortedArrays({1, 2}, {3, 4}));
}

}
