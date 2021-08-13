#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int numRookCaptures(std::vector<std::vector<char>> const &board) const
    {
        // find rock position
        const size_t rowCount = board.size();
        const size_t columnCount = board.front().size();
        size_t rockRow = rowCount;
        size_t rockColumn = columnCount;
        for (size_t index = 0; index < rowCount * columnCount; ++index)
        {
            if (board[index / columnCount][index % columnCount] == Rock)
            {
                rockRow = index / columnCount;
                rockColumn = index % columnCount;
                break;
            }
        }
        size_t capturesCount = 0;
        capturesCount += (hasCapture(board, rockRow, rockColumn, rockRow, -1, 0) ? 1 : 0);
        capturesCount += (hasCapture(board, rockRow, rockColumn, rowCount - rockRow - 1, 1, 0) ? 1 : 0);
        capturesCount += (hasCapture(board, rockRow, rockColumn, rockColumn, 0, -1) ? 1 : 0);
        capturesCount += (hasCapture(board, rockRow, rockColumn, columnCount - rockColumn - 1, 0, 1) ? 1 : 0);
        return static_cast<int>(capturesCount);
    }

private:
    static constexpr char Rock = 'R';
    //static constexpr char Bishop = 'B';
    static constexpr char Pawn = 'p';
    static constexpr char Empty = '.';

    bool hasCapture(std::vector<std::vector<char>> const &board, size_t rockRow, size_t rockColumn, size_t shiftMax, int horizontalFactor, int verticalFactor) const
    {
        for (size_t shift = 1; shift <= shiftMax; ++shift)
        {
            const size_t row = rockRow + horizontalFactor * shift;
            const size_t column = rockColumn + verticalFactor * shift;
            if (board[row][column] != Empty)
                return board[row][column] == Pawn;
        }
        return false;
    }
};

}

namespace AvailableCapturesForRookTask
{

TEST(AvailableCapturesForRookTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(3, solution.numRookCaptures({{'.', '.', '.', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', 'p', '.', '.', '.', '.'},
                                           {'.', '.', '.', 'R', '.', '.', '.', 'p'},
                                           {'.', '.', '.', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', 'p', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '.', '.', '.', '.'}}));
    ASSERT_EQ(0, solution.numRookCaptures({{'.', '.', '.', '.', '.', '.', '.', '.'},
                                           {'.', 'p', 'p', 'p', 'p', 'p', '.', '.'},
                                           {'.', 'p', 'p', 'B', 'p', 'p', '.', '.'},
                                           {'.', 'p', 'B', 'R', 'B', 'p', '.', '.'},
                                           {'.', 'p', 'p', 'B', 'p', 'p', '.', '.'},
                                           {'.', 'p', 'p', 'p', 'p', 'p', '.', '.'},
                                           {'.', '.', '.', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '.', '.', '.', '.'}}));
    ASSERT_EQ(3, solution.numRookCaptures({{'.', '.', '.', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', 'p', '.', '.', '.', '.'},
                                           {'.', '.', '.', 'p', '.', '.', '.', '.'},
                                           {'p', 'p', '.', 'R', '.', 'p', 'B', '.'},
                                           {'.', '.', '.', '.', '.', '.', '.', '.'},
                                           {'.', '.', '.', 'B', '.', '.', '.', '.'},
                                           {'.', '.', '.', 'p', '.', '.', '.', '.'},
                                           {'.', '.', '.', '.', '.', '.', '.', '.'}}));
}

}