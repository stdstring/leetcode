#include <map>
#include <numeric>
#include <tuple>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxPoints(std::vector<std::vector<int>> const &points) const
    {
        if (points.size() == 1)
            return 1;
        // data: direct vector X, direct vector Y, crosspoint numerator, crosspoint denominator
        std::map<std::tuple<int, int, int, int>, size_t> linesData;
        size_t result = 0;
        for (size_t index1 = 0; index1 < points.size(); ++index1)
        {
            for (size_t index2 = index1 + 1; index2 < points.size(); ++index2)
            {
                std::pair<int, int> directVector(calcDirectVector(points[index1], points[index2]));
                std::pair<int, int> crosspoint(calcCrosspoint(points[index1], directVector));
                std::tuple<int, int, int, int> key = std::make_tuple(directVector.first, directVector.second, crosspoint.first, crosspoint.second);
                auto iterator = linesData.find(key);
                if (iterator == linesData.end())
                    iterator = linesData.emplace(key, 1).first;
                ++iterator->second;
                result = std::max(result, iterator->second);
            }
            linesData.clear();
        }
        return static_cast<int>(result);
    }

private:
    [[nodiscard]] std::pair<int, int> calcDirectVector(std::vector<int> const &point1, std::vector<int> const &point2) const
    {
        int directX = point1[0] - point2[0];
        int directY = point1[1] - point2[1];
        if ((directX < 0) || ((directX == 0) && (directY < 0)))
        {
            directX *= -1;
            directY *= -1;
        }
        const int directGCD = std::gcd(directX, directY);
        return {directX /= directGCD, directY /= directGCD};
    }

    [[nodiscard]] std::pair<int, int> calcCrosspoint(std::vector<int> const &point1, std::pair<int, int> const &directVector) const
    {
        if (directVector.first == 0)
            return {point1[0], 1};
        // x = x0 + dx * t
        // y = y0 + dy * t
        // x == 0 => t = -x0 / dx, y = y0 - dy * x0 / dx = (dx * y0 - dy * x0) / dx
        int crosspointNumerator = directVector.first * point1[1] - directVector.second * point1[0];
        int crosspointDenominator = directVector.first;
        const int crosspointGCD = std::gcd(crosspointNumerator, crosspointDenominator);
        return {crosspointNumerator / crosspointGCD, crosspointDenominator / crosspointGCD};
    }
};

}

namespace MaxPointsOnLineTask
{

TEST(MaxPointsOnLineTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.maxPoints({{1, 1}, {2, 2}, {3, 3}}));
    ASSERT_EQ(4, solution.maxPoints({{1, 1}, {3, 2}, {5, 3}, {4, 1}, {2, 3}, {1, 4}}));
}

TEST(MaxPointsOnLineTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.maxPoints({{0, 0}}));
    ASSERT_EQ(7, solution.maxPoints({{0, 1}, {0, 0}, {0, 4}, {0, -2}, {0, -1}, {0, 3}, {0, -4}}));
}

}