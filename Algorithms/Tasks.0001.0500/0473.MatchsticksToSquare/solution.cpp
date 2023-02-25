#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool makesquare(std::vector<int> const &nums) const
    {
        const int perimeter = std::accumulate(nums.cbegin(), nums.cend(), 0);
        if ((perimeter % 4) != 0)
            return false;
        const int side = perimeter / 4;
        return canMakeSquare(nums, 0, 0, 0, side, 0);
    }

private:
    bool canMakeSquare(std::vector<int> const &nums, int usedMatchsticks, int sideCount, int current, int side, size_t index) const
    {
        if (sideCount == 3)
            return true;
        if (index == nums.size())
            return false;
        const int mask = 1 << index;
        if ((usedMatchsticks & mask) != 0)
            return canMakeSquare(nums, usedMatchsticks, sideCount, current, side, index + 1);
        if ((current + nums[index]) > side)
            return canMakeSquare(nums, usedMatchsticks, sideCount, current, side, index + 1);
        usedMatchsticks |= mask;
        if ((current + nums[index]) == side)
            return canMakeSquare(nums, usedMatchsticks, sideCount + 1, 0, side, 0);
        if (canMakeSquare(nums, usedMatchsticks, sideCount, current + nums[index], side, index + 1))
            return true;
        usedMatchsticks &= ~mask;
        return canMakeSquare(nums, usedMatchsticks, sideCount, current, side, index + 1);
    }
};

}

namespace MatchsticksToSquareTask
{

TEST(MatchsticksToSquareTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.makesquare({1, 1, 2, 2, 2}));
    ASSERT_EQ(false, solution.makesquare({3, 3, 3, 3, 4}));
}

TEST(MatchsticksToSquareTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.makesquare({5, 5, 5, 5, 4, 4, 4, 4, 3, 3, 3, 3}));
    ASSERT_EQ(true, solution.makesquare({1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}));
}

}