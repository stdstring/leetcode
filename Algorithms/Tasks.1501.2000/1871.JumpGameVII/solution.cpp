#include <queue>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canReach(std::string const &s, int minJump, int maxJump) const
    {
        if (s.back() == '1')
            return false;
        const size_t minJumpValue = minJump;
        const size_t maxJumpValue = maxJump;
        const size_t targetPosition = s.size() - 1;
        if ((0 + minJumpValue <= targetPosition) && (0 + maxJumpValue >= targetPosition))
            return true;
        std::queue<size_t> positions;
        for (size_t index = minJumpValue; index <= maxJumpValue; ++index)
        {
            if (s[index] == '0')
                positions.push(index);
        }
        size_t rightBorder = maxJumpValue;
        while (!positions.empty())
        {
            const size_t current = positions.front();
            positions.pop();
            if (current + minJumpValue > targetPosition)
                return false;
            if ((current + minJumpValue <= targetPosition) && (current + maxJumpValue >= targetPosition))
                return true;
            size_t nextRightBorder = std::min(current + maxJumpValue, targetPosition);
            for (size_t index = std::max(rightBorder + 1, current + minJumpValue); index <= nextRightBorder; ++index)
            {
                if (s[index] == '0')
                    positions.push(index);
            }
            rightBorder = std::max(rightBorder, nextRightBorder);
        }
        return false;
    }
};

}

namespace JumpGameVIITask
{

TEST(JumpGameVIITaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.canReach("011010", 2, 3));
    ASSERT_EQ(false, solution.canReach("01101110", 2, 3));
}

TEST(JumpGameVIITaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(true, solution.canReach("00", 1, 1));
}

}