#include <queue>
#include <tuple>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<std::vector<int>> updateMatrix(std::vector<std::vector<int>> const &matrix) const
    {
        std::vector<std::vector<int>> distances(matrix.size(), std::vector<int>(matrix.front().size(), INT_MAX));
        std::queue<std::tuple<size_t, size_t, int>> queue;
        processZeroes(matrix, distances, queue);
        processQueue(matrix, distances, queue);
        return distances;
    }

private:
    void processZeroes(std::vector<std::vector<int>> const &matrix, std::vector<std::vector<int>> &distances, std::queue<std::tuple<size_t, size_t, int>> &queue) const
    {
        const size_t rowMax = matrix.size() - 1;
        const size_t columnMax = matrix.front().size() - 1;
        for (size_t row = 0; row < matrix.size(); ++row)
        {
            for (size_t column = 0; column < matrix.front().size(); ++column)
            {
                if ((matrix[row][column] != 0))
                    continue;
                distances[row][column] = 0;
                if ((row > 0) && (matrix[row - 1][column] == 1) && (distances[row - 1][column] != 1))
                {
                    distances[row - 1][column] = 1;
                    queue.emplace(row - 1, column, 1);
                }
                if ((row < rowMax) && (matrix[row + 1][column] == 1) && (distances[row + 1][column] != 1))
                {
                    distances[row + 1][column] = 1;
                    queue.emplace(row + 1, column, 1);
                }
                if ((column > 0) && (matrix[row][column - 1] == 1) && (distances[row][column - 1] != 1))
                {
                    distances[row][column - 1] = 1;
                    queue.emplace(row, column - 1, 1);
                }
                if ((column < columnMax) && (matrix[row][column + 1] == 1) && (distances[row][column + 1] != 1))
                {
                    distances[row][column + 1] = 1;
                    queue.emplace(row, column + 1, 1);
                }
            }
        }
    }

    void processQueue(std::vector<std::vector<int>> const &matrix, std::vector<std::vector<int>> &distances, std::queue<std::tuple<size_t, size_t, int>> &queue) const
    {
        const size_t rowMax = matrix.size() - 1;
        const size_t columnMax = matrix.front().size() - 1;
        while (!queue.empty())
        {
            size_t currentRow;
            size_t currentColumn;
            int currentDistance;
            std::tie(currentRow, currentColumn, currentDistance) = queue.front();
            queue.pop();
            if (currentDistance > distances[currentRow][currentColumn])
                continue;
            distances[currentRow][currentColumn] = currentDistance++;
            if ((currentRow > 0) && (matrix[currentRow - 1][currentColumn] != 0) && (currentDistance < distances[currentRow - 1][currentColumn]))
                queue.emplace(currentRow - 1, currentColumn, currentDistance);
            if ((currentRow < rowMax) && (matrix[currentRow + 1][currentColumn] != 0) && (currentDistance < distances[currentRow + 1][currentColumn]))
                queue.emplace(currentRow + 1, currentColumn, currentDistance);
            if ((currentColumn > 0) && (matrix[currentRow][currentColumn - 1] != 0) && (currentDistance < distances[currentRow][currentColumn - 1]))
                queue.emplace(currentRow, currentColumn - 1, currentDistance);
            if ((currentColumn < columnMax) && (matrix[currentRow][currentColumn + 1] != 0) && (currentDistance < distances[currentRow][currentColumn + 1]))
                queue.emplace(currentRow, currentColumn + 1, currentDistance);
        }
    }
};

}

namespace Matrix01Task
{

TEST(Matrix01TaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}), solution.updateMatrix({{0, 0, 0}, {0, 1, 0}, {0, 0, 0}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 0, 0}, {0, 1, 0}, {1, 2, 1}}), solution.updateMatrix({{0, 0, 0}, {0, 1, 0}, {1, 1, 1}}));
}

TEST(Matrix01TaskTests, FromWrongAnswers)
{
    const Solution solution;
    const std::vector<std::vector<int>> source({{1, 0, 1, 1, 0, 0, 1, 0, 0, 1},
                                                {0, 1, 1, 0, 1, 0, 1, 0, 1, 1},
                                                {0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
                                                {1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
                                                {0, 1, 0, 1, 1, 0, 0, 0, 0, 1},
                                                {0, 0, 1, 0, 1, 1, 1, 0, 1, 0},
                                                {0, 1, 0, 1, 0, 1, 0, 0, 1, 1},
                                                {1, 0, 0, 0, 1, 1, 1, 1, 0, 1},
                                                {1, 1, 1, 1, 1, 1, 1, 0, 1, 0},
                                                {1, 1, 1, 1, 0, 1, 0, 0, 1, 1}});
    const std::vector<std::vector<int>> result({{1, 0, 1, 1, 0, 0, 1, 0, 0, 1},
                                                {0, 1, 1, 0, 1, 0, 1, 0, 1, 1},
                                                {0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
                                                {1, 0, 1, 0, 1, 1, 1, 1, 1, 1},
                                                {0, 1, 0, 1, 1, 0, 0, 0, 0, 1},
                                                {0, 0, 1, 0, 1, 1, 1, 0, 1, 0},
                                                {0, 1, 0, 1, 0, 1, 0, 0, 1, 1},
                                                {1, 0, 0, 0, 1, 2, 1, 1, 0, 1},
                                                {2, 1, 1, 1, 1, 2, 1, 0, 1, 0},
                                                {3, 2, 2, 1, 0, 1, 0, 0, 1, 1}});
    ASSERT_EQ(result, solution.updateMatrix(source));
}

}