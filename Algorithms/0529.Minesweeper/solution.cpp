#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<char>> updateBoard(std::vector<std::vector<char>> const &board, std::vector<int> const &click) const
    {
        const int row = click[0];
        const int column = click[1];
        std::vector<std::vector<char>> dest(board);
        switch (dest[row][column])
        {
            case 'M':
                dest[row][column] = 'X';
                break;
            case 'E':
                revealeCell(dest, row, column);
                break;
            default:
                /* do nothing */;
        }
        return dest;
    }

private:
    void revealeCell(std::vector<std::vector<char>> &board, int row, int column) const
    {
        if (board[row][column] != 'E')
            return;
        const int maxRow = static_cast<int>(board.size() - 1);
        const int maxColumn = static_cast<int>(board[0].size() - 1);
        const int adjacentMinesCount = calcAdjacentMinesCount(board, row, column);
        if (adjacentMinesCount > 0)
        {
            board[row][column] = '0' + adjacentMinesCount;
            return;
        }
        board[row][column] = 'B';
        if (row > 0)
        {
            if (column > 0)
                revealeCell(board, row - 1, column - 1);
            revealeCell(board, row - 1, column);
            if (column < maxColumn)
                revealeCell(board, row - 1, column + 1);
        }
        if (column > 0)
            revealeCell(board, row, column - 1);
        if (column < maxColumn)
                revealeCell(board, row, column + 1);
        if (row < maxRow)
        {
            if (column > 0)
                revealeCell(board, row + 1, column - 1);
            revealeCell(board, row + 1, column);
            if (column < maxColumn)
                revealeCell(board, row + 1, column + 1);
        }
    }

    int calcAdjacentMinesCount(std::vector<std::vector<char>> const &board, int row, int column) const
    {
        const int maxRow = static_cast<int>(board.size() - 1);
        const int maxColumn = static_cast<int>(board[0].size() - 1);
        int adjacentMinesCount = 0;
        if (row > 0)
        {
            adjacentMinesCount += (column > 0) && (board[row - 1][column - 1] == 'M') ? 1 : 0;
            adjacentMinesCount += (board[row - 1][column] == 'M') ? 1 : 0;
            adjacentMinesCount += (column < maxColumn) && (board[row - 1][column + 1] == 'M') ? 1 : 0;
        }
        adjacentMinesCount += (column > 0) && (board[row][column - 1] == 'M') ? 1 : 0;
        adjacentMinesCount += (column < maxColumn) && (board[row][column + 1] == 'M') ? 1 : 0;
        if (row < maxRow)
        {
            adjacentMinesCount += (column > 0) && (board[row + 1][column - 1] == 'M') ? 1 : 0;
            adjacentMinesCount += (board[row + 1][column] == 'M') ? 1 : 0;
            adjacentMinesCount += (column < maxColumn) && (board[row + 1][column + 1] == 'M') ? 1 : 0;
        }
        return adjacentMinesCount;
    }
};

}

namespace MinesweeperTask
{

TEST(MinesweeperTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<char>>({{'B', '1', 'E', '1', 'B'}, {'B', '1', 'M', '1', 'B'}, {'B', '1', '1', '1', 'B'}, {'B', 'B', 'B', 'B', 'B'}}),
              solution.updateBoard({{'E', 'E', 'E', 'E', 'E'}, {'E', 'E', 'M', 'E', 'E'}, {'E', 'E', 'E', 'E', 'E'}, {'E', 'E', 'E', 'E', 'E'}}, {3, 0}));
    ASSERT_EQ(std::vector<std::vector<char>>({{'B', '1', 'E', '1', 'B'}, {'B', '1', 'X', '1', 'B'}, {'B', '1', '1', '1', 'B'}, {'B', 'B', 'B', 'B', 'B'}}),
              solution.updateBoard({{'B', '1', 'E', '1', 'B'}, {'B', '1', 'M', '1', 'B'}, {'B', '1', '1', '1', 'B'}, {'B', 'B', 'B', 'B', 'B'}}, {1, 2}));
}

}