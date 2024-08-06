#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int nonSpecialCount(int l, int r) const
    {
        const int totalNumberCount = r - l + 1;
        int specialCount = 0;
        if ((l <= 4) && (4 <= r))
            ++specialCount;
        for(int number = 3;; number += 2)
        {
            const int square = number * number;
            if (square < l)
                continue;
            if (square > r)
                break;
            if (isOddPrime(number))
                ++specialCount;
        }
        return totalNumberCount - specialCount;
    }

private:
    bool isOddPrime(int oddNumber) const
    {
        for (int factor = 3; factor * factor <= oddNumber; factor += 2)
        {
            if ((oddNumber % factor) == 0)
                return false;
        }
        return true;
    }
};

}

namespace FindCountNumbersWhichAreNotSpecialTask
{

TEST(FindCountNumbersWhichAreNotSpecialTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(3, solution.nonSpecialCount(5, 7));
    ASSERT_EQ(11, solution.nonSpecialCount(4, 16));
}

}