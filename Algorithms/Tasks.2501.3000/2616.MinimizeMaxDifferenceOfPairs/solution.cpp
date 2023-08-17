#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimizeMax(std::vector<int> const &nums, int p) const
    {
        if (p == 0)
            return 0;
        std::vector<int> sortedNumbers(nums);
        std::ranges::sort(sortedNumbers);
        int left = 0;
        int right = sortedNumbers.back() - sortedNumbers.front();
        while (left < right)
        {
            const int middle = (left + right) / 2;
            if (hasEnoughPairs(sortedNumbers, p, middle))
                right = middle;
            else
                left = middle + 1;
        }
        return left;
    }

private:
    [[nodiscard]] bool hasEnoughPairs(std::vector<int> const &sortedNumbers, size_t expectedPairs, int pairValue) const
    {
        size_t pairCount = 0;
        for (size_t index = 0; index < sortedNumbers.size() - 1; ++index)
        {
            if ((sortedNumbers[index + 1] - sortedNumbers[index]) <= pairValue)
            {
                ++pairCount;
                ++index;
            }
            if (pairCount == expectedPairs)
                return true;
        }
        return false;
    }
};

}

namespace MinimizeMaxDifferenceOfPairsTask
{

TEST(MinimizeMaxDifferenceOfPairsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minimizeMax({10, 1, 2, 7, 1, 3}, 2));
    ASSERT_EQ(0, solution.minimizeMax({4, 2, 1, 2}, 1));
}

TEST(MinimizeMaxDifferenceOfPairsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.minimizeMax({2, 6, 2, 4, 2, 2, 0, 2}, 4));
}

}