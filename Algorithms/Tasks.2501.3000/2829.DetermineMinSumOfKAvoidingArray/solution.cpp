#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minimumSum(int n, int k) const
    {
        std::vector<bool> bannedNumbers(k + 1, false);
        int result = 0;
        int usedNumbers = 0;
        int currentNumber = 1;
        while (usedNumbers < n)
        {
            if ((currentNumber >= k) || !bannedNumbers[currentNumber])
            {
                if (currentNumber < k)
                    bannedNumbers[k - currentNumber] = true;
                ++usedNumbers;
                result += currentNumber;
            }
            ++currentNumber;
        }
        return result;
    }
};

}

namespace DetermineMinSumOfKAvoidingArrayTask
{

TEST(DetermineMinSumOfKAvoidingArrayTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(18, solution.minimumSum(5, 4));
    ASSERT_EQ(3, solution.minimumSum(2, 6));
}

}