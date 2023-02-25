#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int firstMissingPositive(std::vector<int> &nums)
    {
        int minValue = 0;
        int maxValue = 0;
        int count = 0;
        int currentIndex = 0;
        for (size_t index = 0; index < nums.size(); ++index)
        {
            if (nums[index] > 0)
            {
                ++count;
                nums[currentIndex++] = nums[index];
                minValue = (minValue == 0) || (nums[index] < minValue) ? nums[index] : minValue;
                maxValue = (maxValue == 0) || (nums[index] > maxValue) ? nums[index] : maxValue;
            }
        }
        if (minValue > 1)
            return 1;
        for (int index = 0; index < count; ++index)
        {
            const int refIndex = abs(nums[index]) - minValue;
            if ((refIndex < count) && (nums[refIndex] > 0))
                nums[refIndex] = -nums[refIndex];
        }
        for (int index = 0; index < count; ++index)
        {
            if (nums[index] > 0)
                return minValue + index;
        }
        return maxValue + 1;
    }
};

}

namespace FirstMissingPositiveTask
{

TEST(FirstMissingPositiveTaskTests, Examples)
{
    Solution solution;
    std::vector<int> data1({1, 2, 0});
    ASSERT_EQ(3, solution.firstMissingPositive(data1));
    std::vector<int> data2({3, 4, -1, 1});
    ASSERT_EQ(2, solution.firstMissingPositive(data2));
    std::vector<int> data3({7, 8, 9, 11, 12});
    ASSERT_EQ(1, solution.firstMissingPositive(data3));
}

}