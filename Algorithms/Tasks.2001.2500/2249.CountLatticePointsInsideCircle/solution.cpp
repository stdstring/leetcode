#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countLatticePoints(std::vector<std::vector<int>> const &circles) const
    {
        constexpr size_t maxCoord = 100;
        constexpr size_t size = 2 * maxCoord + 1;
        std::vector<std::vector<bool>> points(size, std::vector<bool>(size, false));
        size_t count = 0;
        for (std::vector<int> const &circle: circles)
            count += processCircle(circle[0], circle[1], circle[2], points);
        return static_cast<int>(count);
    }

private:
    size_t processCircle(int x0, int y0, int radius, std::vector<std::vector<bool>> &points) const
    {
        size_t count = 0;
        const int radiusSquare = radius * radius;
        for (int deltaX = 0; deltaX <= radius; ++deltaX)
        {
            for (int deltaY = 0; deltaY <= radius; ++deltaY)
            {
                if ((deltaX * deltaX + deltaY * deltaY) <= radiusSquare)
                {
                    if (!points[0LL + x0 + deltaX][0LL + y0 + deltaY])
                        ++count;
                    points[0LL + x0 + deltaX][0LL + y0 + deltaY] = true;
                    if (!points[0LL + x0 + deltaX][0LL + y0 - deltaY])
                        ++count;
                    points[0LL + x0 + deltaX][0LL + y0 - deltaY] = true;
                    if (!points[0LL + x0 - deltaX][0LL + y0 + deltaY])
                        ++count;
                    points[0LL + x0 - deltaX][0LL + y0 + deltaY] = true;
                    if (!points[0LL + x0 - deltaX][0LL + y0 - deltaY])
                        ++count;
                    points[0LL + x0 - deltaX][0LL + y0 - deltaY] = true;
                }
            }
        }
        return count;
    }
};

}

namespace CountLatticePointsInsideCircleTask
{

TEST(CountLatticePointsInsideCircleTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(5, solution.countLatticePoints({{2, 2, 1}}));
    ASSERT_EQ(16, solution.countLatticePoints({{2, 2, 2}, {3, 4, 1}}));
}

}