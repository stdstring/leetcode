#include <cstdint>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool exist(std::vector<std::vector<char>> const &board, std::string const &word) const
    {
        const size_t rowCount = board.size();
        const size_t columnCount = board.front().size();
        std::vector<uint8_t> usedPositions(rowCount * columnCount, 0);
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (findWord(board, word, row, column, usedPositions, 0))
                    return true;
            }
        }
        return false;
    }

private:
    bool findWord(std::vector<std::vector<char>> const &board, std::string const &word, size_t row, size_t column, std::vector<uint8_t> &usedPositions, size_t letterIndex) const
    {
        const size_t rowCount = board.size();
        const size_t columnCount = board.front().size();
        const size_t currentPosition = calcCellIndex(row, column, columnCount);
        if (usedPositions[currentPosition] == 1)
            return false;
        if (board[row][column] != word[letterIndex])
            return false;
        if (letterIndex + 1 == word.size())
            return true;
        usedPositions[currentPosition] = 1;
        if (row > 0 && findWord(board, word, row - 1, column, usedPositions, letterIndex + 1))
            return true;
        if (row < (rowCount - 1) && findWord(board, word, row + 1, column, usedPositions, letterIndex + 1))
            return true;
        if (column > 0 && findWord(board, word, row, column - 1, usedPositions, letterIndex + 1))
            return true;
        if (column < (columnCount - 1) && findWord(board, word, row, column + 1, usedPositions, letterIndex + 1))
            return true;
        usedPositions[currentPosition] = 0;
        return false;
    }

    size_t calcCellIndex(size_t row, size_t column, size_t columnCount) const
    {
        return row * columnCount + column;
    }
};

}

namespace WordSearchTask
{

TEST(WordSearchTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.exist({{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "ABCCED"));
    ASSERT_EQ(true, solution.exist({{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "SEE"));
    ASSERT_EQ(false, solution.exist({{'A', 'B', 'C', 'E'}, {'S', 'F', 'C', 'S'}, {'A', 'D', 'E', 'E'}}, "ABCB"));
}

TEST(WordSearchTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.exist({{'a'}}, "a"));
    ASSERT_EQ(false, solution.exist({{'a'}}, "b"));
}

}