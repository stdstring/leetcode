#include <algorithm>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> deckRevealedIncreasing(std::vector<int> const &deck) const
    {
        std::vector<int> sortedDeck(deck);
        std::sort(sortedDeck.begin(), sortedDeck.end());
        std::queue<size_t> initIndices;
        for (size_t index = 0; index < sortedDeck.size(); ++index)
            initIndices.push(index);
        std::queue<size_t> indices;
        while (!initIndices.empty())
        {
            indices.push(initIndices.front());
            initIndices.pop();
            if (!initIndices.empty())
            {
                initIndices.push(initIndices.front());
                initIndices.pop();
            }
        }
        std::vector<int> result(sortedDeck.size(), 0);
        for (size_t index = 0; index < sortedDeck.size(); ++index)
        {
            result[indices.front()] = sortedDeck[index];
            indices.pop();
        }
        return result;
    }
};

}

namespace RevealCardsIncreasingOrderTask
{

TEST(RevealCardsIncreasingOrderTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({2, 13, 3, 11, 5, 17, 7}), solution.deckRevealedIncreasing({17, 13, 11, 2, 3, 5, 7}));
}

}
