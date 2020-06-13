#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int removeDuplicates(std::vector<int>& nums)
    {
        if (nums.empty())
            return 0;
        int shift = 0;
        int length = 1;
        int value = nums[0];
        int count = 1;
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if (nums[index] == value)
            {
                if (count < 2)
                {
                    ++count;
                    nums[index - shift] = value;
                    ++length;
                }
                else
                {
                    ++shift;
                }
            }
            else
            {
                value = nums[index];
                count = 1;
                nums[index - shift] = value;
                ++length;
            }
        }
        return length;
    }
};

}

namespace RemoveDuplicatesFromSortedArrayIITask
{

TEST(RemoveDuplicatesFromSortedArrayIITaskTests, Examples)
{
    Solution solution;
    std::vector<int> nums1({1, 1, 1, 2, 2, 3});
    ASSERT_EQ(5, solution.removeDuplicates(nums1));
    ASSERT_EQ(std::vector<int>({1, 1, 2, 2, 3}), std::vector<int>(nums1.cbegin(), nums1.cbegin() + 5));
    std::vector<int> nums2({0, 0, 1, 1, 1, 1, 2, 3, 3});
    ASSERT_EQ(7, solution.removeDuplicates(nums2));
    ASSERT_EQ(std::vector<int>({0, 0, 1, 1, 2, 3, 3}), std::vector<int>(nums2.cbegin(), nums2.cbegin() + 7));
}

}