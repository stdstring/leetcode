#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long dividePlayers(std::vector<int> const &skill) const
    {
        std::vector<int> sortedSkill(skill);
        std::ranges::sort(sortedSkill);
        const int expectedTeamSkill = sortedSkill.front() + sortedSkill.back();
        long long result = 0;
        for (size_t first = 0, second = sortedSkill.size() - 1; first < second; ++first, --second)
        {
            if ((sortedSkill[first] + sortedSkill[second]) != expectedTeamSkill)
                return -1;
            result += 1LL *sortedSkill[first] * sortedSkill[second];
        }
        return result;
    }
};

}

namespace DividePlayersIntoTeamsOfEqualSkillTask
{

TEST(DividePlayersIntoTeamsOfEqualSkillTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(22, solution.dividePlayers({3, 2, 5, 1, 3, 4}));
    ASSERT_EQ(12, solution.dividePlayers({3, 4}));
    ASSERT_EQ(-1, solution.dividePlayers({1, 1, 2, 3}));
}

}