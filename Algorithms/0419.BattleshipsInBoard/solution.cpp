#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int countBattleships(std::vector<std::vector<char>> const &board) const
    {
        const size_t rowCount = board.size();
        const size_t columnCount = board.front().size();
        int count = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (board[row][column] == 'X' && isBattleshipStart(board, row, column))
                    ++count;
            }
        }
        return count;
    }

private:
    bool isBattleshipStart(std::vector<std::vector<char>> const &board, size_t row, size_t column) const
    {
        if (row == 0 && column == 0)
            return true;
        if (row == 0)
            return board[row][column - 1] == '.';
        if (column == 0)
            return board[row - 1][column] == '.';
        return (board[row][column - 1] == '.') && (board[row - 1][column] == '.');
    }
};

}

namespace BattleshipsInBoardTask
{

TEST(BattleshipsInBoardTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.countBattleships({{'X', '.', '.', 'X'}, {'.', '.', '.', 'X'}, {'.', '.', '.', 'X'}}));
}

TEST(BattleshipsInBoardTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.countBattleships({{'X', '.', 'X'}, {'X', '.', 'X'}}));
}

}