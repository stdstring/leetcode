#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long largestPerimeter(std::vector<int> const &nums) const
    {
        std::vector<int> numbers(nums);
        std::ranges::sort(numbers);
        std::vector<long long> prefixSum(numbers.size(), 0);
        for (size_t index = 0; index < numbers.size(); ++index)
            prefixSum[index] = 1LL * numbers[index] + (index > 0 ? prefixSum[index - 1] : 0);
        // min 3 sides
        for (size_t index = numbers.size() - 1; index > 1; --index)
        {
            if (prefixSum[index - 1] > numbers[index])
                return prefixSum[index];
        }
        return -1;
    }
};

}

namespace FindPolygonWithLargestPerimeterTask
{

TEST(FindPolygonWithLargestPerimeterTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(15, solution.largestPerimeter({5, 5, 5}));
    ASSERT_EQ(12, solution.largestPerimeter({1, 12, 1, 2, 5, 50, 3}));
    ASSERT_EQ(-1, solution.largestPerimeter({5, 5, 50}));
}

}