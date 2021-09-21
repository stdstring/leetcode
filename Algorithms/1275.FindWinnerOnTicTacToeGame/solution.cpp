#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::string tictactoe(std::vector<std::vector<int>> const &moves) const
    {
        constexpr size_t fieldSize = 3;
        std::vector<char> field(3 * 3, ' ');
        for (size_t index = 0; index < moves.size(); ++index)
            field[moves[index][0] * fieldSize + moves[index][1]] = (index % 2 == 0 ? 'X' : 'O');
        if (checkLine('X', field[0 * fieldSize + 0], field[0 * fieldSize + 1], field[0 * fieldSize + 2]) ||
            checkLine('X', field[1 * fieldSize + 0], field[1 * fieldSize + 1], field[1 * fieldSize + 2]) ||
            checkLine('X', field[2 * fieldSize + 0], field[2 * fieldSize + 1], field[2 * fieldSize + 2]) ||
            checkLine('X', field[0 * fieldSize + 0], field[1 * fieldSize + 0], field[2 * fieldSize + 0]) ||
            checkLine('X', field[0 * fieldSize + 1], field[1 * fieldSize + 1], field[2 * fieldSize + 1]) ||
            checkLine('X', field[0 * fieldSize + 2], field[1 * fieldSize + 2], field[2 * fieldSize + 2]) ||
            checkLine('X', field[0 * fieldSize + 0], field[1 * fieldSize + 1], field[2 * fieldSize + 2]) ||
            checkLine('X', field[0 * fieldSize + 2], field[1 * fieldSize + 1], field[2 * fieldSize + 0]))
            return "A";
        if (checkLine('O', field[0 * fieldSize + 0], field[0 * fieldSize + 1], field[0 * fieldSize + 2]) ||
            checkLine('O', field[1 * fieldSize + 0], field[1 * fieldSize + 1], field[1 * fieldSize + 2]) ||
            checkLine('O', field[2 * fieldSize + 0], field[2 * fieldSize + 1], field[2 * fieldSize + 2]) ||
            checkLine('O', field[0 * fieldSize + 0], field[1 * fieldSize + 0], field[2 * fieldSize + 0]) ||
            checkLine('O', field[0 * fieldSize + 1], field[1 * fieldSize + 1], field[2 * fieldSize + 1]) ||
            checkLine('O', field[0 * fieldSize + 2], field[1 * fieldSize + 2], field[2 * fieldSize + 2]) ||
            checkLine('O', field[0 * fieldSize + 0], field[1 * fieldSize + 1], field[2 * fieldSize + 2]) ||
            checkLine('O', field[0 * fieldSize + 2], field[1 * fieldSize + 1], field[2 * fieldSize + 0]))
            return "B";
        return moves.size() == fieldSize * fieldSize ? "Draw" : "Pending";
    }

private:
    bool checkLine(char expectedValue, char cell1, char cell2, char cell3) const
    {
        return (cell1 == expectedValue) && (cell2 == expectedValue) && (cell3 == expectedValue);
    }
};

}

namespace FindWinnerOnTicTacToeGameTask
{

TEST(FindWinnerOnTicTacToeGameTask, Examples)
{
    const Solution solution;
    ASSERT_EQ("A", solution.tictactoe({{0, 0}, {2, 0}, {1, 1}, {2, 1}, {2, 2}}));
    ASSERT_EQ("B", solution.tictactoe({{0, 0}, {1, 1}, {0, 1}, {0, 2}, {1, 0}, {2, 0}}));
    ASSERT_EQ("Draw", solution.tictactoe({{0, 0}, {1, 1}, {2, 0}, {1, 0}, {1, 2}, {2, 1}, {0, 1}, {0, 2}, {2, 2}}));
    ASSERT_EQ("Pending", solution.tictactoe({{0, 0}, {1, 1}}));
}

}