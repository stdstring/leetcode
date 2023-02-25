#include <string>
#include <utility>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isRobotBounded(std::string const &instructions) const
    {
        std::pair<int, int> position(0, 0);
        std::pair<int, int> direction(0, 1);
        for (char ch : instructions)
        {
            switch(ch)
            {
                case 'G':
                    position.first += direction.first;
                    position.second += direction.second;
                    break;
                case 'L':
                    direction = rotateLeft(direction);
                    break;
                case 'R':
                    direction = rotateRight(direction);
                    break;
                default:
                    break;
            }
        }
        return (position.first == 0 && position.second == 0) || !(direction.first == 0 && direction.second == 1);
    }

private:
    std::pair<int, int> rotateLeft(std::pair<int, int> const &direction) const
    {
        // (1, 0) -> (0, 1) -> (-1, 0) -> (0, -1)
        if (direction.first == 1)
            return {0, 1};
        if (direction.first == -1)
            return {0, -1};
        if (direction.second == 1)
            return {-1, 0};
        if (direction.second == -1)
            return {1, 0};
        return {0, 0};
    }

    std::pair<int, int> rotateRight(std::pair<int, int> const &direction) const
    {
        // (1, 0) -> (0, -1) -> (-1, 0) -> (0, 1)
        if (direction.first == 1)
            return {0, -1};
        if (direction.first == -1)
            return {0, 1};
        if (direction.second == 1)
            return {1, 0};
        if (direction.second == -1)
            return {-1, 0};
        return {0, 0};
    }
};

}

namespace RobotBoundedInCircleTask
{

TEST(RobotBoundedInCircleTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isRobotBounded("GGLLGG"));
    ASSERT_EQ(false, solution.isRobotBounded("GG"));
    ASSERT_EQ(true, solution.isRobotBounded("GL"));
}

}
