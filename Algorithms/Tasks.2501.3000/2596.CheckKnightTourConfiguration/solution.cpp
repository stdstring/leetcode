#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool checkValidGrid(std::vector<std::vector<int>> const &grid) const
    {
        if (grid[0][0] != 0)
            return false;
        size_t row = 0;
        size_t column = 0;
        for (int number = 1; number < static_cast<int>(grid.size() * grid.size()); ++number)
        {
            bool hasValidMove = false;
            for (auto const &[nextRow, nextColumn] : getPossibleMoves(row, column, grid.size()))
            {
                if (grid[nextRow][nextColumn] == number)
                {
                    row = nextRow;
                    column = nextColumn;
                    hasValidMove = true;
                    break;
                }
            }
            if (!hasValidMove)
                return false;
        }
        return true;
    }

private:
    [[nodiscard]] std::vector<std::pair<size_t, size_t>> getPossibleMoves(size_t row, size_t column, size_t gridSize) const
    {
        std::vector<std::pair<size_t, size_t>> possibleMoves;
        if (row > 0 && column > 1)
            possibleMoves.emplace_back(row - 1, column - 2);
        if (row > 1 && column > 0)
            possibleMoves.emplace_back(row - 2, column - 1);
        if (row < (gridSize - 1) && column > 1)
            possibleMoves.emplace_back(row + 1, column - 2);
        if (row < (gridSize - 2) && column > 0)
            possibleMoves.emplace_back(row + 2, column - 1);
        if (row > 0 && column < (gridSize - 2))
            possibleMoves.emplace_back(row - 1, column + 2);
        if (row > 1 && column < (gridSize - 1))
            possibleMoves.emplace_back(row - 2, column + 1);
        if (row < (gridSize - 1) && column < (gridSize - 2))
            possibleMoves.emplace_back(row + 1, column + 2);
        if (row < (gridSize - 2) && column < (gridSize - 1))
            possibleMoves.emplace_back(row + 2, column + 1);
        return possibleMoves;
    }
};

}

namespace CheckKnightTourConfigurationTask
{

TEST(CheckKnightTourConfigurationTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.checkValidGrid({{0, 11, 16, 5, 20}, {17, 4, 19, 10, 15}, {12, 1, 8, 21, 6}, {3, 18, 23, 14, 9}, {24, 13, 2, 7, 22}}));
    ASSERT_EQ(false, solution.checkValidGrid({{0, 3, 6}, {5, 8, 1}, {2, 7, 4}}));
}

}