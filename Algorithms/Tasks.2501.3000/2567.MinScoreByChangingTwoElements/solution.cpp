#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimizeSum(std::vector<int> const &nums) const
    {
        if (nums.size() == 3)
            return 0;
        std::vector<int> sortedNumbers(nums);
        std::sort(sortedNumbers.begin(), sortedNumbers.end());
        return std::min(sortedNumbers[sortedNumbers.size() - 1] - sortedNumbers[2],
                        std::min(sortedNumbers[sortedNumbers.size() - 2] - sortedNumbers[1], sortedNumbers[sortedNumbers.size() - 3] - sortedNumbers[0]));
    }
};

}

namespace MinScoreByChangingTwoElementsTask
{

TEST(MinScoreByChangingTwoElementsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(0, solution.minimizeSum({1, 4, 3}));
    ASSERT_EQ(3, solution.minimizeSum({1, 4, 7, 8, 5}));
}

TEST(MinScoreByChangingTwoElementsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(14, solution.minimizeSum({31, 25, 72, 79, 74, 65}));
}

}