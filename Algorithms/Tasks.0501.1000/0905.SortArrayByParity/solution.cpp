#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> sortArrayByParity(std::vector<int> const &nums) const
    {
        std::vector<int> result(nums.size(), 0);
        size_t left = 0;
        size_t right = result.size() - 1;
        for (const int num : nums)
        {
            if (num % 2 == 0)
                result[left++] = num;
            else
                result[right--] = num;
        }
        return result;
    }
};

}

namespace SortArrayByParityTask
{

TEST(SortArrayByParityTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({2, 4, 1, 3}), solution.sortArrayByParity({3, 1, 2, 4}));
    ASSERT_EQ(std::vector<int>({0}), solution.sortArrayByParity({0}));
}

}