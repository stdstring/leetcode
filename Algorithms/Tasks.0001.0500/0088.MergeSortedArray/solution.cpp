#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    void merge(std::vector<int>& nums1, int m, std::vector<int> const &nums2, int n)
    {
        const size_t size1 = m;
        const size_t size2 = n;
        std::queue<int> nums1Queue;
        size_t index2 = 0;
        // merge from nums1, nums2 and nums1Queue into [0, m - 1] range
        for (size_t index1 = 0; index1 < size1; ++index1)
        {
            if (index2 < size2 && nums2[index2] < nums1[index1] && (nums1Queue.empty() || nums2[index2] < nums1Queue.front()))
            {
                nums1Queue.push(nums1[index1]);
                nums1[index1] = nums2[index2++];
            }
            else if (!nums1Queue.empty())
            {
                nums1Queue.push(nums1[index1]);
                nums1[index1] = nums1Queue.front();
                nums1Queue.pop();
            }
        }
        // merge from nums2 and nums1Queue into [m, m + n - 1] range
        for (size_t index1 = m; index1 < size1 + size2; ++index1)
        {
            if (nums1Queue.empty() || (index2 < size2 && nums2[index2] < nums1Queue.front()))
                nums1[index1] = nums2[index2++];
            else
            {
                nums1[index1] = nums1Queue.front();
                nums1Queue.pop();
            }
        }
    }
};

}

namespace
{

void checkMerge(std::vector<int> &&nums1, int m, std::vector<int> const &nums2, int n, std::vector<int> const &expectedResult)
{
    std::vector<int> data(nums1);
    Solution solution;
    solution.merge(data, m, nums2, n);
    ASSERT_EQ(expectedResult, data);
}

}

namespace MergeSortedArrayTask
{

TEST(MergeSortedArrayTaskTests, Examples)
{
    checkMerge({1, 2, 3, 0, 0, 0}, 3, {2, 5, 6}, 3, {1, 2, 2, 3, 5, 6});
}

TEST(MergeSortedArrayTaskTests, FromWrongAnswers)
{
    checkMerge({1}, 1, {}, 0, {1});
    checkMerge({2, 0}, 1, {1}, 1, {1, 2});
    checkMerge({1, 2, 4, 5, 6, 0}, 5, {3}, 1, {1, 2, 3, 4, 5, 6});
}

}