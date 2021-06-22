#include <map>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isNStraightHand(std::vector<int> const &hand, int groupSize) const
    {
        if (hand.size() % groupSize != 0)
            return false;
        std::map<int, int> cardMap;
        for (int card : hand)
            ++cardMap[card];
        for (size_t group = 0; group < hand.size() / groupSize; ++group)
        {
            auto iterator = cardMap.begin();
            int prevCard = iterator->first;
            --iterator->second;
            iterator = checkMoveNext(cardMap, iterator);
            for (size_t groupIndex = 1; groupIndex < groupSize; ++groupIndex)
            {
                if (iterator == cardMap.end())
                    return false;
                if (iterator->first > prevCard + 1)
                    return false;
                prevCard = iterator->first;
                --iterator->second;
                iterator = checkMoveNext(cardMap, iterator);
            }
        }
        return true;
    }

private:
    std::map<int, int>::iterator checkMoveNext(std::map<int, int> &cardMap, std::map<int, int>::iterator iterator) const
    {
        if (iterator->second == 0)
        {
            const auto current = iterator++;
            cardMap.erase(current);
        }
        else
            ++iterator;
        return iterator;
    }
};

}

namespace HandOfStraightsTask
{

TEST(HandOfStraightsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isNStraightHand({1, 2, 3, 6, 2, 3, 4, 7, 8}, 3));
    ASSERT_EQ(false, solution.isNStraightHand({1, 2, 3, 4, 5}, 4));
}

}