#include <algorithm>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int lenOfVDiagonal(std::vector<std::vector<int>> const &grid) const
    {
        std::vector<TShift> shifts({{1, 1}, {1, -1}, {-1, -1}, {-1, 1}});
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        TMemo memo({rowCount, {columnCount, {DirectionCount, std::vector<int>(TurnCount, -1)}}});
        int result = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (grid[row][column] != 1)
                    continue;
                for (int direction = 0; direction < DirectionCount; ++direction)
                {
                    const int current = processDFS(grid, shifts, memo, static_cast<int>(row), static_cast<int>(column), direction, true, 2) + 1;
                    result = std::max(result, current);
                }
            }
        }
        return result;
    }

private:
    typedef std::vector<std::vector<int>> TGrid;
    typedef std::pair<int, int> TShift;
    typedef std::vector<std::vector<std::vector<std::vector<int>>>> TMemo;

    //static constexpr int DirectLR = 0;
    //static constexpr int ReverseRL = 1;
    //static constexpr int DirectRL = 2;
    //static constexpr int ReverseLR = 3;
    static constexpr int DirectionCount = 4;
    static constexpr int TurnCount = 2;

    [[nodiscard]] int processDFS(TGrid const &grid,
                                 std::vector<TShift> const &shifts,
                                 TMemo &memo,
                                 int currentRow,
                                 int currentColumn,
                                 int direction,
                                 bool turn,
                                 int target) const
    {
        constexpr int beforeTurn = 0;
        constexpr int afterTurn = 1;
        const int rowMax = static_cast<int>(grid.size()) - 1;
        const int columnMax = static_cast<int>(grid.front().size()) - 1;
        const int nextRow = currentRow + shifts[direction].first;
        const int nextColumn = currentColumn + shifts[direction].second;
        if ((nextRow < 0) ||
            (nextRow > rowMax) ||
            (nextColumn < 0) ||
            (nextColumn > columnMax) ||
            (grid[nextRow][nextColumn] != target))
            return 0;
        const int turnValue = turn ? beforeTurn : afterTurn;
        if (memo[nextRow][nextColumn][direction][turnValue] != -1)
            return memo[nextRow][nextColumn][direction][turnValue];
        int maxStep = processDFS(grid, shifts, memo, nextRow, nextColumn, direction, turn, 2 - target);
        if (turn)
            maxStep = std::max(maxStep, processDFS(grid, shifts, memo, nextRow, nextColumn, (direction + 1) % DirectionCount, false, 2 - target));
        memo[nextRow][nextColumn][direction][turnValue] = maxStep + 1;
        return maxStep + 1;
    }
};

}

namespace LengthLongestVDiagonalSegmentTask
{

TEST(LengthLongestVDiagonalSegmentTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.lenOfVDiagonal({{2, 2, 1, 2, 2}, {2, 0, 2, 2, 0}, {2, 0, 1, 1, 0}, {1, 0, 2, 2, 2}, {2, 0, 0, 2, 2}}));
    ASSERT_EQ(4, solution.lenOfVDiagonal({{2, 2, 2, 2, 2}, {2, 0, 2, 2, 0}, {2, 0, 1, 1, 0}, {1, 0, 2, 2, 2}, {2, 0, 0, 2, 2}}));
    ASSERT_EQ(5, solution.lenOfVDiagonal({{1, 2, 2, 2, 2}, {2, 2, 2, 2, 0}, {2, 0, 0, 0, 0}, {0, 0, 2, 2, 2}, {2, 0, 0, 2, 0}}));
}

}