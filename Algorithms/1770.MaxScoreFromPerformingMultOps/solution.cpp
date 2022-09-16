#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumScore(std::vector<int> const &nums, std::vector<int> const &multipliers) const
    {
        std::vector<int> currentRow(multipliers.size() + 1, INT_MIN);
        currentRow[0] = nums.back() * multipliers[0];
        currentRow[1] = nums[0] * multipliers[0];
        for (size_t multiplierIndex = 1; multiplierIndex < multipliers.size(); ++multiplierIndex)
        {
            std::vector<int> nextRow(multipliers.size() + 1, INT_MIN);
            const int multiplier = multipliers[multiplierIndex];
            for (size_t usedNumbersFromLeft = 0; usedNumbersFromLeft <= multiplierIndex; ++usedNumbersFromLeft)
            {
                const size_t usedNumbersFromRight = multiplierIndex - usedNumbersFromLeft;
                if (usedNumbersFromRight < nums.size())
                    nextRow[usedNumbersFromLeft] = std::max(nextRow[usedNumbersFromLeft],
                                                            currentRow[usedNumbersFromLeft] + multiplier * nums[nums.size() - 1 - usedNumbersFromRight]);
                nextRow[usedNumbersFromLeft + 1] = std::max(nextRow[usedNumbersFromLeft + 1],
                                                            currentRow[usedNumbersFromLeft] + multiplier * nums[usedNumbersFromLeft]);
            }
            std::swap(currentRow, nextRow);
        }
        return *std::max_element(currentRow.cbegin(), currentRow.cend());
    }
};

}

namespace MaxScoreFromPerformingMultOpsTask
{

TEST(MaxScoreFromPerformingMultOpsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(14, solution.maximumScore({1, 2, 3}, {3, 2, 1}));
    ASSERT_EQ(102, solution.maximumScore({-5, -3, -3, -2, 7, 1}, {-10, -5, 3, 4, 6}));
}

}