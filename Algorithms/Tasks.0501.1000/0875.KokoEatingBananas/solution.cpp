#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minEatingSpeed(std::vector<int> const &piles, int h) const
    {
        int leftValue = 1;
        int rightValue = *std::max_element(piles.cbegin(), piles.cend());
        while (leftValue < rightValue)
        {
            const int middleValue = (leftValue + rightValue) / 2;
            const int hours = calcHours(piles, middleValue);
            if (hours <= h)
                rightValue = middleValue;
            if (hours > h)
                leftValue = middleValue + 1;
        }
        return leftValue;
    }

private:
    [[nodiscard]] int calcHours(std::vector<int> const &piles, int value) const
    {
        int hours = 0;
        for (const int pile : piles)
            hours += pile / value + (pile % value == 0 ? 0 : 1);
        return hours;
    }
};

}

namespace KokoEatingBananasTask
{

TEST(KokoEatingBananasTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(4, solution.minEatingSpeed({3, 6, 7, 11}, 8));
    ASSERT_EQ(30, solution.minEatingSpeed({30, 11, 23, 4, 20}, 5));
    ASSERT_EQ(23, solution.minEatingSpeed({30, 11, 23, 4, 20}, 6));
}

TEST(KokoEatingBananasTaskTests, FromWrongAnswers)
{
    const Solution solution;
    ASSERT_EQ(2, solution.minEatingSpeed({312884470}, 312884469));
    ASSERT_EQ(14, solution.minEatingSpeed({332484035,
                                           524908576,
                                           855865114,
                                           632922376,
                                           222257295,
                                           690155293,
                                           112677673,
                                           679580077,
                                           337406589,
                                           290818316,
                                           877337160,
                                           901728858,
                                           679284947,
                                           688210097,
                                           692137887,
                                           718203285,
                                           629455728,
                                           941802184}, 823855818));
}

}
