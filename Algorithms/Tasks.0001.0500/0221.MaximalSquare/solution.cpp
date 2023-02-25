#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int maximalSquare(std::vector<std::vector<char>> const &matrix) const
    {
        if (matrix.empty())
            return 0;
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        std::vector<std::vector<int>> squaresData(rowCount, std::vector<int>(columnCount, 0));
        int maxSquare = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                if (matrix[row][column] == '0')
                    squaresData[row][column] = 0;
                else
                {
                    int topSquare = row > 0 ? squaresData[row - 1][column] : 0;
                    int leftSquare = column > 0 ? squaresData[row][column - 1] : 0;
                    int topLeftSquare = (row > 0) && (column > 0) ? squaresData[row - 1][column - 1] : 0;
                    int currentSquare = 1 + std::min(topSquare, std::min(leftSquare, topLeftSquare));
                    squaresData[row][column] = currentSquare;
                    maxSquare = std::max(currentSquare, maxSquare);
                }
            }
        }
        return maxSquare * maxSquare;
    }
};

}

namespace MaximalSquareTask
{

TEST(MaximalSquareTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.maximalSquare({{'1', '0', '1', '0', '0'}, {'1', '0', '1', '1', '1'}, {'1', '1', '1', '1', '1'}, {'1', '0', '0', '1', '0'}}));
}

TEST(MaximalSquareTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(0, solution.maximalSquare({}));
}

}