#include <algorithm>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int reachNumber(int target) const
    {
        // when target 4:
        // 1 + 2 + 3 = 6 (So, 4 is Over)
        // Now, just think that we can surely make this equation to form 4 by flipping 1 to(-1).
        // So then summation will be 6 - (1 + 1) == 4.
        // So, assumption is when we flip a number(here 1) then we have to subtract that number from the summation(here 6) twice (here 6 - (1 + 1) == 4).
        // So, from here what we can observe that as for flipping we have to subtract twice of some number from summation.
        // So, obviously we are subtracting even number (here we are flipping 1, So we have to subtract(1 + 1) which is even from summation 6)
        // and finally we can reach goal target 4.
        // when target 5:
        // 1 + 2 + 3 + 4 + 5 = 15;
        // if we flip 5 to(-5), then what we can observe here .....our now sum value will be 15 - (5 + 5) = 5,
        // let's see this as series below: 1 + 2 + 3 + 4 - 5 = 5;
        // That means we have to search for when Our summation(15) will be over our target(5) where our difference(10) is even number,
        // because to flip a number(5) from positive(+5) to negative(-5) we have to subtract twice(5 + 5) of that number
        // So, we will get our target step, when our summation and target value difference is even number
        target = std::abs(target);
        for (int number = 1, sum = 0;; ++number)
        {
            sum += number;
            if (sum == target)
                return number;
            if ((sum > target) && (((sum - target) % 2) == 0))
                return number;
        }
    }
};

}

namespace ReachNumberTask
{

TEST(ReachNumberTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.reachNumber(2));
    ASSERT_EQ(2, solution.reachNumber(3));
}

TEST(ReachNumberTaskTests, CustomExamples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.reachNumber(4));
    ASSERT_EQ(5, solution.reachNumber(5));
}

}