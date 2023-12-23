#include <functional>
#include <stdexcept>
#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool isPathCrossing(std::string const &path) const
    {
        auto hash = [](std::pair<int, int> const &point)
        {
            constexpr std::hash<int> hasher;
            return hasher(point.first) ^ hasher(point.second);
        };
        std::unordered_set<std::pair<int, int>, decltype(hash)> points(8, hash);
        std::pair<int, int> current({0, 0});
        points.emplace(current);
        for (const char move : path)
        {
            switch (move)
            {
            case 'N':
                ++current.second;
                break;
            case 'S':
                --current.second;
                break;
            case 'E':
                ++current.first;
                break;
            case 'W':
                --current.first;
                break;
            default:
                throw std::logic_error("bad move");
            }
            if (points.contains(current))
                return true;
            points.emplace(current);
        }
        return false;
    }
};

}

namespace PathCrossingTask
{

TEST(PathCrossingTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(false, solution.isPathCrossing("NES"));
    ASSERT_EQ(true, solution.isPathCrossing("NESWW"));
}

}