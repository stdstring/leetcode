#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<std::string>> solveNQueens(int n) const
    {
        const std::vector<int> boardMask(n, 0);
        std::vector<std::string> board(n, std::string(n, '.'));
        std::vector<std::vector<std::string>> dest;
        generateQueens(n, 0, boardMask, (1 << n) - 1, board, dest);
        return dest;
    }

private:
    void generateQueens(int n, int row, std::vector<int> const &boardMask, int busyRowMask, std::vector<std::string> &board, std::vector<std::vector<std::string>> &dest) const
    {
        if (row == n)
        {
            dest.push_back(board);
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
                board[row][column] = 'Q';
                generateQueens(n, row + 1, newBoardMask, busyRowMask, board, dest);
                board[row][column] = '.';
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

namespace NQueensTask
{

TEST(NQueensTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<std::string>>({{".Q..", "...Q", "Q...", "..Q."}, {"..Q.", "Q...", "...Q", ".Q.."}}), solution.solveNQueens(4));
}

}