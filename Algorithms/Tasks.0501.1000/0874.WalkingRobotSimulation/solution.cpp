#include <stdexcept>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int robotSim(std::vector<int> const &commands, std::vector<std::vector<int>> const &obstacles) const
    {
        std::unordered_map<int, std::unordered_set<int>> obstaclesXY;
        for (std::vector<int> const &obstacle : obstacles)
            obstaclesXY[obstacle[0]].insert(obstacle[1]);
        std::pair<int, int> direction({0, 1});
        int x = 0;
        int y = 0;
        int maxSquaredDistance = 0;
        for (const int command : commands)
        {
            switch (command)
            {
                case -2:
                    direction = turnLeft(direction);
                    break;
                case -1:
                    direction = turnRight(direction);
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                case 7:
                case 8:
                case 9:
                    for (int step = 0; step < command; ++step)
                    {
                        int nextX = x + direction.first;
                        int nextY = y + direction.second;
                        auto iterator = obstaclesXY.find(nextX);
                        if ((iterator != obstaclesXY.cend()) && (iterator->second.count(nextY)))
                            break;
                        x = nextX;
                        y = nextY;
                    }
                    break;
                default:
                    throw std::logic_error("Unknown command");
            }
            maxSquaredDistance = std::max(maxSquaredDistance, x * x + y * y);
        }
        return maxSquaredDistance;
    }

private:
    [[nodiscard]] std::pair<int, int> turnLeft(std::pair<int, int> const &direction) const
    {
        int xDirection = direction.first == 0 ? (direction.second == 1 ? -1 : 1 ) : 0;
        int yDirection = direction.second == 0 ? (direction.first == 1 ? 1 : -1 ) : 0;
        return {xDirection, yDirection};
    }

    [[nodiscard]] std::pair<int, int> turnRight(std::pair<int, int> const &direction) const
    {
        int xDirection = direction.first == 0 ? (direction.second == 1 ? 1 : -1 ) : 0;
        int yDirection = direction.second == 0 ? (direction.first == 1 ? -1 : 1 ) : 0;
        return {xDirection, yDirection};
    }
};

}

namespace WalkingRobotSimulationTask
{

TEST(WalkingRobotSimulationTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(25, solution.robotSim({4, -1, 3}, {}));
    ASSERT_EQ(65, solution.robotSim({4, -1, 4, -2, 4}, {{2, 4}}));
    ASSERT_EQ(36, solution.robotSim({6, -1, -1, 6}, {}));
}

}