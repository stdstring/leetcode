#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    int minimumTotal(std::vector<std::vector<int>> const &triangle) const
    {
        std::vector<int> paths(triangle.front());
        int rowMinValue = paths.front();
        for (size_t rowIndex = 1; rowIndex < triangle.size(); ++rowIndex)
        {
            std::vector<int> const &row = triangle[rowIndex];
            int prevSumValue = 0;
            for (size_t columnIndex = 0; columnIndex < row.size(); ++columnIndex)
            {
                int currentSumValue = columnIndex < paths.size() ? paths[columnIndex] : 0;
                if (columnIndex == 0)
                {
                    paths[0] = currentSumValue + row[0];
                    rowMinValue = paths[0];
                }
                else if (columnIndex == (row.size() - 1))
                    paths.push_back(prevSumValue + row[columnIndex]);
                else
                    paths[columnIndex] = std::min(prevSumValue, currentSumValue) + row[columnIndex];
                prevSumValue = currentSumValue;
                if (paths[columnIndex] < rowMinValue)
                    rowMinValue = paths[columnIndex];
            }
        }
        return rowMinValue;
    }
};

}

namespace TriangleTask
{

TEST(TriangleTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(11, solution.minimumTotal({{2}, {3, 4}, {6, 5, 7}, {4, 1, 8, 3}}));
}

TEST(TriangleTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(-10, solution.minimumTotal({{-10}}));
}

}