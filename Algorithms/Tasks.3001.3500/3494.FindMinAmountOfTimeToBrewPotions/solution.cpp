#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long minTime(std::vector<int> const &skill, std::vector<int> const &mana) const
    {
        std::vector<long long> processTimes(skill.size(), 0);
        for (int potion : mana)
        {
            long long maxShift = 0;
            long long currentTime = 0;
            for (size_t index = 0; index < skill.size(); ++index)
            {
                if (processTimes[index] > currentTime)
                    maxShift = std::max(maxShift, processTimes[index] - currentTime);
                currentTime += 1LL * skill[index] * potion;
            }
            currentTime = 0;
            for (size_t index = 0; index < skill.size(); ++index)
            {
                currentTime += 1LL * skill[index] * potion;
                processTimes[index] = currentTime + maxShift;
            }
        }
        return processTimes.back();
    }
};

}

namespace FindMinAmountOfTimeToBrewPotionsTask
{

TEST(FindMinAmountOfTimeToBrewPotionsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(110, solution.minTime({1, 5, 2, 4}, {5, 1, 4, 2}));
    ASSERT_EQ(5, solution.minTime({1, 1, 1}, {1, 1, 1}));
    ASSERT_EQ(21, solution.minTime({1, 2, 3, 4}, {1, 2}));
}

}