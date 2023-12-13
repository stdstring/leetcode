#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numSpecial(std::vector<std::vector<int>> const &mat) const
    {
        const size_t rowCount = mat.size();
        const size_t columnCount = mat.front().size();
        std::vector<size_t> rowData(rowCount, columnCount);
        std::vector<size_t> columnData(columnCount, rowCount);
        for (size_t row = 0; row < rowCount; ++row)
            rowData[row] = calcRowData(mat, row);
        for (size_t column = 0; column < columnCount; ++column)
            columnData[column] = calcColumnData(mat, column);
        size_t result = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            if ((rowData[row] != columnCount) && (columnData[rowData[row]] != rowCount))
                ++result;
        }
        return static_cast<int>(result);
    }

private:
    size_t calcRowData(std::vector<std::vector<int>> const &mat, size_t row) const
    {
        const size_t columnCount = mat.front().size();
        size_t suitableColumn = columnCount;
        for (size_t column = 0; column < columnCount; ++column)
        {
            if (mat[row][column] == 1)
            {
                if (suitableColumn != columnCount)
                    return columnCount;
                suitableColumn = column;
            }
        }
        return suitableColumn;
    }

    size_t calcColumnData(std::vector<std::vector<int>> const &mat, size_t column) const
    {
        const size_t rowCount = mat.size();
        size_t suitableRow = rowCount;
        for (size_t row = 0; row < rowCount; ++row)
        {
            if (mat[row][column] == 1)
            {
                if (suitableRow != rowCount)
                    return rowCount;
                suitableRow = row;
            }
        }
        return suitableRow;
    }
};

}

namespace SpecialPositionsInBinaryMatrixTask
{

TEST(SpecialPositionsInBinaryMatrixTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.numSpecial({{1, 0, 0}, {0, 0, 1}, {1, 0, 0}}));
    ASSERT_EQ(3, solution.numSpecial({{1, 0, 0}, {0, 1, 0}, {0, 0, 1}}));
}

TEST(SpecialPositionsInBinaryMatrixTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.numSpecial({{0, 0}, {0, 0}, {1, 0}}));
}

}