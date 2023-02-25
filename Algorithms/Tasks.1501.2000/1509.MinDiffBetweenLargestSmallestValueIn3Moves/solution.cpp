#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int minDifference(std::vector<int> const &nums) const
    {
        if (nums.size() <= 4)
            return 0;
        std::vector<int> numbers(nums);
        std::sort(numbers.begin(), numbers.end());
        const size_t maxIndex = numbers.size() - 1;
        return std::min({numbers[maxIndex - 3] - numbers[0], numbers[maxIndex - 2] - numbers[1], numbers[maxIndex - 1] - numbers[2], numbers[maxIndex] - numbers[3]});
    }
};

}

namespace MinDiffBetweenLargestSmallestValueIn3MovesTask
{

TEST(MinDiffBetweenLargestSmallestValueIn3MovesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(0, solution.minDifference({5, 3, 2, 4}));
    ASSERT_EQ(1, solution.minDifference({1, 5, 0, 10, 14}));
    ASSERT_EQ(2, solution.minDifference({6, 6, 0, 1, 1, 4, 6}));
    ASSERT_EQ(1, solution.minDifference({1, 5, 6, 14, 15}));
}

}