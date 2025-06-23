#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumDifference(std::vector<int> const &nums) const
    {
        int result = -1;
        int minValue = INT_MAX;
        for (int number : nums)
        {
            if (minValue < number)
            {
                const int delta = number - minValue;
                result = std::max(result, delta);
            }
            minValue = std::min(minValue, number);
        }
        return result;
    }
};

}

namespace MaxDiffBetweenIncreasingElementsTask
{

TEST(MaxDiffBetweenIncreasingElementsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.maximumDifference({7, 1, 5, 4}));
    ASSERT_EQ(-1, solution.maximumDifference({9, 4, 3, 2}));
    ASSERT_EQ(9, solution.maximumDifference({1, 5, 2, 10}));
}

}