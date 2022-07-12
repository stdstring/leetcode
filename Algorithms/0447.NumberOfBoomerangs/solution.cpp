#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numberOfBoomerangs(std::vector<std::vector<int>> const &points) const
    {
        size_t result = 0;
        for (size_t point1 = 0; point1 < points.size(); ++point1)
        {
            std::unordered_map<int, size_t> distanceMap;
            for (size_t point2 = 0; point2 < points.size(); ++point2)
            {
                if (point1 == point2)
                    continue;
                int distance = (points[point1][0] - points[point2][0]) * (points[point1][0] - points[point2][0]) + (points[point1][1] - points[point2][1]) * (points[point1][1] - points[point2][1]);
                ++distanceMap[distance];
            }
            for (const auto &entry : distanceMap)
                result += entry.second * (entry.second - 1);
        }
        return static_cast<int>(result);
    }
};

}

namespace NumberOfBoomerangsTask
{

TEST(NumberOfBoomerangsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.numberOfBoomerangs({{0, 0}, {1, 0}, {2, 0}}));
    ASSERT_EQ(2, solution.numberOfBoomerangs({{1, 1}, {2, 2}, {3, 3}}));
    ASSERT_EQ(0, solution.numberOfBoomerangs({{1, 1}}));
}

}