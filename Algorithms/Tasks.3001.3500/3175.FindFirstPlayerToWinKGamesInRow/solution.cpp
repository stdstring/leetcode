#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findWinningPlayer(std::vector<int> const &skills, int k) const
    {
        size_t maxSkillPlayer = 0;
        std::queue<size_t> players;
        for (size_t index = 0; index < skills.size(); ++index)
        {
            players.emplace(index);
            if (skills[index] > skills[maxSkillPlayer])
                maxSkillPlayer = index;
        }
        if (maxSkillPlayer == 0)
            return 0;
        int winCount = 0;
        size_t firstPlayer = players.front();
        players.pop();
        while (winCount < k)
        {
            size_t currentPlayer = players.front();
            players.pop();
            if (skills[firstPlayer] > skills[currentPlayer])
            {
                ++winCount;
                players.emplace(currentPlayer);
            }
            else
            {
                players.emplace(firstPlayer);
                firstPlayer = currentPlayer;
                winCount = 1;
            }
            if (firstPlayer == maxSkillPlayer)
                return static_cast<int>(maxSkillPlayer);
        }
        return static_cast<int>(firstPlayer);
    }
};

}

namespace FindFirstPlayerToWinKGamesInRowTask
{

TEST(FindFirstPlayerToWinKGamesInRowTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.findWinningPlayer({4, 2, 6, 3, 9}, 2));
    ASSERT_EQ(1, solution.findWinningPlayer({2, 5, 4}, 3));
}

}