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
    [[nodiscard]] std::string rankTeams(std::vector<std::string> const &votes) const
    {
        const size_t teamsCount = votes.front().size();
        std::unordered_map<char, size_t> positionsMap;
        std::vector<size_t> indices;
        for (size_t index = 0; index < teamsCount; ++index)
        {
            positionsMap.emplace(votes.front()[index], index);
            indices.push_back(index);
        }
        std::vector<std::vector<size_t>> ranks(teamsCount, std::vector<size_t>(teamsCount, 0));
        for (std::string const &vote : votes)
        {
            for (size_t index = 0; index < teamsCount; ++index)
            {
                const size_t position = positionsMap[vote[index]];
                ++ranks[position][index];
            }
        }
        auto sortFun = [this, &ranks, &votes](size_t left, size_t right)
        {
            switch (compareRanks(ranks[left], ranks[right]))
            {
                case -1:
                    return true;
                case 0:
                    return votes.front()[left] < votes.front()[right];
                case 1:
                default:
                    return false;
            }
        };
        std::sort(indices.begin(), indices.end(), sortFun);
        std::string result;
        for (const size_t index : indices)
            result.push_back(votes.front()[index]);
        return result;
    }

private:
    int compareRanks(std::vector<size_t> const &left, std::vector<size_t> const &right) const
    {
        for (size_t index = 0; index < left.size(); ++index)
        {
            if (left[index] < right[index])
                return 1;
            if (left[index] > right[index])
                return -1;
        }
        return 0;
    }
};

}

namespace RankTeamsByVotesTask
{

TEST(RankTeamsByVotesTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ("ACB", solution.rankTeams({"ABC", "ACB", "ABC", "ACB", "ACB"}));
    ASSERT_EQ("XWYZ", solution.rankTeams({"WXYZ", "XYZW"}));
    ASSERT_EQ("ZMNAGUEDSJYLBOPHRQICWFXTVK", solution.rankTeams({"ZMNAGUEDSJYLBOPHRQICWFXTVK"}));
    ASSERT_EQ("ABC", solution.rankTeams({"BCA", "CAB", "CBA", "ABC", "ACB", "BAC"}));
    ASSERT_EQ("M", solution.rankTeams({"M", "M", "M", "M"}));
}

}
