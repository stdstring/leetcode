#include <limits>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    void setZeroes(std::vector<std::vector<int>> &matrix)
    {
        bool isFirstRowZero = false;
        bool isFirstColumnZero = false;
        for (size_t row = 0; row < matrix.size(); ++row)
        {
            for (size_t column = 0; column < matrix.front().size(); ++column)
            {
                if (matrix[row][column] == 0)
                {
                    matrix[row][0] = 0;
                    matrix[0][column] = 0;
                    if (row == 0)
                        isFirstRowZero = true;
                    if (column == 0)
                        isFirstColumnZero = true;
                }
            }
        }
        for (size_t row = 1; row < matrix.size(); ++row)
        {
            if (matrix[row][0] == 0)
                setRowZeroes(matrix, row);
        }
        for (size_t column = 1; column < matrix.front().size(); ++column)
        {
            if (matrix[0][column] == 0)
                setColumnZeroes(matrix, column);
        }
        if (isFirstRowZero)
            setRowZeroes(matrix, 0);
        if (isFirstColumnZero)
            setColumnZeroes(matrix, 0);
    }

private:
    void setRowZeroes(std::vector<std::vector<int>> &matrix, size_t row)
    {
        for (size_t column = 0; column < matrix.front().size(); ++column)
            matrix[row][column] = 0;
    }

    void setColumnZeroes(std::vector<std::vector<int>> &matrix, size_t column)
    {
        for (size_t row = 0; row < matrix.size(); ++row)
            matrix[row][column] = 0;
    }
};

}

namespace SetMatrixZeroesTask
{

TEST(SetMatrixZeroesTaskTests, Examples)
{
    Solution solution;
    std::vector<std::vector<int>> matrix1({{1, 1, 1}, {1, 0, 1}, {1, 1, 1}});
    solution.setZeroes(matrix1);
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 0, 1}, {0, 0, 0}, {1, 0, 1}}), matrix1);
    std::vector<std::vector<int>> matrix2({{0, 1, 2, 0}, {3, 4, 5, 2}, {1, 3, 1, 5}});
    solution.setZeroes(matrix2);
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 0, 0, 0}, {0, 4, 5, 0}, {0, 3, 1, 0}}), matrix2);
}

TEST(SetMatrixZeroesTaskTests, FromWrongAnswers)
{
    Solution solution;
    std::vector<std::vector<int>> matrix1({{2147483647}, {2}, {3}});
    solution.setZeroes(matrix1);
    ASSERT_EQ(std::vector<std::vector<int>>({{2147483647}, {2}, {3}}), matrix1);
    std::vector<std::vector<int>> matrix2({{std::numeric_limits<int>::min()}, {2}, {3}});
    solution.setZeroes(matrix2);
    ASSERT_EQ(std::vector<std::vector<int>>({{std::numeric_limits<int>::min()}, {2}, {3}}), matrix2);
    std::vector<std::vector<int>> matrix3({{1, 2, 3, 4}, {5, 0, 7, 8}, {0, 10, 11, 12}, {13, 14, 15, 0}});
    solution.setZeroes(matrix3);
    ASSERT_EQ(std::vector<std::vector<int>>({{0,0,3,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}}), matrix3);
    std::vector<std::vector<int>> matrix4({{1, 0, 3}});
    solution.setZeroes(matrix4);
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 0, 0}}), matrix4);
}

}