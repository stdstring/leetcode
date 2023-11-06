#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxCoins(std::vector<int> const &piles) const
    {
        std::vector<int> sortedPiles(piles);
        std::ranges::sort(sortedPiles, std::greater<int>());
        int result = 0;
        for (size_t index = 0; index < sortedPiles.size() / 3; ++index)
            result += sortedPiles[2 * index + 1];
        return result;
    }
};

}

namespace MaxNumberCoinsYouCanGetTask
{

TEST(MaxNumberCoinsYouCanGetTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(9, solution.maxCoins({2, 4, 1, 2, 7, 8}));
    ASSERT_EQ(4, solution.maxCoins({2, 4, 5}));
    ASSERT_EQ(18, solution.maxCoins({9, 8, 7, 6, 5, 1, 2, 3, 4}));
}

}