#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int regionsBySlashes(std::vector<std::string> const &grid) const
    {
        const size_t n = grid.size();
        std::vector<std::vector<int>> visited(n, std::vector<int>(n, Empty));
        size_t regionsCount = 0;
        for (size_t row = 0; row < n; ++row)
        {
            for (size_t column = 0; column < n; ++column)
            {
                if (visited[row][column] == FillFull)
                    continue;
                while (visited[row][column] != FillFull)
                {
                    ++regionsCount;
                    visitRegion(grid, row, column, visited);
                }
            }
        }
        return static_cast<int>(regionsCount);
    }

private:
    static constexpr int Empty = 0b00;
    static constexpr int FillLeft = 0b10;
    static constexpr int FillRight = 0b01;
    static constexpr int FillFull = 0b11;

    struct Cell
    {
        Cell(size_t row, size_t column, bool leftPart) : Row(row), Column(column), LeftPart(leftPart)
        {
        }

        size_t Row;
        size_t Column;
        bool LeftPart;
    };

    void visitRegion(std::vector<std::string> const &grid, size_t startRow, size_t startColumn, std::vector<std::vector<int>> &visited) const
    {
        std::queue<Cell> region;
        if (grid[startRow][startColumn] == ' ')
            region.emplace(startRow, startColumn, false);
        else
        {
            region.emplace(startRow, startColumn, (visited[startRow][startColumn] & FillLeft) == 0);
            visited[startRow][startColumn] |= (visited[startRow][startColumn] & FillLeft) == 0 ? FillLeft : FillRight;
        }
        while (!region.empty())
        {
            Cell current(region.front());
            region.pop();
            moveTop(grid, current, visited, region);
            moveBottom(grid, current, visited, region);
            moveLeft(grid, current, visited, region);
            moveRight(grid, current, visited, region);
        }
    }

    void moveTop(std::vector<std::string> const &grid, Cell const &current, std::vector<std::vector<int>> &visited, std::queue<Cell> &region) const
    {
        if (current.Row == 0)
            return;
        if ((grid[current.Row][current.Column] == '\\') && current.LeftPart)
            return;
        if ((grid[current.Row][current.Column] == '/') && !current.LeftPart)
            return;
        if (visited[current.Row - 1][current.Column] == FillFull)
            return;
        if ((grid[current.Row - 1][current.Column] == '\\') && ((visited[current.Row - 1][current.Column] & FillLeft) != 0))
            return;
        if ((grid[current.Row - 1][current.Column] == '/') && ((visited[current.Row - 1][current.Column] & FillRight) != 0))
            return;
        switch (grid[current.Row - 1][current.Column])
        {
            case ' ':
                region.emplace(current.Row - 1, current.Column, false);
                visited[current.Row - 1][current.Column] = FillFull;
                break;
            case '\\':
                region.emplace(current.Row - 1, current.Column, true);
                visited[current.Row - 1][current.Column] |= FillLeft;
                break;
            case '/':
                region.emplace(current.Row - 1, current.Column, false);
                visited[current.Row - 1][current.Column] |= FillRight;
                break;
            default:
                break;
        }
    }

    void moveBottom(std::vector<std::string> const &grid, Cell const &current, std::vector<std::vector<int>> &visited, std::queue<Cell> &region) const
    {
        const size_t n = grid.size();
        if (current.Row == (n - 1))
            return;
        if ((grid[current.Row][current.Column] == '\\') && !current.LeftPart)
            return;
        if ((grid[current.Row][current.Column] == '/') && current.LeftPart)
            return;
        if (visited[current.Row + 1][current.Column] == FillFull)
            return;
        if ((grid[current.Row + 1][current.Column] == '\\') && ((visited[current.Row + 1][current.Column] & FillRight) != 0))
            return;
        if ((grid[current.Row + 1][current.Column] == '/') && ((visited[current.Row + 1][current.Column] & FillLeft) != 0))
            return;
        switch (grid[current.Row + 1][current.Column])
        {
            case ' ':
                region.emplace(current.Row + 1, current.Column, false);
                visited[current.Row + 1][current.Column] = FillFull;
                break;
            case '\\':
                region.emplace(current.Row + 1, current.Column, false);
                visited[current.Row + 1][current.Column] |= FillRight;
                break;
            case '/':
                region.emplace(current.Row + 1, current.Column, true);
                visited[current.Row + 1][current.Column] |= FillLeft;
                break;
            default:
                break;
        }
    }

    void moveLeft(std::vector<std::string> const &grid, Cell const &current, std::vector<std::vector<int>> &visited, std::queue<Cell> &region) const
    {
        if (current.Column == 0)
            return;
        if ((grid[current.Row][current.Column] == '\\') && !current.LeftPart)
            return;
        if ((grid[current.Row][current.Column] == '/') && !current.LeftPart)
            return;
        if (visited[current.Row][current.Column - 1] == FillFull)
            return;
        if ((grid[current.Row][current.Column - 1] == '\\') && ((visited[current.Row][current.Column - 1] & FillRight) != 0))
            return;
        if ((grid[current.Row][current.Column - 1] == '/') && ((visited[current.Row][current.Column - 1] & FillRight) != 0))
            return;
        switch (grid[current.Row][current.Column - 1])
        {
            case ' ':
                region.emplace(current.Row, current.Column - 1, false);
                visited[current.Row][current.Column - 1] = FillFull;
                break;
            case '\\':
            case '/':
                region.emplace(current.Row, current.Column - 1, false);
                visited[current.Row][current.Column - 1] |= FillRight;
                break;
            default:
                break;
        }
    }

    void moveRight(std::vector<std::string> const &grid, Cell const &current, std::vector<std::vector<int>> &visited, std::queue<Cell> &region) const
    {
        const size_t n = grid.size();
        if (current.Column == (n - 1))
            return;
        if ((grid[current.Row][current.Column] == '\\') && current.LeftPart)
            return;
        if ((grid[current.Row][current.Column] == '/') && current.LeftPart)
            return;
        if (visited[current.Row][current.Column + 1] == FillFull)
            return;
        if ((grid[current.Row][current.Column + 1] == '\\') && ((visited[current.Row][current.Column + 1] & FillLeft) != 0))
            return;
        if ((grid[current.Row][current.Column + 1] == '/') && ((visited[current.Row][current.Column + 1] & FillLeft) != 0))
            return;
        switch (grid[current.Row][current.Column + 1])
        {
            case ' ':
                region.emplace(current.Row, current.Column + 1, false);
                visited[current.Row][current.Column + 1] = FillFull;
                break;
            case '\\':
            case '/':
                region.emplace(current.Row, current.Column + 1, true);
                visited[current.Row][current.Column + 1] |= FillLeft;
                break;
            default:
                break;
        }
    }
};

}

namespace RegionsCutBySlashesTask
{

TEST(RegionsCutBySlashesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.regionsBySlashes({" /", "/ "}));
    ASSERT_EQ(1, solution.regionsBySlashes({" /", "  "}));
    ASSERT_EQ(5, solution.regionsBySlashes({"/\\", "\\/"}));
}

}