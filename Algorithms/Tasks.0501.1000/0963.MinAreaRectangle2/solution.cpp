#include <algorithm>
#include <functional>
#include <unordered_set>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] double minAreaFreeRect(std::vector<std::vector<int>> const &points) const
    {
        if (points.size() < 4)
            return 0;
        auto hash = [](std::pair<int, int> const &p)
        {
            constexpr std::hash<int> int_hasher;
            return int_hasher(p.first) ^ int_hasher(p.second);
        };
        std::unordered_set<std::pair<int, int>, decltype(hash)> knownPoint(16, hash);
        for (std::vector<int> const& point : points)
            knownPoint.emplace(point[0], point[1]);
        double minArea = 0;
        for (size_t indexA = 0; indexA < points.size(); ++indexA)
        {
            for (size_t indexB = 0; indexB < points.size(); ++indexB)
            {
                if (indexA == indexB)
                    continue;
                for (size_t indexC = 0; indexC < points.size(); ++indexC)
                {
                    if ((indexA == indexC) || (indexB == indexC))
                        continue;
                    const int abX = points[indexB][0] - points[indexA][0];
                    const int abY = points[indexB][1] - points[indexA][1];
                    const int acX = points[indexC][0] - points[indexA][0];
                    const int acY = points[indexC][1] - points[indexA][1];
                    if ((abX * acY - abY * acX) == 0)
                        continue;
                    if ((abX * acX + abY * acY) != 0)
                        continue;
                    const int dx = points[indexA][0] + abX + acX;
                    const int dy = points[indexA][1] + abY + acY;
                    if (!knownPoint.contains(std::pair<int, int>(dx, dy)))
                        continue;
                    const double ab = sqrt(1.0 * (abX * abX + abY * abY));
                    const double ac = sqrt(1.0 * (acX * acX + acY * acY));
                    double area = ab * ac;
                    minArea = (minArea == 0.0 ? area : std::min(area, minArea));
                }
            }
        }
        return minArea;
    }
};

}

namespace MinAreaRectangle2Task
{

TEST(MinAreaRectangle2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_NEAR(2.00000, solution.minAreaFreeRect({{1, 2}, {2, 1}, {1, 0}, {0, 1}}), 0.00001);
    ASSERT_NEAR(1.00000, solution.minAreaFreeRect({{0, 1}, {2, 1}, {1, 1}, {1, 0}, {2, 0}}), 0.00001);
    ASSERT_NEAR(0, solution.minAreaFreeRect({{0, 3}, {1, 2}, {3, 1}, {1, 3}, {2, 1}}), 0.00001);
}

TEST(MinAreaRectangle2Taskests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_NEAR(2.00000, solution.minAreaFreeRect({{3, 1}, {1, 1}, {0, 1}, {2, 1}, {3, 3}, {3, 2}, {0, 2}, {2, 3}}), 0.00001);
    ASSERT_NEAR(20.00000, solution.minAreaFreeRect({{7, 3}, {8, 12}, {13, 5}, {6, 2}, {8, 0}, {12, 8}, {14, 2}, {2, 6}}), 0.00001);
}

}