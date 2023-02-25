#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int totalNQueens(int n) const
    {
        int count = 0;
        const std::vector<int> boardMask(n, 0);
        calcQueensCount(n, 0, boardMask, (1 << n) - 1, count);
        return count;
    }

private:
    void calcQueensCount(int n, int row, std::vector<int> const &boardMask, int busyRowMask, int &count) const
    {
        if (row == n)
        {
            ++count;
            return;
        }
        if (boardMask[row] == busyRowMask)
            return;
        for (int column = 0; column < n; ++column)
        {
            if ((boardMask[row] & (1 << column)) == 0)
            {
                std::vector<int> newBoardMask(boardMask);
                strikeOutQueenAttackedCells(n, newBoardMask, row, column);
                calcQueensCount(n, row + 1, newBoardMask, busyRowMask, count);
            }
        }
    }

    void strikeOutQueenAttackedCells(int n, std::vector<int> &boardMask, int queenRow, int queenColumn) const
    {
        boardMask[queenRow] |= (1 << queenColumn);
        int leftDiagonal = queenColumn;
        int rightDiagonal = queenColumn;
        for (int row = queenRow + 1; row < n; ++row)
        {
            --leftDiagonal;
            ++rightDiagonal;
            boardMask[row] |= (1 << queenColumn);
            if (leftDiagonal >= 0)
                boardMask[row] |= (1 << leftDiagonal);
            if (rightDiagonal < n)
                boardMask[row] |= (1 << rightDiagonal);
        }
    }
};

}

namespace NQueensIITask
{

TEST(NQueensIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.totalNQueens(4));
}

TEST(NQueensIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(10, solution.totalNQueens(5));
}

}