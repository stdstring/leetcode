#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int matrixScore(std::vector<std::vector<int>> const &grid) const
    {
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<int>> dest(grid);
        for (std::vector<int> &row : dest)
        {
            if (row.front() == 0)
                std::transform(row.cbegin(), row.cend(), row.begin(), [](int value){ return value == 0 ? 1 : 0; });
        }
        size_t result = rowCount * (1LL << (columnCount - 1));
        for (size_t column = 1; column < columnCount; ++column)
        {
            size_t onesCount = 0;
            for (size_t row = 0; row < rowCount; ++row)
                onesCount += dest[row][column];
            // virtual flip
            if (onesCount < (rowCount / 2 + rowCount % 2))
                onesCount = rowCount - onesCount;
            result += onesCount * (1LL << (columnCount - 1 - column));
        }
        return static_cast<int>(result);
    }
};

}

namespace ScoreAfterFlippingMatrixTask
{

TEST(ScoreAfterFlippingMatrixTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(39, solution.matrixScore({{0, 0, 1, 1}, {1, 0, 1, 0}, {1, 1, 0, 0}}));
    ASSERT_EQ(1, solution.matrixScore({{0}}));
}

TEST(ScoreAfterFlippingMatrixTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(11, solution.matrixScore({{0, 1}, {0, 1}, {0, 1}, {0, 0}}));
}

}