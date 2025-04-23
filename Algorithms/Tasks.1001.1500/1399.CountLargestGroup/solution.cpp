#include <unordered_map>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int countLargestGroup(int n) const
    {
        std::unordered_map<int, int> digitSumMap;
        for (int number = 1; number <= n; ++number)
            ++digitSumMap[calcDigitCount(number)];
        int bestCount = 0;
        int bestSize = 0;
        for (auto [_, size] : digitSumMap)
        {
            if (bestSize < size)
            {
                bestSize = size;
                bestCount = 0;
            }
            if (bestSize == size)
                ++bestCount;
        }
        return bestCount;
    }

private:
    [[nodiscard]] int calcDigitCount(int number) const
    {
        int result = 0;
        for (;number > 0; number /= 10)
            result += (number % 10);
        return result;
    }
};

}

namespace CountLargestGroupTask
{

TEST(CountLargestGroupTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.countLargestGroup(13));
    ASSERT_EQ(2, solution.countLargestGroup(2));
}

}