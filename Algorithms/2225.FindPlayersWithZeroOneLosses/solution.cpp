#include <map>
#include <vector>


#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<std::vector<int>> findWinners(std::vector<std::vector<int>> const &matches) const
    {
        std::map<int, size_t> playerLossesMap;
        for (std::vector<int> const &match : matches)
        {
            auto winnerIterator = playerLossesMap.find(match[0]);
            if (winnerIterator == playerLossesMap.cend())
                playerLossesMap.emplace(match[0], 0);
            ++playerLossesMap[match[1]];
        }
        std::vector<std::vector<int>> result(2, std::vector<int>());
        for (auto [player, lossesCount] : playerLossesMap)
        {
            switch (lossesCount)
            {
                case 0:
                    result[0].emplace_back(player);
                    break;
                case 1:
                    result[1].emplace_back(player);
                    break;
                default:
                    break;
            }
        }
        return result;
    }
};

}

namespace FindPlayersWithZeroOneLossesTask
{

TEST(FindPlayersWithZeroOneLossesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2, 10}, {4, 5, 7, 8}}),
              solution.findWinners({{1, 3}, {2, 3}, {3, 6}, {5, 6}, {5, 7}, {4, 5}, {4, 8}, {4, 9}, {10, 4}, {10, 9}}));
    ASSERT_EQ(std::vector<std::vector<int>>({{1, 2, 5, 6}, {}}), solution.findWinners({{2, 3}, {1, 3}, {5, 4}, {6, 4}}));
}

}