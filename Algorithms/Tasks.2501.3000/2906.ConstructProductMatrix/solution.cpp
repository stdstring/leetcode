#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> constructProductMatrix(std::vector<std::vector<int>> const &grid) const
    {
        constexpr int modValue = 12345;
        const size_t rowCount = grid.size();
        const size_t columnCount = grid.front().size();
        std::vector<std::vector<int>> dest(rowCount, std::vector<int>(columnCount, 1));
        long long prefix = grid[0][0] % modValue;
        for (size_t index = 1; index < rowCount * columnCount; ++index)
        {
            const size_t row = index / columnCount;
            const size_t column = index % columnCount;
            dest[row][column] *= static_cast<int>(prefix);
            prefix = (prefix * grid[row][column]) % modValue;
        }
        long long suffix = grid.back().back() % modValue;
        for (size_t rIndex = 1; rIndex < rowCount * columnCount; ++rIndex)
        {
            const size_t index = rowCount * columnCount - 1 - rIndex;
            const size_t row = index / columnCount;
            const size_t column = index % columnCount;
            dest[row][column] = static_cast<int>((suffix * dest[row][column]) % modValue);
            suffix = (suffix * grid[row][column]) % modValue;
        }
        return dest;
    }
};

}

namespace ConstructProductMatrixTask
{

TEST(ConstructProductMatrixTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{24, 12}, {8, 6}}), solution.constructProductMatrix({{1, 2}, {3, 4}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{2}, {0}, {0}}), solution.constructProductMatrix({{12345}, {2}, {1}}));
}

}