#include <algorithm>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfSubmatrices(std::vector<std::vector<char>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        // balance - has X
        typedef std::pair<int, bool> TPrefixData;
        std::vector<TPrefixData> prevRow(columnCount, TPrefixData(0, false));
        size_t submatricesCount = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            std::vector<TPrefixData> currentRow(columnCount, TPrefixData(0, false));
            for (size_t column = 0; column < columnCount; ++column)
            {
                const char cell = grid[row][column];
                currentRow[column].first = getCellValue(cell) +
                                           (column > 0 ? currentRow[column - 1].first : 0) +
                                           prevRow[column].first -
                                           (column > 0 ? prevRow[column - 1].first : 0);
                currentRow[column].second = (column > 0 ? currentRow[column - 1].second : false) ||
                                            prevRow[column].second ||
                                            (cell == 'X');
                if (currentRow[column].second && (currentRow[column].first == 0))
                    ++submatricesCount;
            }
            std::swap(prevRow, currentRow);
        }
        return static_cast<int>(submatricesCount);
    }

private:
    [[nodiscard]] int getCellValue(char cell) const
    {
        switch (cell)
        {
        case 'X':
            return +1;
        case 'Y':
            return -1;
        default:
            return 0;
        }
    }
};

}

namespace CountSubmatricesEqualFrequencyXYTask
{

TEST(CountSubmatricesEqualFrequencyXYTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.numberOfSubmatrices({{'X', 'Y', '.'}, {'Y', '.', '.'}}));
    ASSERT_EQ(0, solution.numberOfSubmatrices({{'X', 'X'}, {'X', 'Y'}}));
    ASSERT_EQ(0, solution.numberOfSubmatrices({{'.', '.'}, {'.', '.'}}));
}

}