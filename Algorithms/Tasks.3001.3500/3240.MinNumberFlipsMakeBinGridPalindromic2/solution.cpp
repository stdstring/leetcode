#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minFlips(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        size_t flipCount = 0;
        for (size_t topRow = 0, bottomRow = rowCount - 1; topRow < bottomRow; ++topRow, --bottomRow)
        {
            for (size_t leftColumn = 0, rightColumn = columnCount - 1; leftColumn < rightColumn; ++leftColumn, --rightColumn)
            {
                int cellsSum = grid[topRow][leftColumn] + grid[topRow][rightColumn] + grid[bottomRow][leftColumn] + grid[bottomRow][rightColumn];
                flipCount += std::min(cellsSum, 4 - cellsSum);
            }
        }
        if (((rowCount % 2) == 1) && ((columnCount % 2) == 1) && (grid[rowCount / 2][columnCount / 2] == 1))
            ++flipCount;
        size_t middleOnePairs = 0;
        size_t middleFlip = 0;
        if ((rowCount % 2) == 1)
        {
            for (size_t leftColumn = 0, rightColumn = columnCount - 1; leftColumn < rightColumn; ++leftColumn, --rightColumn)
            {
                if (grid[rowCount / 2][leftColumn] != grid[rowCount / 2][rightColumn])
                    ++middleFlip;
                if ((grid[rowCount / 2][leftColumn] == 1) && (grid[rowCount / 2][rightColumn] == 1))
                    ++middleOnePairs;
            }
        }
        if ((columnCount % 2) == 1)
        {
            for (size_t topRow = 0, bottomRow = rowCount - 1; topRow < bottomRow; ++topRow, --bottomRow)
            {
                if (grid[topRow][columnCount / 2] != grid[bottomRow][columnCount / 2])
                    ++middleFlip;
                if ((grid[topRow][columnCount / 2] == 1) && (grid[bottomRow][columnCount / 2] == 1))
                    ++middleOnePairs;
            }
        }
        return static_cast<int>(flipCount + middleFlip + (((middleFlip == 0) && ((middleOnePairs % 2) != 0)) ? 2 : 0));
    }
};

}

namespace MinNumberFlipsMakeBinGridPalindromic2Task
{

TEST(MinNumberFlipsMakeBinGridPalindromic2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.minFlips({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}));
    ASSERT_EQ(2, solution.minFlips({{0, 1}, {0, 1}, {0, 0}}));
    ASSERT_EQ(2, solution.minFlips({{1}, {1}}));
}

}