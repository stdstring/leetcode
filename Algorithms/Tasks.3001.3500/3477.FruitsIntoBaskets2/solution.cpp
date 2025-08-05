#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int numOfUnplacedFruits(std::vector<int> const &fruits, std::vector<int> const &baskets) const
    {
        std::vector<bool> usedBaskets(baskets.size(), false);
        int result = 0;
        for (const int fruit : fruits)
        {
            bool placed = false;
            for (size_t basketIndex = 0; basketIndex < baskets.size(); ++basketIndex)
            {
                if (usedBaskets[basketIndex])
                    continue;
                if (baskets[basketIndex] >= fruit)
                {
                    usedBaskets[basketIndex] = true;
                    placed = true;
                    break;
                }
            }
            if (!placed)
                ++result;
        }
        return result;
    }
};

}

namespace FruitsIntoBaskets2Task
{

TEST(FruitsIntoBaskets2TaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.numOfUnplacedFruits({4, 2, 5}, {3, 5, 4}));
    ASSERT_EQ(0, solution.numOfUnplacedFruits({3, 6, 1}, {6, 4, 7}));
}

}