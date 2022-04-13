#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int triangularSum(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        for (size_t size = numbers.size(); size > 1; --size)
        {
            for (size_t index = 1; index < size; ++index)
                numbers[index - 1] = (numbers[index - 1] + numbers[index]) % 10;
        }
        return numbers.front();
    }
};

}

namespace FindTriangularSumOfArrayTask
{

TEST(FindTriangularSumOfArrayTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(8, solution.triangularSum({1, 2, 3, 4, 5}));
    ASSERT_EQ(5, solution.triangularSum({5}));
}

}