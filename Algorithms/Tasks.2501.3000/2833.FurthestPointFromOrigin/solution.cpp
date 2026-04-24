#include <stdexcept>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int furthestDistanceFromOrigin(std::string const &moves) const
    {
        size_t leftCount = 0;
        size_t rightCount = 0;
        size_t underlineCount = 0;
        for (const char ch : moves)
        {
            switch(ch)
            {
            case 'L':
                ++leftCount;
                break;
            case 'R':
                ++rightCount;
                break;
            case '_':
                ++underlineCount;
                break;
            default:
                throw std::logic_error("unexpected control flow");
            }
        }
        return static_cast<int>((leftCount >= rightCount ? leftCount - rightCount : rightCount - leftCount) + underlineCount);
    }
};

}

namespace FurthestPointFromOriginTask
{

TEST(FurthestPointFromOriginTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.furthestDistanceFromOrigin("L_RL__R"));
    ASSERT_EQ(5, solution.furthestDistanceFromOrigin("_R__LL_"));
    ASSERT_EQ(7, solution.furthestDistanceFromOrigin("_______"));
}

}