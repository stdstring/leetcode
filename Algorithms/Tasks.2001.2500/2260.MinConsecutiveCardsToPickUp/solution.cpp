#include <unordered_map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumCardPickup(std::vector<int> const &cards) const
    {
        std::unordered_map<int, CardData> cardMap;
        for (size_t index = 0; index < cards.size(); ++index)
        {
            auto iterator = cardMap.find(cards[index]);
            if (iterator == cardMap.end())
                cardMap.emplace(cards[index], index);
            else
            {
                const size_t currentSize = index - iterator->second.LastPos + 1;
                iterator->second.LastPos = index;
                if ((iterator->second.BestSize == 0) || (currentSize < iterator->second.BestSize))
                    iterator->second.BestSize = currentSize;
            }
        }
        size_t bestSize = 0;
        for (auto const &[_, data] : cardMap)
        {
            if (data.BestSize == 0)
                continue;
            if ((bestSize == 0) || (data.BestSize < bestSize))
                bestSize = data.BestSize;
        }
        return bestSize == 0 ? -1 : static_cast<int>(bestSize);
    }

private:
    struct CardData
    {
        explicit CardData(size_t lastPos) : LastPos(lastPos)
        {
        }

        size_t LastPos;
        size_t BestSize = 0;
    };
};

}

namespace MinConsecutiveCardsToPickUpTask
{

TEST(MinConsecutiveCardsToPickUpTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.minimumCardPickup({3, 4, 2, 3, 4, 7}));
    ASSERT_EQ(-1, solution.minimumCardPickup({1, 0, 5, 3}));
}

}