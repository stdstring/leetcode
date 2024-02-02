#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> rangeAddQueries(int n, std::vector<std::vector<int>> const &queries) const
    {
        std::vector<std::vector<int>> diffMatrix(n, std::vector<int>(n, 0));
        for (std::vector<int> const &query : queries)
        {
            const int rowStart = query[0];
            const int columnStart = query[1];
            const int rowEnd = query[2];
            const int columnEnd = query[3];
            for (int row = rowStart; row <= rowEnd; ++row)
            {
                ++diffMatrix[row][columnStart];
                if (columnEnd < (n - 1))
                    --diffMatrix[row][columnEnd + 1];
            }
        }
        std::vector<std::vector<int>> result(n, std::vector<int>(n, 0));
        for (int row = 0; row < n; ++row)
        {
            for (int column = 0; column < n; ++column)
            {
                result[row][column] = (column > 0 ? result[row][column - 1] : 0) + diffMatrix[row][column];
            }
        }
        return result;
    }
};

}

namespace IncrementSubmatricesByOneTask
{

TEST(IncrementSubmatricesByOneTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1, 0}, {1, 2, 1}, {0, 1, 1}}),
              solution.rangeAddQueries(3, {{1, 1, 2, 2}, {0, 0, 1, 1}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 1}, {1, 1}}),
              solution.rangeAddQueries(2, {{0, 0, 1, 1}}));
}

}