#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int firstCompleteIndex(std::vector<int> const &arr, std::vector<std::vector<int>> const &mat) const
    {
        const size_t rowCount = mat.size();
        const size_t columnCount = mat.front().size();
        std::unordered_map<int, std::pair<size_t, size_t>> numbersMap;
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
                numbersMap.emplace(mat[row][column], std::pair<size_t, size_t>(row, column));
        }
        std::vector<size_t> rowPaint(rowCount, 0);
        std::vector<size_t> columnPaint(columnCount, 0);
        for (size_t index = 0; index < arr.size(); ++index)
        {
            auto const &[row, column] = numbersMap[arr[index]];
            ++rowPaint[row];
            ++columnPaint[column];
            if ((rowPaint[row] == columnCount) || (columnPaint[column] == rowCount))
                return static_cast<int>(index);
        }
        return -1;
    }
};

}

namespace FirstCompletelyPaintedRowColumnTask
{

TEST(FirstCompletelyPaintedRowColumnTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.firstCompleteIndex({1, 3, 4, 2}, {{1, 4}, {2, 3}}));
    ASSERT_EQ(3, solution.firstCompleteIndex({2, 8, 7, 4, 1, 3, 5, 6, 9}, {{3, 2, 5}, {1, 4, 6}, {8, 7, 9}}));
}

TEST(FirstCompletelyPaintedRowColumnTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.firstCompleteIndex({1, 4, 5, 2, 6, 3}, {{4, 3, 5}, {1, 2, 6}}));
}

}