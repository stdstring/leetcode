#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int removeStones(std::vector<std::vector<int>> const &stones) const
    {
        constexpr int minValue = 0;
        constexpr int maxValue = 10000;
        constexpr int range = maxValue - minValue + 1;
        std::unordered_map<int, int> leaderMap;
        std::unordered_map<int, int> rowLeaderMap;
        std::unordered_map<int, int> columnLeaderMap;
        for (std::vector<int> const &stone : stones)
        {
            int point = (stone[0] - minValue) * range + (stone[1] - minValue);
            int rowLeader = findRCLeader(leaderMap, rowLeaderMap, stone[0]);
            int columnLeader = findRCLeader(leaderMap, columnLeaderMap, stone[1]);
            if ((rowLeader == -1) && (columnLeader == -1))
            {
                leaderMap.emplace(point, -1);
                rowLeaderMap.emplace(stone[0], point);
                columnLeaderMap.emplace(stone[1], point);
            }
            if ((rowLeader != -1) && (columnLeader == -1))
            {
                leaderMap.emplace(point, rowLeader);
                columnLeaderMap.emplace(stone[1], point);
            }
            if ((rowLeader == -1) && (columnLeader != -1))
            {
                leaderMap.emplace(point, columnLeader);
                rowLeaderMap.emplace(stone[0], point);
            }
            if ((rowLeader != -1) && (columnLeader != -1))
            {
                if (rowLeader == columnLeader)
                    leaderMap.emplace(point, rowLeader);
                else if (rowLeader < columnLeader)
                {
                    leaderMap.emplace(point, rowLeader);
                    leaderMap[columnLeader] = rowLeader;
                }
                else
                {
                    leaderMap.emplace(point, columnLeader);
                    leaderMap[rowLeader] = columnLeader;
                }
            }
        }
        size_t leadersCount = 0;
        for (auto const &[_, parent] : leaderMap)
        {
            if (parent == -1)
                ++leadersCount;
        }
        return static_cast<int>(stones.size() - leadersCount);
    }

private:
    [[nodiscard]] int findRCLeader(std::unordered_map<int, int> const &leaderMap, std::unordered_map<int, int> const &rcMap, int rcValue) const
    {
        const auto rcIterator = rcMap.find(rcValue);
        if (rcIterator == rcMap.cend())
            return -1;
        int leader = rcIterator->second;
        while (leaderMap.at(leader) != -1)
            leader = leaderMap.at(leader);
        return leader;
    }
};

}

namespace SomeLeetcodeTaskTask
{

TEST(SomeLeetcodeTaskTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.removeStones({{0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 2}}));
    ASSERT_EQ(3, solution.removeStones({{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}}));
    ASSERT_EQ(0, solution.removeStones({{0, 0}}));
}

TEST(SomeLeetcodeTaskTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(6, solution.removeStones({{3, 2}, {0, 0}, {3, 3}, {2, 1}, {2, 3}, {2, 2}, {0, 2}}));
}

}