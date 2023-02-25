#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> rotateGrid(std::vector<std::vector<int>> const &grid, int k) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        size_t topRow = 0;
        size_t bottomRow = rowCount - 1;
        size_t leftColumn = 0;
        size_t rightColumn = columnCount - 1;
        std::vector<std::vector<int>> result(grid);
        for (;((bottomRow - topRow) > 1) && ((rightColumn - leftColumn) > 1);++topRow, --bottomRow, ++leftColumn, --rightColumn)
        {
            std::vector<int> layer(getLayer(grid, topRow, leftColumn, bottomRow, rightColumn));
            setLayer(result, topRow, leftColumn, bottomRow, rightColumn, shiftData(layer, k));
        }
        if (((bottomRow - topRow) == 1) || ((rightColumn - leftColumn) == 1))
        {
            std::vector<int> layer(getLayer(grid, topRow, leftColumn, bottomRow, rightColumn));
            setLayer(result, topRow, leftColumn, bottomRow, rightColumn, shiftData(layer, k));
        }
        return result;
    }

private:
    [[nodiscard]] std::vector<int> getLayer(std::vector<std::vector<int>> const &grid, size_t topRow, size_t leftColumn, size_t bottomRow, size_t rightColumn) const
    {
        std::vector<int> layer;
        if (topRow == bottomRow)
        {
            for (size_t index = 0; index <= (rightColumn - leftColumn); ++index)
                layer.push_back(grid[topRow][rightColumn - index]);
        }
        else if (leftColumn == rightColumn)
        {
            for (size_t row = topRow; row <= bottomRow; ++row)
                layer.push_back(grid[row][leftColumn]);
        }
        else
        {
            for (size_t row = topRow; row < bottomRow; ++row)
                layer.push_back(grid[row][leftColumn]);
            for (size_t column = leftColumn; column < rightColumn; ++column)
                layer.push_back(grid[bottomRow][column]);
            for (size_t row = bottomRow; row > topRow; --row)
                layer.push_back(grid[row][rightColumn]);
            for (size_t column = rightColumn; column > leftColumn; --column)
                layer.push_back(grid[topRow][column]);
        }
        return layer;
    }

    void setLayer(std::vector<std::vector<int>> &grid, size_t topRow, size_t leftColumn, size_t bottomRow, size_t rightColumn, std::vector<int> const &layer) const
    {
        if (topRow == bottomRow)
        {
            for (size_t index = 0; index < layer.size(); ++index)
                grid[topRow][rightColumn - index] = layer[index];
        }
        else if (leftColumn == rightColumn)
        {
            for (size_t index = 0; index < layer.size(); ++index)
                grid[topRow + index][leftColumn] = layer[index];
        }
        else
        {
            size_t index = 0;
            for (size_t row = topRow; row < bottomRow; ++row, ++index)
                grid[row][leftColumn] = layer[index];
            for (size_t column = leftColumn; column < rightColumn; ++column, ++index)
                grid[bottomRow][column] = layer[index];
            for (size_t row = bottomRow; row > topRow; --row, ++index)
                grid[row][rightColumn] = layer[index];
            for (size_t column = rightColumn; column > leftColumn; --column, ++index)
                grid[topRow][column] = layer[index];
        }
    }

    [[nodiscard]] std::vector<int> shiftData(std::vector<int> const &source, size_t shift) const
    {
        std::vector<int> dest(source);
        for (size_t index = 0; index < source.size(); ++index)
            dest[(index + shift) % dest.size()] = source[index];
        return dest;
    }
};

}

namespace CyclicallyRotatingGridTask
{

TEST(CyclicallyRotatingGridTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{10, 20}, {40, 30}}), solution.rotateGrid({{40, 10}, {30, 20}}, 1));
    ASSERT_EQ(std::vector<std::vector<int>>({{3, 4, 8, 12}, {2, 11, 10, 16}, {1, 7, 6, 15}, {5, 9, 13, 14}}),
              solution.rotateGrid({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}}, 2));
}

}