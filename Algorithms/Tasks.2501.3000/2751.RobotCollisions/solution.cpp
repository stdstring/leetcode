#include <algorithm>
#include <numeric>
#include <stack>
#include <string>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> survivedRobotsHealths(std::vector<int> const &positions, std::vector<int> const &healths, std::string const &directions) const
    {
        std::vector<size_t> indices(positions.size(), 0);
        std::iota(indices.begin(), indices.end(), 0);
        std::sort(indices.begin(), indices.end(), [&positions](size_t left, size_t right) { return positions[left] < positions[right]; });
        std::vector<int> currentHealths(healths);
        std::stack<size_t> rightMovedRobots;
        for (size_t index : indices)
        {
            constexpr char leftMove = 'L';
            constexpr char rightMove = 'R';
            switch (directions[index])
            {
            case leftMove:
                while((!rightMovedRobots.empty()) && (currentHealths[index] > 0))
                {
                    const size_t rightMovedRobotIndex = rightMovedRobots.top();
                    if (currentHealths[index] < currentHealths[rightMovedRobotIndex])
                    {
                        currentHealths[index] = 0;
                        --currentHealths[rightMovedRobotIndex];
                    }
                    if (currentHealths[index] == currentHealths[rightMovedRobotIndex])
                    {
                        currentHealths[index] = 0;
                        currentHealths[rightMovedRobotIndex] = 0;
                        rightMovedRobots.pop();
                    }
                    if (currentHealths[index] > currentHealths[rightMovedRobotIndex])
                    {
                        --currentHealths[index];
                        currentHealths[rightMovedRobotIndex] = 0;
                        rightMovedRobots.pop();
                    }
                }
                break;
            case rightMove:
                rightMovedRobots.push(index);
                break;
            default:
                throw std::logic_error("Bad move");
            }
        }
        std::vector<int> result;
        for (int health : currentHealths)
        {
            if (health > 0)
                result.emplace_back(health);
        }
        return result;
    }
};

}

namespace RobotCollisionsTask
{

TEST(RobotCollisionsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({2, 17, 9, 15, 10}), solution.survivedRobotsHealths({5, 4, 3, 2, 1}, {2, 17, 9, 15, 10}, "RRRRR"));
    ASSERT_EQ(std::vector<int>({14}), solution.survivedRobotsHealths({3, 5, 2, 6}, {10, 10, 15, 12}, "RLRL"));
    ASSERT_EQ(std::vector<int>(), solution.survivedRobotsHealths({1, 2, 5, 6}, {10, 10, 11, 11}, "RLRL"));
}

}