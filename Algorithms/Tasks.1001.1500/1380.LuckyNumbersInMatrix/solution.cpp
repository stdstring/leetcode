#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> luckyNumbers (std::vector<std::vector<int>> const &matrix) const
    {
        const size_t rowCount = matrix.size();
        const size_t columnCount = matrix.front().size();
        std::vector<size_t> rowMinElements(rowCount, 0);
        for (size_t row = 0; row < rowCount; ++row)
            rowMinElements[row] = getRowMinElementIndex(matrix, row);
        std::vector<size_t> columnMaxElements(columnCount, 0);
        for (size_t column = 0; column < columnCount; ++column)
            columnMaxElements[column] = getColumnMaxElementIndex(matrix, column);
        std::vector<int> answer;
        for (size_t row = 0; row < rowCount; ++row)
        {
            const size_t rowMinElement = rowMinElements[row];
            if (matrix[row][rowMinElement] == matrix[columnMaxElements[rowMinElement]][rowMinElement])
                answer.push_back(matrix[row][rowMinElement]);
        }
        return answer;
    }

private:
    [[nodiscard]] size_t getRowMinElementIndex(std::vector<std::vector<int>> const &matrix, size_t row) const
    {
        const size_t columnCount = matrix.front().size();
        size_t minElementIndex = 0;
        for (size_t column = 0; column < columnCount; ++column)
        {
            if (matrix[row][column] < matrix[row][minElementIndex])
                minElementIndex = column;
        }
        return minElementIndex;
    }

    [[nodiscard]] size_t getColumnMaxElementIndex(std::vector<std::vector<int>> const &matrix, size_t column) const
    {
        const size_t rowCount = matrix.size();
        size_t maxElementIndex = 0;
        for (size_t row = 0; row < rowCount; ++row)
        {
            if (matrix[row][column] > matrix[maxElementIndex][column])
                maxElementIndex = row;
        }
        return maxElementIndex;
    }
};

}

namespace LuckyNumbersInMatrixTask
{

TEST(LuckyNumbersInMatrixTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({15}), solution.luckyNumbers({{3, 7, 8}, {9, 11, 13}, {15, 16, 17}}));
    ASSERT_EQ(std::vector<int>({12}), solution.luckyNumbers({{1, 10, 4, 2}, {9, 3, 8, 7}, {15, 16, 17, 12}}));
    ASSERT_EQ(std::vector<int>({7}), solution.luckyNumbers({{7, 8}, {1, 2}}));
}

}