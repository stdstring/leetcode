#include <algorithm>
#include <string>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int minSwaps(std::string const &s) const
    {
        std::string buffer(s);
        int balance = 0;
        size_t swapCount = 0;
        for (size_t start = 0, end = s.size() - 1; start < end; ++start)
        {
            balance += (buffer[start] == '[' ? 1 : -1);
            if (balance < 0)
            {
                while (buffer[end] != '[')
                    --end;
                std::swap(buffer[start], buffer[end]);
                balance += 2;
                ++swapCount;
            }
        }
        return static_cast<int>(swapCount);
    }
};

}

namespace MinNumberSwapsMakeStringBalancedTask
{

TEST(MinNumberSwapsMakeStringBalancedTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(1, solution.minSwaps("][]["));
    ASSERT_EQ(2, solution.minSwaps("]]][[["));
    ASSERT_EQ(0, solution.minSwaps("[]"));
}

}