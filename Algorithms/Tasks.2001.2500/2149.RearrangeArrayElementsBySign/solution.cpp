#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> rearrangeArray(std::vector<int> const &nums) const
    {
        std::vector<int> result(nums.size(), 0);
        size_t positiveIndex = nums.size();
        size_t negativeIndex = nums.size();
        for (size_t index = 0; index < nums.size(); index += 2)
        {
            // next positive number
            positiveIndex = (positiveIndex == nums.size() ? 0 : positiveIndex + 1);
            while (nums[positiveIndex] < 0)
                ++positiveIndex;
            result[index] = nums[positiveIndex];
            // next negative number
            negativeIndex = (negativeIndex == nums.size() ? 0 : negativeIndex + 1);
            while (nums[negativeIndex] > 0)
                ++negativeIndex;
            result[index + 1] = nums[negativeIndex];
        }
        return result;
    }
};

}

namespace RearrangeArrayElementsBySignTask
{

TEST(RearrangeArrayElementsBySignTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({3, -2, 1, -5, 2, -4}), solution.rearrangeArray({3, 1, -2, -5, 2, -4}));
    ASSERT_EQ(std::vector<int>({1, -1}), solution.rearrangeArray({-1, 1}));
}

}