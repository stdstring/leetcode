#include <numeric>
#include <queue>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] long long pickGifts(std::vector<int> const &gifts, int k) const
    {
        long long giftsRest = std::accumulate(gifts.cbegin(), gifts.cend(), 0LL);
        std::priority_queue<int> giftsQueue(gifts.cbegin(), gifts.cend());
        for (int time = 1; time <= k; ++time)
        {
            int pile = giftsQueue.top();
            giftsQueue.pop();
            int pileRoot = calcSquareRoot(pile);
            giftsRest -= (pile - pileRoot);
            giftsQueue.push(pileRoot);
        }
        return giftsRest;
    }

private:
    [[nodiscard]] int calcSquareRoot(int value) const
    {
        if (value == 1)
            return value;
        for (int rootValue = 2;; ++rootValue)
        {
            int product = rootValue * rootValue;
            if (product == value)
                return rootValue;
            if (product > value)
                return rootValue - 1;
        }
    }
};

}

namespace TakeGiftsFromRichestPileTask
{

TEST(TakeGiftsFromRichestPileTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(29, solution.pickGifts({25, 64, 9, 4, 100}, 4));
    ASSERT_EQ(4, solution.pickGifts({1, 1, 1, 1}, 4));
}

}