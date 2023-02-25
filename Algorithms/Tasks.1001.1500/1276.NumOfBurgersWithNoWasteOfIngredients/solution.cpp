#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] std::vector<int> numOfBurgers(int tomatoSlices, int cheeseSlices) const
    {
        // 4 * X + 2 * Y = tomatoSlices, X + Y = cheeseSlices =>
        // 2 * X + 2 * cheeseSlices = tomatoSlices => X = tomatoSlices / 2 - cheeseSlices
        // Y = cheeseSlices - X = cheeseSlices - (tomatoSlices / 2 - cheeseSlices) = 2 * cheeseSlices - tomatoSlices / 2
        if (tomatoSlices % 2 == 1)
            return {};
        int x = tomatoSlices / 2 - cheeseSlices;
        if (x < 0)
            return {};
        int y = cheeseSlices - x;
        if (y < 0)
            return {};
        return {x, y};
    }
};

}

namespace NumOfBurgersWithNoWasteOfIngredientsTask
{

TEST(NumOfBurgersWithNoWasteOfIngredientsTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 6}), solution.numOfBurgers(16, 7));
    ASSERT_EQ(std::vector<int>(), solution.numOfBurgers(17, 4));
    ASSERT_EQ(std::vector<int>(), solution.numOfBurgers(4, 17));
}

}