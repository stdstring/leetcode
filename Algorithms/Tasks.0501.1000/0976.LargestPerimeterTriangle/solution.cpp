#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int largestPerimeter(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end(), std::greater<>());
        for (size_t index = 0; index <= numbers.size() - 3; ++index)
        {
            if (canFormTriangle(numbers[index], numbers[index + 1], numbers[index + 2]))
                return numbers[index] + numbers[index + 1] + numbers[index + 2];
        }
        return 0;
    }

private:
    bool canFormTriangle(int sideA, int sideB, int sideC) const
    {
        return (sideA < (sideB + sideC)) && (sideB < (sideC + sideA)) && (sideC < (sideA + sideB));
    }
};

}

namespace LargestPerimeterTriangleTask
{

TEST(LargestPerimeterTriangleTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.largestPerimeter({2, 1, 2}));
    ASSERT_EQ(0, solution.largestPerimeter({1, 2, 1}));
    ASSERT_EQ(10, solution.largestPerimeter({3, 2, 3, 4}));
    ASSERT_EQ(8, solution.largestPerimeter({3, 6, 2, 3}));
}

}