#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int matchPlayersAndTrainers(std::vector<int> const &players, std::vector<int> const &trainers) const
    {
        std::vector<int> sortedPlayers(players);
        std::ranges::sort(sortedPlayers);
        std::vector<int> sortedTrainers(trainers);
        std::ranges::sort(sortedTrainers);
        size_t matchCount = 0;
        for (size_t playerIndex = 0, trainerIndex = 0; (playerIndex < sortedPlayers.size()) && (trainerIndex < sortedTrainers.size());)
        {
            if (sortedPlayers[playerIndex] <= sortedTrainers[trainerIndex])
            {
                ++matchCount;
                ++playerIndex;
            }
            ++trainerIndex;
        }
        return static_cast<int>(matchCount);
    }
};

}

namespace MaxMatchingPlayersWithTrainersTask
{

TEST(MaxMatchingPlayersWithTrainersTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.matchPlayersAndTrainers({4, 7, 9}, {8, 2, 5, 8}));
    ASSERT_EQ(1, solution.matchPlayersAndTrainers({1, 1, 1}, {10}));
}

}