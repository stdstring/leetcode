#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int smallestRepunitDivByK(int k) const
    {
        if ((k % 2 == 0) || (k % 5 == 0))
            return -1;
        std::vector<bool> knownRests(k, false);
        size_t numberSize = 1;
        int currentNumber = 1;
        while (currentNumber != 0)
        {
            while (currentNumber < k)
            {
                currentNumber = 10 * currentNumber + 1;
                ++numberSize;
            }
            currentNumber %= k;
            if (knownRests[currentNumber])
                return -1;
            knownRests[currentNumber] = true;
        }
        return static_cast<int>(numberSize);
    }
};

}

namespace SmallestIntegerDivisibleByKTask
{

TEST(SmallestIntegerDivisibleByKTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(1, solution.smallestRepunitDivByK(1));
    ASSERT_EQ(-1, solution.smallestRepunitDivByK(2));
    ASSERT_EQ(3, solution.smallestRepunitDivByK(3));
}

}