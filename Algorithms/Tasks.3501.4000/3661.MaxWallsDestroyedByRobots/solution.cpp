#include <algorithm>
#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxWalls(std::vector<int> const &robots, std::vector<int> const &distance, std::vector<int> const &walls) const
    {
        std::map<int, int> robotData;
        for (size_t index = 0; index < robots.size(); ++index)
            robotData.emplace(robots[index], distance[index]);
        std::vector<int> sortedWalls(walls);
        std::ranges::sort(sortedWalls);
        int dpLeftPrev = 0;
        int dpRightPrev = 0;
        for (auto iterator = robotData.cbegin(); iterator != robotData.cend(); ++iterator)
        {
            const int currentPos = iterator->first;
            const int currentDistance = iterator->second;
            // left
            int llShoot = currentPos - currentDistance;
            int lrShoot = currentPos - currentDistance;
            if (iterator != robotData.cbegin())
            {
                const auto prevIterator = std::prev(iterator, 1);
                llShoot = std::max(llShoot, prevIterator->first + 1);
                int prevRightShoot = prevIterator->first + prevIterator->second;
                if (prevRightShoot >= lrShoot)
                    lrShoot = std::min(currentPos, prevRightShoot + 1);
            }
            const int llWalls = calcWalls(sortedWalls, llShoot, currentPos);
            const int lrWalls = calcWalls(sortedWalls, lrShoot, currentPos);
            const int dpLeft = std::max(dpLeftPrev + llWalls, dpRightPrev + lrWalls);
            // right
            int rShoot = currentPos + currentDistance;
            const auto nextIterator = std::next(iterator, 1);
            if (nextIterator != robotData.cend())
                rShoot = std::min(rShoot, nextIterator->first - 1);
            const int rWalls = calcWalls(sortedWalls, currentPos, rShoot);
            const int dpRight = rWalls + std::max(dpLeftPrev, dpRightPrev);
            dpLeftPrev = dpLeft;
            dpRightPrev = dpRight;
        }
        return std::max(dpLeftPrev, dpRightPrev);
    }

private:
    [[nodiscard]] int calcWalls(std::vector<int> const &sortedWalls, int left, int right) const
    {
        const auto leftIterator = std::ranges::lower_bound(sortedWalls, left);
        const auto rightIterator = std::ranges::upper_bound(sortedWalls, right);
        return static_cast<int>(std::distance(leftIterator, rightIterator));
    }
};

}

namespace MaxWallsDestroyedByRobotsTask
{

TEST(MaxWallsDestroyedByRobotsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.maxWalls({4}, {3}, {1, 10}));
    ASSERT_EQ(3, solution.maxWalls({10, 2}, {5, 1}, {5, 2, 7}));
    ASSERT_EQ(0, solution.maxWalls({1, 2}, {100, 1}, {10}));
}

TEST(MaxWallsDestroyedByRobotsTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.maxWalls({1, 5}, {2, 2}, {3}));
}

}
