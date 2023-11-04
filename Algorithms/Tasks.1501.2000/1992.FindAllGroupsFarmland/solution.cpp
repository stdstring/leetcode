#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> findFarmland(std::vector<std::vector<int>> const &land) const
    {
        const size_t rowCount = land.size();
        const size_t columnCount = land.front().size();
        std::vector<bool> visited(rowCount * columnCount, false);
        std::vector<std::vector<int>> result;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (land[row][column] == 0)
                    continue;
                if (visited[row * columnCount + column])
                    continue;
                result.emplace_back(processFarmland(land, visited, row, column));
            }
        }
        return result;
    }

private:
    [[nodiscard]] std::vector<int> processFarmland(std::vector<std::vector<int>> const &land, std::vector<bool> &visited, size_t topRow, size_t leftColumn) const
    {
        const size_t rowCount = land.size();
        const size_t columnCount = land.front().size();
        size_t bottomRow = topRow + 1;
        size_t rightColumn = leftColumn;
        for (; (rightColumn < columnCount) && (land[topRow][rightColumn] == 1); ++rightColumn)
            visited[topRow * columnCount + rightColumn] = true;
        --rightColumn;
        for (;(bottomRow < rowCount) && (land[bottomRow][leftColumn] == 1); ++bottomRow)
        {
            for (size_t column = leftColumn; column <= rightColumn; ++column)
                visited[bottomRow * columnCount + column] = true;
        }
        --bottomRow;
        return {static_cast<int>(topRow), static_cast<int>(leftColumn), static_cast<int>(bottomRow), static_cast<int>(rightColumn)};
    }
};

}

namespace FindAllGroupsFarmlandTask
{

TEST(FindAllGroupsFarmlandTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 0, 0, 0}, {1, 1, 2, 2}}), solution.findFarmland({{1, 0, 0}, {0, 1, 1}, {0, 1, 1}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 0, 1, 1}}), solution.findFarmland({{1, 1}, {1, 1}}));
    ASSERT_EQ(std::vector<std::vector<int>>(), solution.findFarmland({{0}}));
}

}