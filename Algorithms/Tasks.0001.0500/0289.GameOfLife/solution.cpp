#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    void gameOfLife(std::vector<std::vector<int>> &board)
    {
        const size_t rowCount = board.size();
        const size_t columnCount = board.front().size();
        for (size_t row  = 0; row < rowCount; ++row)
        {
            for (size_t column  = 0; column < columnCount; ++column)
            {
                const size_t neighborsCount = calcNeighborsCount(board, row, column);
                switch(board[row][column])
                {
                    case deadValue:
                        if (neighborsCount == 3)
                            board[row][column] = nextRoundLiveValue;
                        break;
                    case liveValue:
                        if (neighborsCount < 2 || neighborsCount > 3)
                            board[row][column] = nextRoundDeadValue;
                        break;
                    default:
                        /* do nothing */;
                }
            }
        }
        postProcess(board);
    }

private:
    constexpr static int deadValue = 0;
    constexpr static int liveValue = 1;
    constexpr static int nextRoundDeadValue = 2;
    constexpr static int nextRoundLiveValue = 3;

    size_t calcNeighborsCount(std::vector<std::vector<int>> const &board, size_t row, size_t column)
    {
        const size_t maxRow = board.size() - 1;
        const size_t maxColumn = board.front().size() - 1;
        size_t neighborsCount = 0;
        neighborsCount += (column > 0 && isLiveCell(board[row][column - 1]) ? 1 : 0);
        neighborsCount += (row > 0 && column > 0 && isLiveCell(board[row - 1][column - 1]) ? 1 : 0);
        neighborsCount += (row > 0 && isLiveCell(board[row - 1][column]) ? 1 : 0);
        neighborsCount += (row > 0 && column < maxColumn && isLiveCell(board[row - 1][column + 1]) ? 1 : 0);
        neighborsCount += (column < maxColumn && isLiveCell(board[row][column + 1]) ? 1 : 0);
        neighborsCount += (row < maxRow && column < maxColumn && isLiveCell(board[row + 1][column + 1]) ? 1 : 0);
        neighborsCount += (row < maxRow && isLiveCell(board[row + 1][column]) ? 1 : 0);
        neighborsCount += (row < maxRow && column > 0 && isLiveCell(board[row + 1][column - 1]) ? 1 : 0);
        return neighborsCount;
    }

    bool isLiveCell(int cellValue)
    {
        return cellValue == liveValue || cellValue == nextRoundDeadValue;
    }

    void postProcess(std::vector<std::vector<int>> &board)
    {
        const size_t rowCount = board.size();
        const size_t columnCount = board.front().size();
        for (size_t row  = 0; row < rowCount; ++row)
        {
            for (size_t column  = 0; column < columnCount; ++column)
            {
                switch(board[row][column])
                {
                    case nextRoundDeadValue:
                        board[row][column] = deadValue;
                        break;
                    case nextRoundLiveValue:
                        board[row][column] = liveValue;
                        break;
                    default:
                        /* do nothing */;
                }
            }
        }
    }
};

}

namespace GameOfLifeTask
{

TEST(TwoSumTaskTests, Examples)
{
    Solution solution;
    std::vector<std::vector<int>> board({{0, 1, 0}, {0, 0, 1}, {1, 1, 1}, {0, 0, 0}});
    solution.gameOfLife(board);
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 0, 0}, {1, 0, 1}, {0, 1, 1}, {0, 1, 0}}), board);
}

}