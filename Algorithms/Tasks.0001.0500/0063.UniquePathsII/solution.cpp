#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int uniquePathsWithObstacles(std::vector<std::vector<int>> const &obstacleGrid) const
    {
        const size_t rowCount = obstacleGrid.size();
        const size_t columnCount = obstacleGrid.front().size();
        std::vector<std::vector<int>> pathCountStorage;
        for (size_t row = 0; row < rowCount; ++row)
        {
            pathCountStorage.emplace_back();
            for (size_t column = 0; column < columnCount; ++column)
            {
                pathCountStorage.back().push_back(row == 0 && column == 0 && obstacleGrid[row][column] == 0 ? 1 : 0);
                if (obstacleGrid[row][column] == 1)
                    continue;
                if (row > 0 && obstacleGrid[row - 1][column] == 0)
                    pathCountStorage[row][column] += pathCountStorage[row - 1][column];
                if (column > 0 && obstacleGrid[row][column - 1] == 0)
                    pathCountStorage[row][column] += pathCountStorage[row][column - 1];
            }
        }
        return pathCountStorage.back().back();
    }
};

}

namespace UniquePathsIITask
{

TEST(UniquePathsIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(2, solution.uniquePathsWithObstacles({{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}));
}

TEST(UniquePathsIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.uniquePathsWithObstacles({{1}}));
}

}