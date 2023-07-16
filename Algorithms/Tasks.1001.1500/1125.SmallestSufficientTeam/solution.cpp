#include <algorithm>
#include <string>
#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> smallestSufficientTeam(std::vector<std::string> const &reqSkills, std::vector<std::vector<std::string>> const &people) const
    {
        // preparation
        std::unordered_map<std::string, int> skillBitMap;
        for (size_t index = 0; index < reqSkills.size(); ++index)
            skillBitMap.emplace(reqSkills[index], 1 << index);
        std::vector<int> peopleSkills(people.size(), 0);
        for (size_t index = 0; index < people.size(); ++index)
        {
            int skillMask = 0;
            for (std::string const& skill : people[index])
                skillMask |= skillBitMap[skill];
            peopleSkills[index] = skillMask;
        }
        // init dp
        const int maskCount = 1 << reqSkills.size();
        std::vector<DpData> dp(maskCount, DpData());
        for (size_t index = 0; index < people.size(); ++index)
            dp[peopleSkills[index]] = {1, index, 0};
        // dp steps
        for (int mask = 1; mask < maskCount; ++mask)
        {
            if (dp[mask].LastMask == -1)
                continue;
            const size_t currentCount = dp[mask].Count;
            for (size_t index = 0; index < people.size(); ++index)
            {
                const int skillMask = peopleSkills[index];
                if ((mask | skillMask) != mask)
                    dp[mask | skillMask] = ((currentCount + 1) < dp[mask | skillMask].Count) ?
                                           DpData{currentCount + 1, index, mask} :
                                           dp[mask | skillMask];
            }
        }
        // restore team from dp
        std::vector<int> minSufficientTeam;
        for (int mask = maskCount - 1; mask != 0; mask = dp[mask].LastMask)
            minSufficientTeam.emplace_back(dp[mask].LastPeople);
        std::ranges::sort(minSufficientTeam);
        return minSufficientTeam;
    }

private:
    struct DpData
    {
        size_t Count = INT_MAX;
        size_t LastPeople = INT_MAX;
        int LastMask = 0;
    };
};

}

namespace SmallestSufficientTeamTask
{

TEST(SmallestSufficientTeamTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<int>({0, 2}), solution.smallestSufficientTeam({"java", "nodejs", "reactjs"}, {{"java"}, {"nodejs"}, {"nodejs", "reactjs"}}));
    ASSERT_EQ(std::vector<int>({1, 2}), solution.smallestSufficientTeam({"algorithms", "math", "java", "reactjs", "csharp", "aws"}, 
                                                                        {{"algorithms", "math", "java"},
                                                                         {"algorithms", "math", "reactjs"},
                                                                         {"java", "csharp", "aws"},
                                                                         {"reactjs", "csharp"},
                                                                         {"csharp", "math"},
                                                                         {"aws", "java"}}));
}

}