#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int largestOverlap(std::vector<std::vector<int>> const &img1, std::vector<std::vector<int>> const &img2) const
    {
        const int n = static_cast<int>(img1.size());
        int bestOverlap = 0;
        for (int rowShift = -n + 1; rowShift < n; ++rowShift)
        {
            for (int columnShift = -n + 1; columnShift < n; ++columnShift)
            {
                // we translate only img2
                const size_t img1Row = rowShift < 0 ? 0 : rowShift;
                const size_t img1Column = columnShift < 0 ? 0 : columnShift;
                const size_t img2Row = rowShift >= 0 ? 0 : std::abs(rowShift);
                const size_t img2Column = columnShift >= 0 ? 0 : std::abs(columnShift);
                bestOverlap = std::max(bestOverlap, calcOverlap(img1, img2, img1Row, img1Column, img2Row, img2Column));
            }
        }
        return bestOverlap;
    }

private:
    [[nodiscard]] int calcOverlap(std::vector<std::vector<int>> const &image,
                                  std::vector<std::vector<int>> const &translatedImage,
                                  size_t imageRow,
                                  size_t imageColumn,
                                  size_t translatedImageRow,
                                  size_t translatedImageColumn) const
    {
        const size_t n = image.size();
        int overlap = 0;
        for (size_t rowShift = 0; (imageRow + rowShift < n) && (translatedImageRow + rowShift < n); ++rowShift)
        {
            for (size_t columnShift = 0; (imageColumn + columnShift < n) && (translatedImageColumn + columnShift < n); ++columnShift)
            {
                if ((image[imageRow + rowShift][imageColumn + columnShift] == 1) &&
                    (translatedImage[translatedImageRow + rowShift][translatedImageColumn + columnShift] == 1))
                    ++overlap;
            }
        }
        return overlap;
    }
};

}

namespace ImageOverlapTask
{

TEST(ImageOverlapTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.largestOverlap({{1, 1, 0}, {0, 1, 0}, {0, 1, 0}}, {{0, 0, 0}, {0, 1, 1}, {0, 0, 1}}));
    ASSERT_EQ(1, solution.largestOverlap({{1}}, {{1}}));
    ASSERT_EQ(0, solution.largestOverlap({{0}}, {{0}}));
}

TEST(ImageOverlapTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.largestOverlap({{0, 0, 0, 0, 1}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}},
                                         {{0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {1, 0, 0, 0, 0}}));
}

}