#include <algorithm>
#include <numeric>
#include <vector>

#include "gtest/gtest.h"

namespace
{

class Solution
{
public:
    [[nodiscard]] int maxSatisfied(std::vector<int> const &customers, std::vector<int> const &grumpy, int minutes) const
    {
        const size_t minutesValue = minutes;
        if (minutesValue == customers.size())
            return std::accumulate(customers.cbegin(), customers.cend(), 0);
        bool hasGrumpy = false;
        int initSatisfied = 0;
        for (size_t index = 0; index < customers.size(); ++index)
        {
            if (grumpy[index] == 1)
                hasGrumpy = true;
            else
                initSatisfied += customers[index];
        }
        if (!hasGrumpy)
            return initSatisfied;
        // init sliding window
        int slidingWindowValue = 0;
        for (size_t index = 0; index < minutesValue; ++index)
        {
            if (grumpy[index] == 1)
                slidingWindowValue += customers[index];
        }
        int bestSatisfied = initSatisfied + slidingWindowValue;
        // move sliding window
        for (size_t index = minutesValue; index < customers.size(); ++index)
        {
            if (grumpy[index - minutesValue] == 1)
                slidingWindowValue -= customers[index - minutesValue];
            if (grumpy[index] == 1)
                slidingWindowValue += customers[index];
            bestSatisfied = std::max(bestSatisfied, initSatisfied + slidingWindowValue);
        }
        return bestSatisfied;
    }
};

}

namespace GrumpyBookstoreOwnerTask
{

TEST(GrumpyBookstoreOwnerTaskTests, Examples)
{
    constexpr Solution solution;
    ASSERT_EQ(16, solution.maxSatisfied({1, 0, 1, 2, 1, 1, 7, 5}, {0, 1, 0, 1, 0, 1, 0, 1}, 3));
    ASSERT_EQ(1, solution.maxSatisfied({1}, {0}, 1));
}

}