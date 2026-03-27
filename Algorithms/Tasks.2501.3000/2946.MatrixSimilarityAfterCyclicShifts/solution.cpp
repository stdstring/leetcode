#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool areSimilar(std::vector<std::vector<int>> const &mat, int k) const
    {
        const size_t rowCount = mat.size();
        const size_t columnCount = mat.front().size();
        k %= static_cast<int>(columnCount);
        std::vector<std::vector<int>> result(mat);
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if ((row % 2) == 0)
                    result[row][column] = mat[row][(column + columnCount - k) % columnCount];
                else
                    result[row][column] = mat[row][(column + k) % columnCount];
            }
        }
        return isEqual(mat, result);
    }

private:
    [[nodiscard]] bool isEqual(std::vector<std::vector<int>> const &mat1, std::vector<std::vector<int>> const &mat2) const
    {
        const size_t rowCount = mat1.size();
        const size_t columnCount = mat1.front().size();
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (mat1[row][column] != mat2[row][column])
                    return false;
            }
        }
        return true;
    }
};

}

namespace MatrixSimilarityAfterCyclicShiftsTask
{

TEST(MatrixSimilarityAfterCyclicShiftsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.areSimilar({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}, 4));
    ASSERT_EQ(true, solution.areSimilar({{1, 2, 1, 2}, {5, 5, 5, 5}, {6, 3, 6, 3}}, 2));
    ASSERT_EQ(true, solution.areSimilar({{2, 2}, {2, 2}}, 3));
}

}