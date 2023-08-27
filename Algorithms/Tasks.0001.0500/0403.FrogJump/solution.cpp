#include <unordered_set>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool canCross(std::vector<int> const &stones) const
    {
        if (stones[1] != 1)
            return false;
        if (stones.size() == 2)
            return true;
        const size_t maxIndex = stones.size() - 1;
        std::unordered_map<int, size_t> knownStones;
        for (size_t index = 0; index < stones.size(); ++index)
            knownStones.emplace(stones[index], index);
        std::vector<std::unordered_set<size_t>> dp(stones.size());
        dp[0].emplace(1);
        for (size_t fromIndex = 0; fromIndex < stones.size() - 1; ++fromIndex)
        {
            for (const size_t toIndex : dp[fromIndex])
            {
                const int step = stones[toIndex] - stones[fromIndex];
                if ((step > 1) && processNextStep(toIndex, step - 1, stones, knownStones, dp))
                    return true;
                if (processNextStep(toIndex, step, stones, knownStones, dp))
                    return true;
                if (processNextStep(toIndex, step + 1, stones, knownStones, dp))
                    return true;
            }
        }
        return false;
    }

private:
    [[nodiscard]] bool processNextStep(size_t index,
                                       int nextStep,
                                       std::vector<int> const &stones,
                                       std::unordered_map<int, size_t> const &knownStones,
                                       std::vector<std::unordered_set<size_t>> &dp) const
    {
        if (!knownStones.contains(stones[index] + nextStep))
            return false;
        const size_t maxIndex = stones.size() - 1;
        const size_t nextIndex = knownStones.at(stones[index] + nextStep);
        if (nextIndex == maxIndex)
            return true;
        dp[index].emplace(nextIndex);
        return false;
    }
};

}

namespace FrogJumpTask
{

TEST(FrogJumpTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canCross({0, 1, 3, 5, 6, 8, 12, 17}));
    ASSERT_EQ(false, solution.canCross({0, 1, 2, 3, 4, 8, 9, 11}));
}

TEST(FrogJumpTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.canCross({0, 1}));
}

}