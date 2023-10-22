#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> restoreMatrix(std::vector<int> const &rowSum, std::vector<int> const &colSum) const
    {
        const size_t rowCount = rowSum.size();
        const size_t columnCount = colSum.size();
        std::vector<std::vector<int>> matrix(rowCount, std::vector<int>(columnCount, 0));
        std::vector<std::pair<int, size_t>> rowSumData;
        for (size_t index = 0; index < rowCount; ++index)
            rowSumData.emplace_back(rowSum[index], index);
        std::ranges::sort(rowSumData, [](std::pair<int, size_t> const &l, std::pair<int, size_t> const &r) { return l.first < r.first; });
        std::vector<std::pair<int, size_t>> columnSumData;
        for (size_t index = 0; index < columnCount; ++index)
            columnSumData.emplace_back(colSum[index], index);
        std::ranges::sort(columnSumData, [](std::pair<int, size_t> const &l, std::pair<int, size_t> const &r) { return l.first < r.first; });
        for (size_t row = 0, column = 0; (row < rowCount) && (column < columnCount);)
        {
            const int rowValue = rowSumData[row].first;
            const size_t rowIndex = rowSumData[row].second;
            const int columnValue = columnSumData[column].first;
            const size_t columnIndex = columnSumData[column].second;
            matrix[rowIndex][columnIndex] = std::min(rowValue, columnValue);
            if (rowValue == columnValue)
            {
                ++row;
                ++column;
            }
            if (rowValue < columnValue)
            {
                ++row;
                columnSumData[column].first -= rowValue;
            }
            if (rowValue > columnValue)
            {
                ++column;
                rowSumData[row].first -= columnValue;
            }
        }
        return matrix;
    }
};

}

namespace FindValidMatrixGivenRowColumnSumsTask
{

TEST(FindValidMatrixGivenRowColumnSumsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{3, 0}, {1, 7}}), solution.restoreMatrix({3, 8}, {4, 7}));
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 5, 0}, {6, 1, 0}, {2, 0, 8}}), solution.restoreMatrix({5, 7, 10}, {8, 6, 8}));
}

}