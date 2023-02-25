#define _USE_MATH_DEFINES
#include <cmath>
#include <limits>
#include <random>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    Solution(double radius, double xCenter, double yCenter) :
        mRadius(radius),
        mXCenter(xCenter),
        mYCenter(yCenter),
        mGenerator(std::random_device()()),
        mRadiusDistribution(0, 1),
        mAngleDistribution(0, 2 * M_PI)
    {
    }

    std::vector<double> randPoint()
    {
        // description: https://mathworld.wolfram.com/DiskPointPicking.html
        const double radius = mRadius * sqrt(mRadiusDistribution(mGenerator));
        const double angle = mAngleDistribution(mGenerator);
        const double x = mXCenter + radius * cos(angle);
        const double y = mYCenter + radius * sin(angle);
        return {x, y};
    }

private:
    double mRadius;
    double mXCenter;
    double mYCenter;
    std::mt19937 mGenerator;
    std::uniform_real_distribution<> mRadiusDistribution;
    std::uniform_real_distribution<> mAngleDistribution;
};

}

namespace
{

void isPointInCircle(std::vector<double> const &point, double radius, double x0, double y0)
{
    const double x = point[0];
    const double y = point[1];
    const double distanceSquare = (x - x0) * (x - x0) + (y - y0) * (y - y0);
    ASSERT_TRUE(distanceSquare <= radius * radius + std::numeric_limits<double>::epsilon());
}

}

namespace GenerateRandomPointInCircleTask
{

TEST(GenerateRandomPointInCircleTaskTests, Examples)
{
    // TODO (std_string) : think about check filling density
    const size_t testCount = 10;
    Solution solution1(1, 0, 0);
    for (size_t number = 1; number <= testCount; ++number)
        isPointInCircle(solution1.randPoint(), 1, 0, 0);
    Solution solution2(10, 5, -7.5);
    for (size_t number = 1; number <= testCount; ++number)
        isPointInCircle(solution2.randPoint(), 10, 5, -7.5);
}

}