#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maximumRows(std::vector<std::vector<int>> const &matrix, int numSelect) const
    {
        std::vector<size_t> columns;
        return calcMaxCoveredRows(matrix, numSelect, columns, 0);
    }

private:
    [[nodiscard]] bool isZeroRow(std::vector<int> const &row) const
    {
        return std::all_of(row.cbegin(), row.cend(), [](int value) { return value == 0; });
    }

    [[nodiscard]] bool isRowCovered(std::vector<int> const &row, std::vector<size_t> const &columns) const
    {
        size_t setIndex = 0;
        for (size_t column = 0; column < row.size(); ++column)
        {
            if ((setIndex < columns.size()) && (column == columns[setIndex]))
                ++setIndex;
            else if (row[column] != 0)
                return false;
        }
        return true;
    }

    [[nodiscard]] int calcCoveredRows(std::vector<std::vector<int>> const &matrix, std::vector<size_t> const &columns) const
    {
        return static_cast<int>(std::count_if(matrix.cbegin(),
                                              matrix.cend(),
                                              [this, &columns](std::vector<int> const &row) { return isZeroRow(row) || isRowCovered(row, columns); }));
    }

    int calcMaxCoveredRows(std::vector<std::vector<int>> const &matrix, size_t numSelect, std::vector<size_t> &columns, size_t columnStart) const
    {
        const size_t columnsCount = matrix.front().size();
        int maxCoveredRowsCount = 0;
        for (size_t column = columnStart; column <= columnsCount - (numSelect - columns.size()); ++column)
        {
            columns.push_back(column);
            int coveredRowsCount = columns.size() == numSelect ? calcCoveredRows(matrix, columns) : calcMaxCoveredRows(matrix, numSelect, columns, column + 1);
            maxCoveredRowsCount = std::max(maxCoveredRowsCount, coveredRowsCount);
            columns.pop_back();
        }
        return maxCoveredRowsCount;
    }
};

}

namespace MaxRowsCoveredByColumnsTask
{

TEST(MaxRowsCoveredByColumnsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maximumRows({{0, 0, 0}, {1, 0, 1}, {0, 1, 1}, {0, 0, 1}}, 2));
    ASSERT_EQ(2, solution.maximumRows({{1}, {0}}, 1));
}

}