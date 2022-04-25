#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkMove(std::vector<std::vector<char>> const &board, int rMove, int cMove, char color) const
    {
        if (board[rMove][cMove] != '.')
            return false;
        return checkLine(board, rMove, cMove, 1, 0, color) ||
               checkLine(board, rMove, cMove, -1, 0, color) ||
               checkLine(board, rMove, cMove, 0, 1, color) ||
               checkLine(board, rMove, cMove, 0, -1, color) ||
               checkLine(board, rMove, cMove, 1, 1, color) ||
               checkLine(board, rMove, cMove, 1, -1, color) ||
               checkLine(board, rMove, cMove, -1, 1, color) ||
               checkLine(board, rMove, cMove, -1, -1, color);
    }

private:
    [[nodiscard]] bool isGoodCell(int row, int column, int rowMax, int columnMax) const
    {
        return (0 <= row) && (row <= rowMax) && (0 <= column) && (column <= columnMax);
    }

    [[nodiscard]] bool checkLine(std::vector<std::vector<char>> const &board, int rMove, int cMove, int rDirection, int cDirection, char color) const
    {
        const char endpointColor = color;
        const char middleColor = color == 'B' ? 'W' : 'B';
        size_t middleSize = 0;
        const int rMax = static_cast<int>(board.size()) - 1;
        const int cMax = static_cast<int>(board.front().size()) - 1;
        rMove += rDirection;
        cMove += cDirection;
        while (isGoodCell(rMove, cMove, rMax, cMax) && (board[rMove][cMove] == middleColor))
        {
            ++middleSize;
            rMove += rDirection;
            cMove += cDirection;
        }
        return (middleSize > 0) && isGoodCell(rMove, cMove, rMax, cMax) && (board[rMove][cMove] == endpointColor);
    }
};

}

namespace CheckIfMoveIsLegalTask
{

TEST(CheckIfMoveIsLegalTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.checkMove({{'.', '.', '.', 'B', '.', '.', '.', '.'},
                                        {'.', '.', '.', 'W', '.', '.', '.', '.'},
                                        {'.', '.', '.', 'W', '.', '.', '.', '.'},
                                        {'.', '.', '.', 'W', '.', '.', '.', '.'},
                                        {'W', 'B', 'B', '.', 'W', 'W', 'W', 'B'},
                                        {'.', '.', '.', 'B', '.', '.', '.', '.'},
                                        {'.', '.', '.', 'B', '.', '.', '.', '.'},
                                        {'.', '.', '.', 'W', '.', '.', '.', '.'}}, 4, 3, 'B'));
    ASSERT_EQ(false, solution.checkMove({{'.', '.', '.', '.', '.', '.', '.', '.'},
                                         {'.', 'B', '.', '.', 'W', '.', '.', '.'},
                                         {'.', '.', 'W', '.', '.', '.', '.', '.'},
                                         {'.', '.', '.', 'W', 'B', '.', '.', '.'},
                                         {'.', '.', '.', '.', '.', '.', '.', '.'},
                                         {'.', '.', '.', '.', 'B', 'W', '.', '.'},
                                         {'.', '.', '.', '.', '.', '.', 'W', '.'},
                                         {'.', '.', '.', '.', '.', '.', '.', 'B'}}, 4, 4, 'W'));
}

}