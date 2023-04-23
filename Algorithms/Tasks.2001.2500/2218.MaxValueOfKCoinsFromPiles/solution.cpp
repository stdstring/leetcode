#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxValueOfCoins(std::vector<std::vector<int>> const &piles, int k) const
    {
        std::vector<int> dpCurrent(k + 1, 0);
        for (std::vector<int> const &pile : piles)
        {
            std::vector<int> dpNext(dpCurrent);
            for (size_t index = 0; index < dpCurrent.size(); ++index)
            {
                int pileSum = 0;
                for (size_t pileIndex = 0; (pileIndex < pile.size()) && ((index + pileIndex + 1) < dpCurrent.size()); ++pileIndex)
                {
                    pileSum += pile[pileIndex];
                    dpNext[index + pileIndex + 1] = std::max(dpNext[index + pileIndex + 1], dpCurrent[index] + pileSum);
                }
            }
            std::swap(dpNext, dpCurrent);
        }
        return dpCurrent.back();
    }
};

}

namespace MaxValueOfKCoinsFromPilesTask
{

TEST(MaxValueOfKCoinsFromPilesTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(101, solution.maxValueOfCoins({{1, 100, 3}, {7, 8, 9}}, 2));
    ASSERT_EQ(706, solution.maxValueOfCoins({{100}, {100}, {100}, {100}, {100}, {100}, {1, 1, 1, 1, 1, 1, 700}}, 7));
}

}