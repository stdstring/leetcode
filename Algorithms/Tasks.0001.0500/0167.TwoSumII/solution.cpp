#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> twoSum(std::vector<int> const &numbers, int target) const
    {
        // two pointer approach
        size_t left = 0;
        size_t right = numbers.size() - 1;
        while (left != right)
        {
            const int value = numbers[left] + numbers[right];
            if (value == target)
                return {static_cast<int>(left + 1), static_cast<int>(right + 1)};
            if (value < target)
                ++left;
            else if (value > target)
                --right;
        }
        return {};
    }
};

}

namespace TwoSumIITask
{

TEST(TwoSumIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2}), solution.twoSum({2, 7, 11, 15}, 9));
}

}