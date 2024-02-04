#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int findSmallestInteger(std::vector<int> const &nums, int value) const
    {
        std::vector<int> restCount(value, 0);
        for (const int number : nums)
        {
            int rest = number % value;
            if (rest < 0)
                rest += value;
            ++restCount[rest];
        }
        long long smallestNumber = INT_MAX;
        for (int rest = 0; rest < value; ++rest)
            smallestNumber = std::min(smallestNumber, 1LL * restCount[rest] * value + rest);
        return static_cast<int>(smallestNumber);
    }
};

}

namespace SmallestMissingNonNegativeIntTask
{

TEST(SmallestMissingNonNegativeIntTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(4, solution.findSmallestInteger({1, -10, 7, 13, 6, 8}, 5));
    ASSERT_EQ(2, solution.findSmallestInteger({1, -10, 7, 13, 6, 8}, 7));
}

}