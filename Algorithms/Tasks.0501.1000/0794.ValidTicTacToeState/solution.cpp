#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool validTicTacToe(std::vector<std::string> const &board) const
    {
        size_t xCount = 0;
        size_t oCount = 0;
        countCells(board, xCount, oCount);
        if ((xCount < oCount) || ((xCount - oCount) > 1))
            return false;
        const bool hasThreeXInRow = hasThreeInRow(board, 'X');
        const bool hasThreeOInRow = hasThreeInRow(board, 'O');
        if (hasThreeXInRow && hasThreeOInRow)
            return false;
        if (!hasThreeXInRow && !hasThreeOInRow)
            return true;
        return (hasThreeXInRow && (xCount > oCount)) || (hasThreeOInRow && (xCount == oCount));
    }

private:
    void countCells(std::vector<std::string> const &board, size_t &xCount, size_t &oCount) const
    {
        for (std::string const &row : board)
        {
            for (char ch : row)
            {
                switch (ch)
                {
                case 'X':
                    ++xCount;
                    break;
                case 'O':
                    ++oCount;
                    break;
                default:
                    /* do nothing */;
                }
            }
        }
    }

    bool hasThreeInRow(std::vector<std::string> const &board, char ch) const
    {
        return (board[0][0] == ch && board[0][1] == ch && board[0][2] == ch) ||
               (board[1][0] == ch && board[1][1] == ch && board[1][2] == ch) ||
               (board[2][0] == ch && board[2][1] == ch && board[2][2] == ch) ||
               (board[0][0] == ch && board[1][0] == ch && board[2][0] == ch) ||
               (board[0][1] == ch && board[1][1] == ch && board[2][1] == ch) ||
               (board[0][2] == ch && board[1][2] == ch && board[2][2] == ch) ||
               (board[0][0] == ch && board[1][1] == ch && board[2][2] == ch) ||
               (board[0][2] == ch && board[1][1] == ch && board[2][0] == ch);
    }
};

}

namespace ValidTicTacToeStateTask
{

TEST(ValidTicTacToeStateTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(false, solution.validTicTacToe({"O  ", "   ", "   "}));
    ASSERT_EQ(false, solution.validTicTacToe({"XOX", " X ", "   "}));
    ASSERT_EQ(false, solution.validTicTacToe({"XXX", "   ", "OOO"}));
    ASSERT_EQ(true, solution.validTicTacToe({"XOX", "O O", "XOX"}));
}

TEST(ValidTicTacToeStateTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(false, solution.validTicTacToe({"XXX","XOO","OO "}));
}

}