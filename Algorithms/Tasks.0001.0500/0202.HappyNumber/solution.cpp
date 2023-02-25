#include <array>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    bool isHappy(int n) const
    {
        std::array<bool, 4 + 9 * 81> sumStorage{};
        sumStorage.fill(false);
        int sum = n;
        while (sum != 1)
        {
            sum = calcDigitsSquareSum(sum);
            if (sumStorage[sum])
                return false;
            sumStorage[sum] = true;
        }
        return true;
    }

private:
    int calcDigitsSquareSum(int n) const
    {
        if (n < 10)
            return n * n;
        const int lastDigit = n % 10;
        return (lastDigit * lastDigit) + calcDigitsSquareSum(n / 10);
    }
};

}

namespace HappyNumberTest
{

TEST(HappyNumberTestTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(true, solution.isHappy(19));
}

}