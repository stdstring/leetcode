#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int removeElement(std::vector<int>& nums, int val)
    {
        if (nums.empty())
            return 0;
        int length = 0;
        int shift = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (nums[index] == val)
                ++shift;
            else
            {
                ++length;
                nums[index - shift] = nums[index];
            }
        }
        return length;
    }
};

}

namespace RemoveElementTask
{

TEST(RemoveElementTaskTests, Examples)
{
    Solution solution;
    std::vector<int> data1({3, 2, 2, 3});
    ASSERT_EQ(2, solution.removeElement(data1, 3));
    ASSERT_EQ(std::vector<int>({2, 2}), std::vector<int>(data1.cbegin(), data1.cbegin() + 2));
    std::vector<int> data2({0, 1, 2, 2, 3, 0, 4, 2});
    ASSERT_EQ(5, solution.removeElement(data2, 2));
    ASSERT_EQ(std::vector<int>({0, 1, 3, 0, 4}), std::vector<int>(data2.cbegin(), data2.cbegin() + 5));

}

}