#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

struct CellData
{
    CellData() : isMine(false), topOnesCount(0), leftOnesCount(0), rightOnesCount(0), bottomOnesCount(0)
    {
    }

    bool isMine;
    size_t topOnesCount;
    size_t leftOnesCount;
    size_t rightOnesCount;
    size_t bottomOnesCount;

    size_t getMinOnesCount() const
    {
        return std::min(topOnesCount, std::min(leftOnesCount, std::min(rightOnesCount, bottomOnesCount)));
    }
};

class Solution
{
public:
    int orderOfLargestPlusSign(int n, std::vector<std::vector<int>> const &mines) const
    {
        const size_t gridSize = n;
        if (gridSize <= 2)
            return mines.size() < gridSize * gridSize ? 1 : 0;
        if (mines.size() == gridSize * gridSize)
            return 0;
        std::vector<std::vector<CellData>> cellsData(gridSize, std::vector<CellData>(gridSize));
        for (std::vector<int> const& mine : mines)
            cellsData[mine[0]][mine[1]].isMine = true;
        for (size_t row = 1; row < gridSize - 1; ++row)
        {
            for (size_t column = 1; column < gridSize - 1; ++column)
            {
                cellsData[row][column].topOnesCount = cellsData[row - 1][column].isMine ? 0 : cellsData[row - 1][column].topOnesCount + 1;
                cellsData[row][column].leftOnesCount = cellsData[row][column - 1].isMine ? 0 : cellsData[row][column - 1].leftOnesCount + 1;
            }
        }
        size_t plusSignOrder = 1;
        for (size_t row = gridSize - 2; row > 0; --row)
        {
            for (size_t column = gridSize - 2; column > 0; --column)
            {
                cellsData[row][column].bottomOnesCount = cellsData[row + 1][column].isMine ? 0 : cellsData[row + 1][column].bottomOnesCount + 1;
                cellsData[row][column].rightOnesCount = cellsData[row][column + 1].isMine ? 0 : cellsData[row][column + 1].rightOnesCount + 1;
                if (!cellsData[row][column].isMine)
                    plusSignOrder = std::max(plusSignOrder, 1 + cellsData[row][column].getMinOnesCount());
            }
        }
        return static_cast<int>(plusSignOrder);
    }
};

}

namespace LargestPlusSignTask
{

TEST(LargestPlusSignTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.orderOfLargestPlusSign(5, {{4, 2}}));
    ASSERT_EQ(0, solution.orderOfLargestPlusSign(1, {{0, 0}}));
}

TEST(LargestPlusSignTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(1, solution.orderOfLargestPlusSign(2, {{0, 0}, {0, 1}, {1, 0}}));
    ASSERT_EQ(1, solution.orderOfLargestPlusSign(5, {{0, 0}, {0, 3}, {1, 1}, {1, 4}, {2, 3}, {3, 0}, {4, 2}}));
}

}
