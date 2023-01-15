#include <stack>
#include <stdexcept>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countCollisions(std::string const &directions) const
    {
        std::stack<char> roadStack;
        size_t collisionCount = 0;
        for (const char ch : directions)
        {
            switch (ch)
            {
                case 'L':
                    if (roadStack.empty())
                        roadStack.push('L');
                    else
                    {
                        switch (roadStack.top())
                        {
                            case 'L':
                                roadStack.push('L');
                                break;
                            case 'R':
                                roadStack.pop();
                                collisionCount += 2;
                                collisionCount += processObstacle(roadStack);
                                break;
                            case 'S':
                                ++collisionCount;
                                break;
                        default:
                            throw std::logic_error("Unexpected branch");
                        }
                    }
                    break;
                case 'R':
                    roadStack.push('R');
                    break;
                case 'S':
                    collisionCount += processObstacle(roadStack);
                    break;
                default:
                    throw std::logic_error("Unexpected branch");
            }
        }
        return static_cast<int>(collisionCount);
    }

private:
    size_t processObstacle(std::stack<char> &roadStack) const
    {
        size_t collisionCount = 0;
        while (!roadStack.empty() && (roadStack.top() == 'R'))
        {
            ++collisionCount;
            roadStack.pop();
        }
        roadStack.push('S');
        return collisionCount;
    }
};

}

namespace CountCollisionsOnRoadTask
{

TEST(CountCollisionsOnRoadTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.countCollisions("RLRSLL"));
    ASSERT_EQ(0, solution.countCollisions("LLRR"));
}

}