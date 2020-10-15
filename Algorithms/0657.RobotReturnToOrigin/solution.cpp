#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool judgeCircle(std::string const &moves) const
    {
        int x = 0;
        int y = 0;
        for (char move : moves)
        {
            switch (move)
            {
                case 'L':
                    --x;
                    break;
                case 'R':
                    ++x;
                    break;
                case 'U':
                    ++y;
                    break;
                case 'D':
                    --y;
                    break;
                default:
                    /* do nothing*/;
            }
        }
        return (x == 0) && (y == 0);
    }
};

}

namespace RobotReturnToOriginTask
{

TEST(RobotReturnToOriginTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.judgeCircle("UD"));
    ASSERT_EQ(false, solution.judgeCircle("LL"));
    ASSERT_EQ(false, solution.judgeCircle("RRDD"));
    ASSERT_EQ(false, solution.judgeCircle("LDRRLRUULR"));
}

}