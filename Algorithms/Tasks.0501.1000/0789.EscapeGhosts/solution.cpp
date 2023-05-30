#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool escapeGhosts(std::vector<std::vector<int>> const &ghosts, std::vector<int> const &target) const
    {
        const int playerDistance = std::abs(target[0]) + std::abs(target[1]);
        return std::all_of(ghosts.cbegin(), ghosts.cend(), [&target, playerDistance](std::vector<int> const& ghost)
        {
            return playerDistance < std::abs(target[0] - ghost[0]) + std::abs(target[1] - ghost[1]);
        });
    }
};

}

namespace EscapeGhostsTask
{

TEST(EscapeGhostsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.escapeGhosts({{1, 0}, {0, 3}}, {0, 1}));
    ASSERT_EQ(false, solution.escapeGhosts({{1, 0}}, {2, 0}));
    ASSERT_EQ(false, solution.escapeGhosts({{2, 0}}, {1, 0}));
}

}