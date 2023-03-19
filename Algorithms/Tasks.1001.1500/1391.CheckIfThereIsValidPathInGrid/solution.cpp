#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool hasValidPath(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        if ((rowCount == 1) && (columnCount == 1))
            return true;
        switch (grid[0][0])
        {
        case LRStreet:
            return columnCount > 1 ? hasValidPath(grid, 0, 1, Direction::Right) : false;
        case UDStreet:
        case LDStreet:
            return rowCount > 1 ? hasValidPath(grid, 1, 0, Direction::Down) : false;
        case RDStreet:
            return (columnCount > 1 ? hasValidPath(grid, 0, 1, Direction::Right) : false) ||
                   (rowCount > 1 ? hasValidPath(grid, 1, 0, Direction::Down) : false);
        case LUStreet:
            return {};
        case RUStreet:
            return columnCount > 1 ? hasValidPath(grid, 0, 1, Direction::Right) : false;
        default:
            throw std::logic_error("Unknown street");
        }
    }

private:
    static constexpr int LRStreet = 1;
    static constexpr int UDStreet = 2;
    static constexpr int LDStreet = 3;
    static constexpr int RDStreet = 4;
    static constexpr int LUStreet = 5;
    static constexpr int RUStreet = 6;

    enum class Direction {None, Left, Right, Up, Down};

    struct NextMove
    {
        NextMove() = default;
        NextMove(Direction direction, size_t row, size_t column) :
            Available(true),
            Direction(direction),
            Row(row),
            Column(column)
        {
        }

        bool Available = false;
        Direction Direction = Direction::None;
        size_t Row = 0;
        size_t Column = 0;
    };

    [[nodiscard]] bool hasValidPath(std::vector<std::vector<int>> const &grid, size_t row, size_t column, Direction direction) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        const size_t rowMax = rowCount - 1;
        const size_t columnMax = columnCount - 1;
        std::vector<bool> visited(rowCount * columnCount, false);
        visited[0] = true;
        while ((row != rowMax) || (column != columnMax))
        {
            NextMove nextMove;
            switch (direction)
            {
            case Direction::None:
                throw std::logic_error("Bad direction");
            case Direction::Left:
                nextMove = processLeftDirection(grid, row, column);
                break;
            case Direction::Right:
                nextMove = processRightDirection(grid, row, column);
                break;
            case Direction::Up:
                nextMove = processUpDirection(grid, row, column);
                break;
            case Direction::Down:
                nextMove = processDownDirection(grid, row, column);
                break;
            }
            if (!nextMove.Available)
                return false;
            row = nextMove.Row;
            column = nextMove.Column;
            direction = nextMove.Direction;
            if (visited[row * columnCount + column])
                return false;
            visited[row * columnCount + column] = true;
        }
        return canEnter(direction, grid[rowMax][columnMax]);
    }

    [[nodiscard]] NextMove processLeftDirection(std::vector<std::vector<int>> const &grid, size_t row, size_t column) const
    {
        const size_t rowCount = grid.size();
        const size_t rowMax = rowCount - 1;
        switch (grid[row][column])
        {
        case LRStreet:
            return column > 0 ? NextMove(Direction::Left, row, column - 1) : NextMove();
        case UDStreet:
        case LDStreet:
            return {};
        case RDStreet:
            return row < rowMax ? NextMove(Direction::Down, row + 1, column) : NextMove();
        case LUStreet:
            return {};
        case RUStreet:
            return row > 0 ? NextMove(Direction::Up, row - 1, column) : NextMove();
        default:
            throw std::logic_error("Unknown street");
        }
    }

    [[nodiscard]] NextMove processRightDirection(std::vector<std::vector<int>> const &grid, size_t row, size_t column) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        const size_t rowMax = rowCount - 1;
        const size_t columnMax = columnCount - 1;
        switch (grid[row][column])
        {
        case LRStreet:
            return column < columnMax ? NextMove(Direction::Right, row, column + 1) : NextMove();
        case UDStreet:
            return {};
        case LDStreet:
            return row < rowMax ? NextMove(Direction::Down, row + 1, column) : NextMove();
        case RDStreet:
            return {};
        case LUStreet:
            return row > 0 ? NextMove(Direction::Up, row - 1, column) : NextMove();
        case RUStreet:
            return {};
        default:
            throw std::logic_error("Unknown street");
        }
    }

    [[nodiscard]] NextMove processUpDirection(std::vector<std::vector<int>> const &grid, size_t row, size_t column) const
    {
        const size_t columnCount = grid.front().size();
        const size_t columnMax = columnCount - 1;
        switch (grid[row][column])
        {
        case LRStreet:
            return {};
        case UDStreet:
            return row > 0 ? NextMove(Direction::Up, row - 1, column) : NextMove();
        case LDStreet:
            return column > 0 ? NextMove(Direction::Left, row, column - 1) : NextMove();
        case RDStreet:
            return column < columnMax ? NextMove(Direction::Right, row, column + 1) : NextMove();
        case LUStreet:
        case RUStreet:
            return {};
        default:
            throw std::logic_error("Unknown street");
        }
    }

    [[nodiscard]] NextMove processDownDirection(std::vector<std::vector<int>> const &grid, size_t row, size_t column) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        const size_t rowMax = rowCount - 1;
        const size_t columnMax = columnCount - 1;
        switch (grid[row][column])
        {
        case LRStreet:
            return {};
        case UDStreet:
            return row < rowMax ? NextMove(Direction::Down, row + 1, column) : NextMove();
        case LDStreet:
        case RDStreet:
            return {};
        case LUStreet:
            return column > 0 ? NextMove(Direction::Left, row, column - 1) : NextMove();
        case RUStreet:
            return column < columnMax ? NextMove(Direction::Right, row, column + 1) : NextMove();
        default:
            throw std::logic_error("Unknown street");
        }
    }

    [[nodiscard]] bool canEnter(Direction direction, int street) const
    {
        switch (direction)
        {
        case Direction::None:
            return true;
        case Direction::Left:
            return (street == LRStreet) || (street == RDStreet) || (street == RUStreet);
        case Direction::Right:
            return (street == LRStreet) || (street == LDStreet) || (street == LUStreet);
        case Direction::Up:
            return (street == UDStreet) || (street == LDStreet) || (street == RDStreet);
        case Direction::Down:
            return (street == UDStreet) || (street == LUStreet) || (street == RUStreet);
        }
        return false;
    }
};

}

namespace CheckIfThereIsValidPathInGridTask
{

TEST(CheckIfThereIsValidPathInGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.hasValidPath({{2, 4, 3}, {6, 5, 2}}));
    ASSERT_EQ(false, solution.hasValidPath({{1, 2, 1}, {1, 2, 1}}));
    ASSERT_EQ(false, solution.hasValidPath({{1, 1, 2}}));
}

TEST(CheckIfThereIsValidPathInGridTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.hasValidPath({ {4, 1} }));
    ASSERT_EQ(true, solution.hasValidPath({ {5} }));
}

TEST(CheckIfThereIsValidPathInGridTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.hasValidPath({{4, 1}, {6, 1}}));
    ASSERT_EQ(false, solution.hasValidPath({{4, 3, 3}, {6, 5, 2}}));
}

}