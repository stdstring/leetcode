#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numEquivDominoPairs(std::vector<std::vector<int>> const &dominoes) const
    {
        std::unordered_map<int, size_t> dominoMap;
        for (std::vector<int> const &domino : dominoes)
            ++dominoMap[domino[0] <= domino[1] ? 10 * domino[0] + domino[1] : 10 * domino[1] + domino[0]];
        size_t result = 0;
        for (auto const& [_, count] : dominoMap)
            // sum of (count - 1) members of arith progression: 1 ...
            result +=  count * (count - 1) / 2;
        return static_cast<int>(result);
    }
};

}

namespace NumberOfEquivalentDominoPairsTask
{

TEST(NumberOfEquivalentDominoPairsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.numEquivDominoPairs({{1, 2}, {2, 1}, {3, 4}, {5, 6}}));
    ASSERT_EQ(3, solution.numEquivDominoPairs({{1, 2}, {1, 2}, {1, 1}, {1, 2}, {2, 2}}));
}

}
