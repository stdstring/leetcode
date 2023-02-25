#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int totalFruit(std::vector<int> const &fruits) const
    {
        size_t fruitCount = 0;
        int firstBasket = fruits.front();
        int secondBasket = -1;
        for (size_t start = 0, end = 0; end < fruits.size(); ++end)
        {
            const int current = fruits[end];
            if (current == firstBasket)
            {
                // do nothing
            }
            else if ((current == secondBasket) || (secondBasket == -1))
                secondBasket = current;
            else
            {
                while (fruits[start] == firstBasket)
                    ++start;
                end = start;
                firstBasket = secondBasket;
                secondBasket = -1;
            }
            fruitCount = std::max(fruitCount, end - start + 1);
        }
        return static_cast<int>(fruitCount);
    }
};

}

namespace FruitIntoBasketsTask
{

TEST(FruitIntoBasketsTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.totalFruit({1, 2, 1}));
    ASSERT_EQ(3, solution.totalFruit({0, 1, 2, 2}));
    ASSERT_EQ(4, solution.totalFruit({1, 2, 3, 2, 2}));
}

TEST(FruitIntoBasketsTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(5, solution.totalFruit({3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4}));
}

}
