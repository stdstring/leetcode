#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxPointsInsideSquare(std::vector<std::vector<int>> const &points, std::string const &s) const
    {
        typedef std::pair<int, char> TPoint;
        std::vector<TPoint> pointData;
        pointData.reserve(points.size());
        for (size_t index = 0; index < points.size(); ++index)
        {
            int sizeX = std::abs(points[index][0]);
            int sizeY = std::abs(points[index][1]);
            pointData.emplace_back(std::max(sizeX, sizeY), s[index]);
        }
        std::ranges::sort(pointData, [](TPoint const& l, TPoint const& r){ return l.first < r.first; });
        constexpr int alphabetStart = 'a';
        int pointsCount = 0;
        int currentSize = 0;
        int usedLetters = 0;
        int currentCount = 0;
        for (auto const &[size, letter] : pointData)
        {
            if (currentSize < size)
            {
                pointsCount += currentCount;
                currentCount = 0;
                currentSize = size;
            }
            const int letterMask = 1 << (letter - alphabetStart);
            if ((usedLetters & letterMask) != 0)
                return pointsCount;
            usedLetters |= letterMask;
            ++currentCount;
        }
        pointsCount += currentCount;
        return pointsCount;
    }
};

}

namespace MaxPointsInsideSquareTask
{

TEST(MaxPointsInsideSquareTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.maxPointsInsideSquare({{2, 2}, {-1, -2}, {-4, 4}, {-3, 1}, {3, -3}}, "abdca"));
    ASSERT_EQ(1, solution.maxPointsInsideSquare({{1, 1}, {-2, -2}, {-2, 2}}, "abb"));
    ASSERT_EQ(0, solution.maxPointsInsideSquare({{1, 1}, {-1, -1}, {2, -2}}, "ccd"));
}

}