#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> sortArrayByParityII(std::vector<int> const &nums) const
    {
        std::vector<int> result(nums.size());
        size_t evenIndex = 0;
        size_t oddIndex = 1;
        for (int number : nums)
        {
            if (number % 2 == 0)
            {
                result[evenIndex] = number;
                evenIndex += 2;
            }
            else
            {
                result[oddIndex] = number;
                oddIndex += 2;
            }
        }
        return result;
    }
};

}

namespace SortArrayByParityIITask
{

TEST(SortArrayByParityIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({4, 5, 2, 7}), solution.sortArrayByParityII({4, 2, 5, 7}));
    ASSERT_EQ(std::vector<int>({2, 3}), solution.sortArrayByParityII({2, 3}));
}

}