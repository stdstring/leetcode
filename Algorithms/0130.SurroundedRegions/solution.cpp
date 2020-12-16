#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    void solve(std::vector<std::vector<char>> &board)
    {
        if (board.empty())
            return;
        const size_t rowCount = board.size();
        const size_t columnCount = board.empty() ? 0 : board.front().size();
        // prepare
        for (size_t row = 0; row < rowCount; ++row)
        {
            if (board[row][0] == RegionMark)
                prepareRegion(board, row, 0);
            if (board[row][columnCount - 1] == RegionMark)
                prepareRegion(board, row, columnCount - 1);
        }
        for (size_t column = 0; column < columnCount; ++column)
        {
            if (board[0][column] == RegionMark)
                prepareRegion(board, 0, column);
            if (board[rowCount - 1][column] == RegionMark)
                prepareRegion(board, rowCount - 1, column);
        }
        // fill
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                switch (board[row][column])
                {
                    case RegionMark:
                        board[row][column] = CaptureMark;
                        break;
                    case PrepareMark:
                        board[row][column] = RegionMark;
                        break;
                    default:
                        /* do nothing */;
                }
            }
        }
    }

private:
    static constexpr char RegionMark = 'O';
    static constexpr char CaptureMark = 'X';
    static constexpr char PrepareMark = '!';

    void prepareRegion(std::vector<std::vector<char>> &board, size_t row, size_t column)
    {
        const size_t rowMax = board.size() - 1;
        const size_t columnMax = board.front().size() - 1;
        board[row][column] = PrepareMark;
        if (row > 0 && board[row - 1][column] == RegionMark)
            prepareRegion(board, row - 1, column);
        if (row < rowMax && board[row + 1][column] == RegionMark)
            prepareRegion(board, row + 1, column);
        if (column > 0 && board[row][column - 1] == RegionMark)
            prepareRegion(board, row, column - 1);
        if (column < columnMax && board[row][column + 1] == RegionMark)
            prepareRegion(board, row, column + 1);
    }
};

}

namespace SurroundedRegionsTask
{

TEST(SurroundedRegionsTaskTests, Examples)
{
    Solution solution;
    std::vector<std::vector<char>> board({{'X', 'X', 'X', 'X'}, {'X', 'O', 'O', 'X'}, {'X', 'X', 'O', 'X'}, {'X', 'O', 'X', 'X'}});
    solution.solve(board);
    ASSERT_EQ(std::vector<std::vector<char>>({{'X', 'X', 'X', 'X'}, {'X', 'X', 'X', 'X'}, {'X', 'X', 'X', 'X'}, {'X', 'O', 'X', 'X'}}), board);
}

TEST(SurroundedRegionsTaskTests, FromWrongAnswers)
{
    Solution solution;
    std::vector<std::vector<char>> board;
    solution.solve(board);
    ASSERT_EQ(std::vector<std::vector<char>>(), board);
}

}