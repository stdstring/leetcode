#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> imageSmoother(std::vector<std::vector<int>> const &img) const
    {
        const size_t rowCount = img.size();
        const size_t rowMax = rowCount - 1;
        const size_t columnCount = img.front().size();
        const size_t columnMax = columnCount - 1;
        std::vector<std::vector<int>> result(rowCount, std::vector<int>(columnCount, 0));
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
            {
                const int sum = img[row][column] +
                                ((row > 0) && (column > 0) ? img[row - 1][column - 1] : 0) +
                                (row > 0 ? img[row - 1][column] : 0) +
                                ((row > 0) && (column < columnMax) ? img[row - 1][column + 1] : 0) +
                                (column > 0 ? img[row][column - 1] : 0) +
                                (column < columnMax ? img[row][column + 1] : 0) +
                                ((row < rowMax) && (column > 0) ? img[row + 1][column - 1] : 0) +
                                (row < rowMax ? img[row + 1][column] : 0) +
                                ((row < rowMax) && (column < columnMax) ? img[row + 1][column + 1] : 0);
                const int cellCount = 1 +
                                      ((row > 0) && (column > 0) ? 1 : 0) +
                                      (row > 0 ? 1 : 0) +
                                      ((row > 0) && (column < columnMax) ? 1 : 0) +
                                      (column > 0 ? 1 : 0) +
                                      (column < columnMax ? 1 : 0) +
                                      ((row < rowMax) && (column > 0) ? 1 : 0) +
                                      (row < rowMax ? 1 : 0) +
                                      ((row < rowMax) && (column < columnMax) ? 1 : 0);
                result[row][column] = sum / cellCount;
            }
        }
        return result;
    }
};

}

namespace ImageSmootherTask
{

TEST(ImageSmootherTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{0, 0, 0}, {0, 0, 0}, {0, 0, 0}}),
              solution.imageSmoother({{1, 1, 1}, {1, 0, 1}, {1, 1, 1}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{137, 141, 137}, {141, 138, 141}, {137, 141, 137}}),
              solution.imageSmoother({{100, 200, 100}, {200, 50, 200}, {100, 200, 100}}));
}

}