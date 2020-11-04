#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> spiralOrder(std::vector<std::vector<int>> const &matrix) const
    {
        if (matrix.empty())
            return {};
        const int m = static_cast<int>(matrix.size());
        const int n = static_cast<int>(matrix[0].size());
        std::vector<int> dest;
        dest.reserve(m * n);
        int rowMin = 0;
        int rowMax = m - 1;
        int columnMin = 0;
        int columnMax = n - 1;
        while ((rowMin <= rowMax) && (columnMin <= columnMax))
        {
            processLayer(matrix, dest, rowMin, rowMax, columnMin, columnMax);
            ++rowMin;
            --rowMax;
            ++columnMin;
            --columnMax;
        }
        return dest;
    }

private:
    void processLayer(std::vector<std::vector<int>> const &matrix, std::vector<int> &dest, int rowMin, int rowMax, int columnMin, int columnMax) const
    {
        if (rowMin == rowMax)
        {
            for(int column = columnMin; column <= columnMax; ++column)
                dest.push_back(matrix[rowMin][column]);
            return;
        }
        if (columnMin == columnMax)
        {
            for(int row = rowMin; row <= rowMax; ++row)
                dest.push_back(matrix[row][columnMin]);
            return;
        }
        for(int column = columnMin; column <= columnMax; ++column)
            dest.push_back(matrix[rowMin][column]);
        for(int row = rowMin + 1; row <= rowMax; ++row)
            dest.push_back(matrix[row][columnMax]);
        for(int column = columnMax - 1; column >= columnMin; --column)
            dest.push_back(matrix[rowMax][column]);
        for(int row = rowMax - 1; row > rowMin; --row)
            dest.push_back(matrix[row][columnMin]);
    }
};

}

namespace SpiralMatrixTask
{

TEST(SpiralMatrixTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 3, 6, 9, 8, 7, 4, 5}), solution.spiralOrder({{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}));
    ASSERT_EQ(std::vector<int>({1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7}), solution.spiralOrder({{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}}));
}

TEST(SpiralMatrixTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>(), solution.spiralOrder({}));
}

}