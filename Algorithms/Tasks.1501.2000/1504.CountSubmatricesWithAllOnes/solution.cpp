#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numSubmat(std::vector<std::vector<int>> const &mat) const
    {
        const size_t rowCount = mat.size();
        const size_t columnCount = mat.front().size();
        std::vector<std::vector<size_t>> prefixRowData(rowCount, std::vector<size_t>(columnCount, 0));
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t rColumn = 0; rColumn < columnCount; ++rColumn)
            {
                const size_t column = columnCount - 1 - rColumn;
                if (mat[row][column] == 1)
                    prefixRowData[row][column] = 1 + (rColumn > 0 ? prefixRowData[row][column + 1] : 0);
            }
        }
        size_t result = 0;
        for (size_t rowFrom = 0; rowFrom < rowCount; ++rowFrom)
        {
            for (size_t columnFrom = 0; columnFrom < columnCount; ++columnFrom)
            {
                if (mat[rowFrom][columnFrom] == 0)
                    continue;
                size_t continuousOneCount = columnCount;
                for (size_t rowTo = rowFrom; (rowTo < rowCount) && (mat[rowTo][columnFrom] == 1); ++rowTo)
                {
                    continuousOneCount = std::min(continuousOneCount, prefixRowData[rowTo][columnFrom]);
                    result += continuousOneCount;
                }
            }
        }
        return static_cast<int>(result);
    }
};

}

namespace CountSubmatricesWithAllOnesTask
{

TEST(CountSubmatricesWithAllOnesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(13, solution.numSubmat({{1, 0, 1}, {1, 1, 0}, {1, 1, 0}}));
    ASSERT_EQ(24, solution.numSubmat({{0, 1, 1, 0}, {0, 1, 1, 1}, {1, 1, 1, 0}}));
}

}