#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numRollsToTarget(int n, int k, int target) const
    {
        constexpr size_t modValue = 1000000007;
        const size_t rowSize = target + 1;
        std::vector<size_t> currentRow(rowSize, 0);
        currentRow[0] = 1;
        for (int dice = 0; dice < n; ++dice)
        {
            std::vector<size_t> nextRow(rowSize, 0);
            for (int face = 1; face <= k; ++face)
            {
                for (size_t index = dice, nextIndex = index + face; (nextIndex < rowSize) && (currentRow[index] != 0); ++index, ++nextIndex)
                    nextRow[nextIndex] = (nextRow[nextIndex] + currentRow[index]) % modValue;
            }
            std::swap(currentRow, nextRow);
        }
        return static_cast<int>(currentRow.back());
    }
};

}

namespace NumberOfDiceRollsWithTargetSumTask
{

TEST(NumberOfDiceRollsWithTargetSumTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.numRollsToTarget(1, 6, 3));
    ASSERT_EQ(6, solution.numRollsToTarget(2, 6, 7));
    ASSERT_EQ(222616187, solution.numRollsToTarget(30, 30, 500));
}

}