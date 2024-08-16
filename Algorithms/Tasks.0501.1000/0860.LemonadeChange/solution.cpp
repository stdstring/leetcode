#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] bool lemonadeChange(std::vector<int> const &bills) const
    {
        size_t change5Count = 0;
        size_t change10Count = 0;
        for (const int bill : bills)
        {
            if (bill == 5)
                ++change5Count;
            if (bill == 10)
            {
                if (change5Count == 0)
                    return false;
                --change5Count;
                ++change10Count;
            }
            if (bill == 20)
            {
                if ((change5Count > 0) && (change10Count > 0))
                {
                    --change5Count;
                    --change10Count;
                }
                else if (change5Count > 2)
                    change5Count -= 3;
                else
                    return false;
            }
        }
        return true;
    }
};

}

namespace LemonadeChangeTask
{

TEST(LemonadeChangeTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.lemonadeChange({5, 5, 5, 10, 20}));
    ASSERT_EQ(false, solution.lemonadeChange({5, 5, 10, 10, 20}));
}

TEST(LemonadeChangeTaskTests, FromWrongAnswers)
{
    constexpr Solution solution;
    ASSERT_EQ(true, solution.lemonadeChange({5, 5, 10, 20, 5, 5, 5, 5, 5, 5, 5, 5, 5, 10, 5, 5, 20, 5, 20, 5}));
}

}