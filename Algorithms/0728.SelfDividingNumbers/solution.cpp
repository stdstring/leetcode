#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    std::vector<int> selfDividingNumbers(int left, int right) const
    {
        std::vector<int> result;
        for (int number = left; number <= right; ++number)
        {
            if (isSelfDividingNumber(number))
                result.push_back(number);
        }
        return result;
    }

private:
    bool isSelfDividingNumber(int number) const
    {
        int rest = number;
        while (rest != 0)
        {
            const int digit = rest % 10;
            if ((digit == 0) || (number % digit != 0))
                return false;
            rest /= 10;
        }
        return true;
    }
};

}

namespace SelfDividingNumbersTask
{

TEST(SelfDividingNumbersTaskTests, Examples)
{
    const Solution solution;
    ASSERT_EQ(std::vector<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 12, 15, 22}), solution.selfDividingNumbers(1, 22));
}

}