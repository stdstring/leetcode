#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> resultGrid(std::vector<std::vector<int>> const &image, int threshold) const
    {
        const size_t rowCount = image.size();
        const size_t columnCount = image.front().size();
        const size_t regionRowCount = rowCount - 2;
        const size_t regionColumnCount = columnCount - 2;
        std::vector<std::vector<int>> regions(regionRowCount, std::vector<int>(regionColumnCount, -1));
        for (size_t row = 0; row < regionRowCount; ++row)
        {
            for (size_t column = 0; column < regionColumnCount; ++column)
                regions[row][column] = calcRegionValue(image, threshold, row, column);
        }
        std::vector<std::vector<int>> result(rowCount, std::vector<int>(columnCount, 0));
        for (size_t row = 0; row < rowCount; ++row)
        {
            for (size_t column = 0; column < columnCount; ++column)
                result[row][column] = calcCellValue(image, regions, row, column);
        }
        return result;
    }

private:
    [[nodiscard]] bool isValidPair(int left, int right, int threshold) const
    {
        return std::abs(left - right) <= threshold;
    }

    [[nodiscard]] int calcRegionValue(std::vector<std::vector<int>> const &image, int threshold, size_t row, size_t column) const
    {
        constexpr int regionSize = 3;
        const bool isValid = isValidPair(image[row][column], image[row][column + 1], threshold) &&
                             isValidPair(image[row][column + 1], image[row][column + 2], threshold) &&
                             isValidPair(image[row + 1][column], image[row + 1][column + 1], threshold) &&
                             isValidPair(image[row + 1][column + 1], image[row + 1][column + 2], threshold) &&
                             isValidPair(image[row + 2][column], image[row + 2][column + 1], threshold) &&
                             isValidPair(image[row + 2][column + 1], image[row + 2][column + 2], threshold) &&
                             isValidPair(image[row][column], image[row + 1][column], threshold) &&
                             isValidPair(image[row + 1][column], image[row + 2][column], threshold) &&
                             isValidPair(image[row][column + 1], image[row + 1][column + 1], threshold) &&
                             isValidPair(image[row + 1][column + 1], image[row + 2][column + 1], threshold) &&
                             isValidPair(image[row][column + 2], image[row + 1][column + 2], threshold) &&
                             isValidPair(image[row + 1][column + 2], image[row + 2][column + 2], threshold);
        if (!isValid)
            return -1;
        const int sum = image[row][column] +
                        image[row][column + 1] +
                        image[row][column + 2] +
                        image[row + 1][column] +
                        image[row + 1][column + 1] +
                        image[row + 1][column + 2] +
                        image[row + 2][column] +
                        image[row + 2][column + 1] +
                        image[row + 2][column + 2];
        return sum / (regionSize * regionSize);
    }

    [[nodiscard]] int calcCellValue(std::vector<std::vector<int>> const &image, std::vector<std::vector<int>> const &regions, size_t row, size_t column) const
    {
        const size_t regionRowCount = regions.size();
        const size_t regionColumnCount = regions.front().size();
        int regionSum = 0;
        int usedRegions = 0;
        for (size_t rowShift = 0; rowShift <= 2; ++rowShift)
        {
            for (size_t columnShift = 0; columnShift <= 2; ++columnShift)
            {
                if ((row >= rowShift) &&
                    (column >= columnShift) &&
                    ((row - rowShift) < regionRowCount) &&
                    ((column - columnShift) < regionColumnCount) &&
                    (regions[row - rowShift][column - columnShift] != -1))
                {
                    regionSum += regions[row - rowShift][column - columnShift];
                    ++usedRegions;
                }
            }
        }
        return usedRegions == 0 ? image[row][column] : regionSum / usedRegions;
    }
};

}

namespace FindGridOfRegionAverageTask
{

TEST(FindGridOfRegionAverageTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{9, 9, 9, 9}, {9, 9, 9, 9}, {9, 9, 9, 9}}),
              solution.resultGrid({{5, 6, 7, 10}, {8, 9, 10, 10}, {11, 12, 13, 10}}, 3));
    ASSERT_EQ(std::vector<std::vector<int>>({{25, 25, 25}, {27, 27, 27}, {27, 27, 27}, {30, 30, 30}}),
              solution.resultGrid({{10, 20, 30}, {15, 25, 35}, {20, 30, 40}, {25, 35, 45}}, 12));
    ASSERT_EQ(std::vector<std::vector<int>>({{5, 6, 7}, {8, 9, 10}, {11, 12, 13}}),
              solution.resultGrid({{5, 6, 7}, {8, 9, 10}, {11, 12, 13}}, 1));
}

}