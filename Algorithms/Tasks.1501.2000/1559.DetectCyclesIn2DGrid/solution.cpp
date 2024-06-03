#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool containsCycle(std::vector<std::vector<char>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = grid.front().size();
        const size_t columnMax = columnCount - 1;
        std::vector<std::vector<bool>> visited(rowCount, std::vector<bool>(columnCount, false));
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (visited[row][column])
                    continue;
                std::queue<std::pair<Cell, Cell>> bfsQueue;
                bfsQueue.emplace(Cell(row, column), Cell(row, column));
                visited[row][column] = true;
                while (!bfsQueue.empty())
                {
                    auto [current, parent] = bfsQueue.front();
                    bfsQueue.pop();
                    if ((current.Row > 0) && (processNext(grid, visited, bfsQueue, parent, current, Cell(current.Row - 1, current.Column))))
                        return true;
                    if ((current.Row < rowMax) && (processNext(grid, visited, bfsQueue, parent, current, Cell(current.Row + 1, current.Column))))
                        return true;
                    if ((current.Column > 0) && (processNext(grid, visited, bfsQueue, parent, current, Cell(current.Row, current.Column - 1))))
                        return true;
                    if ((current.Column < columnMax) && (processNext(grid, visited, bfsQueue, parent, current, Cell(current.Row, current.Column + 1))))
                        return true;
                }
            }
        }
        return false;
    }

private:
    struct Cell
    {
        Cell(size_t row, size_t column) : Row(row), Column(column)
        {
        }

        size_t Row;
        size_t Column;
    };

    bool processNext(std::vector<std::vector<char>> const &grid,
                     std::vector<std::vector<bool>> &visited,
                     std::queue<std::pair<Cell, Cell>> &bfsQueue,
                     Cell const& parent,
                     Cell const &current,
                     Cell const &next) const
    {
        if ((next.Row == parent.Row) && (next.Column == parent.Column))
            return false;
        if (grid[next.Row][next.Column] != grid[current.Row][current.Column])
            return false;
        if (visited[next.Row][next.Column])
            return true;
        visited[next.Row][next.Column] = true;
        bfsQueue.emplace(next, current);
        return false;
    }
};

}

namespace DetectCyclesIn2DGridTask
{

TEST(DetectCyclesIn2DGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.containsCycle({{'a', 'a', 'a', 'a'}, {'a', 'b', 'b', 'a'}, {'a', 'b', 'b', 'a'}, {'a', 'a', 'a', 'a'}}));
    ASSERT_EQ(true, solution.containsCycle({{'c', 'c', 'c', 'a'}, {'c', 'd', 'c', 'c'}, {'c', 'c', 'e', 'c'}, {'f', 'c', 'c', 'c'}}));
    ASSERT_EQ(false, solution.containsCycle({{'a', 'b', 'b'}, {'b', 'z', 'b'}, {'b', 'b', 'a'}}));
}

}