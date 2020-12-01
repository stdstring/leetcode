#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool canPlaceFlowers(std::vector<int> const &flowerbed, int n) const
    {
        if (n == 0)
            return true;
        int flowersCount = 0;
        for(size_t index = 0; index < flowerbed.size();)
        {
            const bool leftGood = (index == 0) || (flowerbed[index - 1] == 0);
            const bool rightGood = (index == flowerbed.size() - 1) || (flowerbed[index + 1] == 0);
            if (flowerbed[index] == 0 && leftGood && rightGood)
            {
                ++flowersCount;
                ++index;
            }
            if (flowersCount == n)
                return true;
            ++index;
        }
        return false;
    }
};

}

namespace CanPlaceFlowersTask
{

TEST(CanPlaceFlowersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.canPlaceFlowers({1, 0, 0, 0, 1}, 1));
    ASSERT_EQ(false, solution.canPlaceFlowers({1, 0, 0, 0, 1}, 2));
}

}
