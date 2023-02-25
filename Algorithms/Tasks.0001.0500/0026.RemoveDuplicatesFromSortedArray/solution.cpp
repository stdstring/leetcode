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
        int length = 1;
        int current = nums[0];
        int shift = 0;
        for (size_t index = 1; index < nums.size(); ++index)
        {
            if (current == nums[index])
                ++shift;
            else
            {
                ++length;
                current = nums[index];
                nums[index - shift] = current;
            }
        }
        return length;
    }
};

}

namespace RemoveDuplicatesFromSortedArrayTask
{

TEST(TwoSumTaskTests, Examples)
{
    Solution solution;
    std::vector<int> data1({1, 1, 2});
    ASSERT_EQ(2, solution.removeDuplicates(data1));
    ASSERT_EQ(std::vector<int>({1, 2}), std::vector<int>(data1.cbegin(), data1.cbegin() + 2));
    std::vector<int> data2({0, 0, 1, 1, 1, 2, 2, 3, 3, 4});
    ASSERT_EQ(5, solution.removeDuplicates(data2));
    ASSERT_EQ(std::vector<int>({0, 1, 2, 3, 4}), std::vector<int>(data2.cbegin(), data2.cbegin() + 5));

}

TEST(TwoSumTaskTests, FromWrongAnswers)
{
    Solution solution;
    std::vector<int> data;
    ASSERT_EQ(0, solution.removeDuplicates(data));
    ASSERT_EQ(std::vector<int>(), data);
}

}
