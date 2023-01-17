#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int flipgame(std::vector<int> const &fronts, std::vector<int> const &backs) const
    {
        std::map<int, bool> cardsMap;
        for (size_t index = 0; index < fronts.size(); ++index)
        {
            if (cardsMap.count(fronts[index]) == 0)
                cardsMap.emplace(fronts[index], false);
            if (cardsMap.count(backs[index]) == 0)
                cardsMap.emplace(backs[index], false);
            if (fronts[index] == backs[index])
                cardsMap[fronts[index]] = true;
        }
        int cardValue = 0;
        for (auto const &entry : cardsMap)
        {
            if (!entry.second)
            {
                cardValue = entry.first;
                break;
            }
        }
        return cardValue;
    }
};

}

namespace CardFlippingGameTask
{

TEST(CardFlippingGameTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(2, solution.flipgame({1, 2, 4, 4, 7}, {1, 3, 4, 1, 3}));
    ASSERT_EQ(0, solution.flipgame({1}, {1}));
}

}