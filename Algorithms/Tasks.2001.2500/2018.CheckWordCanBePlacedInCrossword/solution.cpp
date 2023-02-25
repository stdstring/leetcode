#include <vector>

#include "gtest/gtest.h"

namespace
{

enum class Direction : int {None = 0, Asc = 1, Desc = -1};

class Solution
{
public:
    [[nodiscard]] bool placeWordInCrossword(std::vector<std::vector<char>> const &board, std::string const &word) const
    {
        const int rowCount = static_cast<int>(board.size());
        const int columnCount = static_cast<int>(board.front().size());
        for (int row = 0; row < rowCount; ++row)
        {
            for (int column = 0; column < columnCount; ++column)
            {
                if (checkWord(board, word, row, column, Direction::None, Direction::Asc) ||
                    checkWord(board, word, row, column, Direction::None, Direction::Desc) ||
                    checkWord(board, word, row, column, Direction::Asc, Direction::None) ||
                    checkWord(board, word, row, column, Direction::Desc, Direction::None))
                    return true;
            }
        }
        return false;
    }

private:
    static constexpr char BlockedCell = '#';
    static constexpr char EmptyCell = ' ';

    [[nodiscard]] bool checkWord(std::vector<std::vector<char>> const &board, std::string const &word, int row, int column, Direction rowDirection, Direction columnDirection) const
    {
        const int rowMax = static_cast<int>(board.size() - 1);
        const int columnMax = static_cast<int>(board.front().size() - 1);
        if ((rowDirection == Direction::Asc) && (row > 0) && (board[row - 1][column] != BlockedCell))
            return false;
        if ((rowDirection == Direction::Desc) && (row < rowMax) && (board[row + 1][column] != BlockedCell))
            return false;
        if ((columnDirection == Direction::Asc) && (column > 0) && (board[row][column - 1] != BlockedCell))
            return false;
        if ((columnDirection == Direction::Desc) && (column < columnMax) && (board[row][column + 1] != BlockedCell))
            return false;
        for (const char ch : word)
        {
            if ((row < 0) || (row > rowMax))
                return false;
            if ((column < 0) || (column > columnMax))
                return false;
            if ((board[row][column] != EmptyCell) && (board[row][column] != ch))
                return false;
            row += static_cast<int>(rowDirection);
            column += static_cast<int>(columnDirection);
        }
        return (row < 0) || (row > rowMax) || (column < 0) || (column > columnMax) || board[row][column] == BlockedCell;
    }
};

}

namespace CheckWordCanBePlacedInCrosswordTask
{

TEST(CheckWordCanBePlacedInCrosswordTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.placeWordInCrossword({{'#', ' ', '#'}, {' ', ' ', '#'}, {'#', 'c', ' '}}, "abc"));
    ASSERT_EQ(false, solution.placeWordInCrossword({{' ', '#', 'a'}, {' ', '#', 'c'}, {' ', '#', 'a'}}, "ac"));
    ASSERT_EQ(true, solution.placeWordInCrossword({{'#', ' ', '#'}, {' ', ' ', '#'}, {'#', ' ', 'c'}}, "ca"));
}

TEST(CheckWordCanBePlacedInCrosswordTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.placeWordInCrossword({{'#', ' ', '#'}, {'#', ' ', '#'}, {'#', ' ', 'c'}}, "ca"));
    ASSERT_EQ(false, solution.placeWordInCrossword({{' ', ' '}, {' ', ' '}}, "a"));
}

}