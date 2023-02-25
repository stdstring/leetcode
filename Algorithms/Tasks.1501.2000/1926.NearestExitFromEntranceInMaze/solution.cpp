#include <optional>
#include <queue>
#include <stdexcept>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int nearestExit(std::vector<std::vector<char>> const &maze, std::vector<int> const &entrance) const
    {
        const size_t rowCount = maze.size();
        const size_t columnCount = maze.front().size();
        std::vector<bool> visited(rowCount * columnCount, false);
        std::queue<Cell> queue;
        visited[entrance[0] * columnCount + entrance[1]] = true;
        queue.emplace(entrance[0], entrance[1], 0);
        while (!queue.empty())
        {
            Cell current(queue.front());
            queue.pop();
            std::optional<size_t> leftMove = processNext(maze, visited, queue, current, Move::Left);
            if (leftMove.has_value())
                return static_cast<int>(leftMove.value());
            std::optional<size_t> rightMove = processNext(maze, visited, queue, current, Move::Right);
            if (rightMove.has_value())
                return static_cast<int>(rightMove.value());
            std::optional<size_t> topMove = processNext(maze, visited, queue, current, Move::Top);
            if (topMove.has_value())
                return static_cast<int>(topMove.value());
            std::optional<size_t> bottomMove = processNext(maze, visited, queue, current, Move::Bottom);
            if (bottomMove.has_value())
                return static_cast<int>(bottomMove.value());
        }
        return -1;
    }

private:
    static constexpr char EmptyCell = '.';

    struct Cell
    {
        Cell(size_t row, size_t column, size_t steps) : Row(row), Column(column), Steps(steps)
        {
        }

        size_t Row;
        size_t Column;
        size_t Steps;
    };

    enum class Move {Left, Right, Top, Bottom};

    [[nodiscard]] bool isExit(std::vector<std::vector<char>> const &maze, size_t row, size_t column) const
    {
        const size_t rowMax = maze.size() - 1;
        const size_t columnMax = maze.front().size() - 1;
        return (row == 0) || (row == rowMax) || (column == 0) || (column == columnMax);
    }

    [[nodiscard]] std::pair<size_t, size_t> moveNext(size_t row, size_t column, Move move) const
    {
        switch (move)
        {
            case Move::Left:
                return {row, column - 1};
            case Move::Right:
                return {row, column + 1};
            case Move::Top:
                return {row - 1, column};
            case Move::Bottom:
                return {row + 1, column};
        }
        throw std::logic_error("Unexpected control flow");
    }

    [[nodiscard]] bool canMove(std::vector<std::vector<char>> const &maze, std::vector<bool> const &visited, size_t row, size_t column, Move move) const
    {
        const size_t rowMax = maze.size() - 1;
        const size_t columnCount = maze.front().size();
        const size_t columnMax = columnCount - 1;
        if (((column == 0) && (move == Move::Left)) ||
            ((column == columnMax) && (move == Move::Right)) ||
            ((row == 0) && (move == Move::Top)) ||
            ((row == rowMax) && (move == Move::Bottom)))
        return false;
        const auto[nextRow, nextColumn] = moveNext(row, column, move);
        if (maze[nextRow][nextColumn] != EmptyCell)
            return false;
        if (visited[nextRow * columnCount + nextColumn])
            return false;
        return true;
    }

    std::optional<size_t> processNext(std::vector<std::vector<char>> const &maze, std::vector<bool> &visited, std::queue<Cell> &queue, Cell const &current, Move move) const
    {
        const size_t columnCount = maze.front().size();
        if (!canMove(maze, visited, current.Row, current.Column, move))
            return {};
        const auto[nextRow, nextColumn] = moveNext(current.Row, current.Column, move);
        if (isExit(maze, nextRow, nextColumn))
            return current.Steps + 1;
        visited[nextRow * columnCount + nextColumn] = true;
        queue.emplace(nextRow, nextColumn, current.Steps + 1);
        return {};
    }
};

}

namespace NearestExitFromEntranceInMazeTask
{

TEST(NearestExitFromEntranceInMazeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.nearestExit({{'+', '+', '.', '+'}, {'.', '.', '.', '+'}, {'+', '+', '+', '.'}}, {1, 2}));
    ASSERT_EQ(2, solution.nearestExit({{'+', '+', '+'}, {'.', '.', '.'}, {'+', '+', '+'}}, {1, 0}));
    ASSERT_EQ(-1, solution.nearestExit({{'.', '+'}}, {0, 0}));
}

}